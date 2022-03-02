#include "extraflame.h"
#include "esphome/core/log.h"
#ifdef USE_EXTRAFLAME_DUMP
#include <sstream>
#include <iomanip>
#endif

namespace esphome
{
  namespace extraflame
  {

    static const char *TAG = "extraflame.hub";
    static const char *CURRENT_REQUEST = "extraflame.hub.request";

    static uint8_t get_memory_from_command(uint8_t command)
    {
      if (command == 0x80)
      {
        return 0x00;
      }
      else if (command == 0xA0)
      {
        return 0x20;
      }
      return command;
    }

    void ExtraflameHub::dump_config()
    {
      ESP_LOGCONFIG(TAG, "ExtraflameHub:");
#ifdef USE_EXTRAFLAME_DUMP
      ESP_LOGCONFIG(TAG, "  Dump functionality included");
#endif

      for (auto *component : this->components_)
      {
        component->dump_config_internal();
      }

      this->check_uart_settings(1200, 2, uart::UARTParityOptions::UART_CONFIG_PARITY_NONE, 8);
    }

    void ExtraflameHub::loop()
    {
      while (this->available() >= 2 && this->status_ != NO_REQUEST)
      {
        auto response = *this->read_array<2>();

        ESP_LOGV(TAG, "Read value: 0x%02X 0x%02X", response[0], response[1]);

        if ((this->status_ == REQUEST_SEND && this->is_request_echo_(response, 0)) ||
            (this->status_ == REQUEST_ECHO && this->request_.command.size() == 4 && this->is_request_echo_(response, 2)))
        {
          ESP_LOGV(TAG, "Response was request echo");
          this->status_ = REQUEST_ECHO;
          continue;
        }

        this->cancel_timeout(CURRENT_REQUEST);
        uint8_t value = response[1];
        bool success = true;

        // checksum is calculated by (memory + address + value) & 0xFF
        uint8_t checksum_calc = (this->request_.command[0] + this->request_.command[1] + response[1]) & 0xFF;
        if (checksum_calc != response[0])
        {
          ESP_LOGW(TAG, "Checksum invalid. Skipping update");
          this->reset_input_buffer();
          success = false;
        }
        else
        {
          this->notify_components_(get_memory_from_command(this->request_.command[0]), this->request_.command[1], value);
        }

        if (this->request_.on_response != nullptr)
        {
          this->request_.on_response(value, success);
        }
        this->status_ = NO_REQUEST;
      }

      next_request_();
    }

    void ExtraflameHub::next_request_()
    {
      if (this->status_ == NO_REQUEST)
      {
#ifdef USE_EXTRAFLAME_DUMP
        if (this->dump_.current <= this->dump_.end && this->is_dumping())
        {
          ESP_LOGD(TAG, "Dump 0x%02X", this->dump_.current);

          auto request = ExtraflameRequest{
              .command = {this->dump_.memory, this->dump_.current},
              .on_response = [this](uint8_t value, bool success) {
                if (success)
                {
                  std::ostringstream s1, s2;
                  s1 << this->dump_.data << ",\"0x" << std::hex << static_cast<int>(this->dump_.current) << "\":";
                  s2 << s1.str() << int(value);
                  this->dump_.data = s2.str();
                }
                if (this->dump_.current == this->dump_.end)
                {
                  this->dump_.data = this->dump_.data + "}";
                  ESP_LOGD(TAG, "Dump complete");
                  for (auto *trigger : this->finish_triggers_)
                  {
                    trigger->process(this->dump_.data);
                  }
                  this->dump_.data = "";
                }
                else
                {
                  this->dump_.current = this->dump_.current + 1;
                }
              }};

          this->send_request_(request);
          return; //required
        }
#endif
        if (!this->request_queue_.empty())
        {
          auto request = this->request_queue_.front();
          this->request_queue_.erase(request_queue_.begin());
          this->send_request_(request);
        }
      }
    }

