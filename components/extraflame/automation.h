#pragma once

#include "extraflame.h"
#include "esphome/core/automation.h"

namespace esphome
{
  namespace extraflame
  {
    static const char *TAG = "extraflame.hub";

    static bool is_valid_byte(uint8_t value, std::string name)
    {
      if (value < 0x00 || value > 0xFF)
      {
        ESP_LOGE(TAG, "'%s' value is invalid!! Must be between 0x00 - 0xFF but was 0x%02X", name.c_str(), value);
        return false;
      }

      return true;
    }

    template <typename... Ts>
    class ExtraflameWriteAction : public Action<Ts...>, public Parented<ExtraflameHub>
    {
    public:
      TEMPLATABLE_VALUE(uint8_t, address)
      TEMPLATABLE_VALUE(uint8_t, value)

      void set_memory(const uint8_t memory) { this->memory_ = memory; }

      void play_complex(Ts... x) override
      {
        this->num_running_++;

        uint8_t address = this->address_.value(x...);
        uint8_t value_write = this->value_.value(x...);
        if (!is_valid_byte(address, "address") || !is_valid_byte(value_write, "value"))
        {
          this->stop_complex();
          return;
        }

        auto request = ExtraflameRequest{
            .command = {this->memory_, address},
            .on_response = [this, address, value_write, x...](uint8_t value, bool success) {
              if (!success)
              {
                this->stop_complex();
                return;
              }

              if (value_write == value)
              {
                // values are the same, we don't need an update
                this->play_next_(x...);
              }
              else
              {
                uint8_t write_memory = 0x80 + this->memory_;
                uint8_t checksum = (write_memory + address + value_write) & 0xFF;
                auto write_request = ExtraflameRequest{
                    .command = {write_memory, address, value_write, checksum},
                    .on_response = [this, x...](uint8_t value, bool success) {
                      if (success)
                      {
                        this->play_next_(x...);
                      }
                      else
                      {
                        this->stop_complex();
                      }
                    }};
                this->parent_->add_request(write_request, true);
              }
            }};
        this->parent_->add_request(request, true);
      }

      void play(Ts... x) override { this->play_complex(x...); }

    protected:
      uint8_t memory_{};
    };

#ifdef USE_EXTRAFLAME_DUMP
    template <typename... Ts>
    class ExtraflameDumpAction : public Action<Ts...>, public Parented<ExtraflameHub>
    {
    public:
      TEMPLATABLE_VALUE(uint8_t, start)
      TEMPLATABLE_VALUE(uint8_t, end)

      void set_memory(const uint8_t memory) { this->memory_ = memory; }

      void register_finish_trigger(ExtraflameDumpFinishTrigger *trigger) { this->finish_triggers_.push_back(trigger); }

      void play_complex(Ts... x) override
      {
        this->num_running_++;

        auto start = this->start_.value(x...);
        auto end = this->end_.value(x...);
        if (!is_valid_byte(start, "start") || !is_valid_byte(end, "end"))
        {
          this->stop_complex();
          return;
        }

        this->parent_->start_dumping(this->memory_, start, end, this->finish_triggers_);

        this->play_next_(x...);
      }

      void play(Ts... x) override { this->play_complex(x...); }

    protected:
      uint8_t memory_{};
      std::vector<ExtraflameDumpFinishTrigger *> finish_triggers_;
    };


    template<typename... Ts>
    class ExtraflameIsDumpingCondition : public Condition<Ts...>, public Parented<ExtraflameHub> {
    public:
      bool check(Ts... x) override { return this->parent_->is_dumping(); }
    };

#endif

  } // namespace extraflame
} // namespace esphome