    void ExtraflameHub::send_request_(ExtraflameRequest request)
    {
      this->status_ = REQUEST_SEND;
      this->request_ = request;
      this->set_timeout(CURRENT_REQUEST, 1000, [this] {
        if (this->request_.command.size() == 2)
        {
          ESP_LOGW(TAG, "No response for given command: 0x%02X 0x%02X", this->request_.command[0],
                   this->request_.command[1]);
        }
        else
        {
          ESP_LOGW(TAG, "No response for given command: 0x%02X 0x%02X  0x%02X  0x%02X", this->request_.command[0],
                   this->request_.command[1], this->request_.command[2], this->request_.command[3]);
        }
        this->reset_input_buffer();
        if (this->request_.on_response != nullptr)
        {
          this->request_.on_response(0x00, false);
        }
        this->status_ = NO_REQUEST;
      });

      if (this->request_.command.size() == 2)
      {
        ESP_LOGV(TAG, "Sending request: 0x%02X 0x%02X", this->request_.command[0], this->request_.command[1]);
      }
      else
      {
        ESP_LOGV(TAG, "Sending request: 0x%02X 0x%02X  0x%02X  0x%02X", this->request_.command[0],
                 this->request_.command[1], this->request_.command[2], this->request_.command[3]);
      }

      this->write_array(this->request_.command);
    }

    void ExtraflameHub::add_request(ExtraflameRequest request, bool priority)
    {
      ESP_LOGV(TAG, "Adding request");
      if (priority)
      {
        this->request_queue_.insert(this->request_queue_.begin(), request);
      }
      else
      {
        this->request_queue_.push_back(request);
      }
      this->next_request_();
    }

    void ExtraflameHub::add_request(std::vector<uint8_t> command)
    {
      auto request = ExtraflameRequest{.command = command, .on_response = nullptr};
      this->add_request(request, false);
    }

    void ExtraflameHub::reset_input_buffer()
    {
      ESP_LOGW(TAG, "Reseting buffer and going on with next request");
      while (this->available() > 0)
      {
        // to clear the buffer
        this->read();
      }
    }

    void ExtraflameHub::add_component(ExtraflameComponent *component) { this->components_.push_back(component); }

    void ExtraflameHub::notify_components_(uint8_t memory, uint8_t address, uint8_t value)
    {
      for (auto *component : this->components_)
      {
        if (memory == component->get_memory() && address == component->get_address())
        {
          component->on_read_response(value);
        }
      }
    }

    bool ExtraflameHub::is_request_echo_(std::array<uint8_t, 2> response, int request_part_num)
    {
      return this->request_.command[request_part_num] == response[0] &&
             this->request_.command[request_part_num + 1] == response[1];
    }

#ifdef USE_EXTRAFLAME_DUMP
    void ExtraflameHub::start_dumping(uint8_t memory, uint8_t start, uint8_t end, const std::vector<ExtraflameDumpFinishTrigger *> &finish_triggers)
    {
      ESP_LOGD(TAG, "Starting to dump config values of 0x%02X", memory);

      if (start > end)
      {
        ESP_LOGE(TAG, "'start' must be lower or equal to 'end'");
      }
      else if (this->is_dumping())
      {
        ESP_LOGE(TAG, "Already dumping!");
      }
      else
      {
        this->request_queue_.clear();
        std::ostringstream stringStream;
        stringStream << "{\"memory\":\"0x" << std::hex << static_cast<int>(memory) << "\"";
        this->dump_ = Dump{
            .memory = memory,
            .current = start,
            .end = end,
            .data = stringStream.str()};
        this->finish_triggers_ = finish_triggers;
      }
    }

    bool ExtraflameHub::is_dumping()
    {
      return this->dump_.data != "";
    }
#endif

    ExtraflameComponent::ExtraflameComponent(uint8_t memory, uint8_t address)
    {
      this->memory_ = memory;
      this->address_ = address;
    }

    void ExtraflameComponent::setup() { this->parent_->add_component(this); }

    void ExtraflameComponent::update() { this->parent_->add_request({this->get_memory(), this->get_address()}); }

    void ExtraflameComponent::dump_config_internal()
    {
      this->dump_config_internal_();
      ESP_LOGCONFIG(TAG, "    Update Interval: %.1fs", this->get_update_interval() / 1000.0f);
      ESP_LOGCONFIG(TAG, "    Memory: 0x%02X", this->get_memory());
      ESP_LOGCONFIG(TAG, "    Address: 0x%02X", this->get_address());
    }

  } // namespace extraflame
} // namespace esphome
