#include "extraflame.h"
#include "esphome/core/log.h"

namespace esphome {
namespace extraflame {

static const char *TAG = "extraflame.hub";
static const char *CURRENT_REQUEST = "extraflame.hub.request";

void ExtraflameHub::loop() {
  while (this->available() >= 2 && this->ongoing_request_) {
    auto resp = *this->read_array<2>();

    //#ifdef ESPHOME_LOG_LEVEL_VERY_VERBOSE
    ESP_LOGD(TAG, "Read value: 0x%02X 0x%02X", resp[0], resp[1]);
    //#endif

    if (this->request_.command[0] == resp[0] && this->request_.command[1] == resp[1]) {
      ESP_LOGD(TAG, "Response was request echo");
      continue;
    }

    this->cancel_timeout(CURRENT_REQUEST);
    this->ongoing_request_ = false;
    this->request_.on_response(resp);
  }
  process_request_queue_();
}

void ExtraflameHub::process_request_queue_() {
  if (!this->ongoing_request_ && !this->request_queue_.empty()) {
    this->ongoing_request_ = true;
    this->request_ = this->request_queue_.front();
    this->request_queue_.erase(request_queue_.begin());
    this->set_timeout(CURRENT_REQUEST, 1000, [this] {
      if (this->request_.command.size() == 2) {
        ESP_LOGW(TAG, "No response for given command: 0x%02X 0x%02X", this->request_.command[0],
                 this->request_.command[1]);
      } else {
        ESP_LOGW(TAG, "No response for given command: 0x%02X 0x%02X  0x%02X  0x%02X", this->request_.command[0],
                 this->request_.command[1], this->request_.command[2], this->request_.command[3]);
      }
      this->reset_input_buffer();
      this->ongoing_request_ = false;
    });
    ESP_LOGD(TAG, "Sending request: 0x%02X 0x%02X", this->request_.command[0], this->request_.command[1]);
    this->write_array(this->request_.command);
  }
}

void ExtraflameHub::add_request(ExtraflameRequest request) {
  ESP_LOGD(TAG, "Adding request");
  this->request_queue_.push_back(request);
  this->process_request_queue_();
}

void ExtraflameHub::reset_input_buffer() {
  ESP_LOGW(TAG, "Reseting buffer and going on with next request");
  while (this->available() > 0) {
    // to clear the buffer
    this->read();
  }
}

ExtraflameComponent::ExtraflameComponent(std::string memory, uint8_t address) {
  this->memory_ = memory;
  this->address_ = address;
}

uint8_t ExtraflameComponent::get_memory_hex_() {
  if (this->memory_ == "EEPROM") {
    return 0x20;
  }

  return 0x00;
}

void ExtraflameComponent::update() {
  auto request = ExtraflameRequest{.command = {this->get_memory_hex_(), this->address_},
                                   .on_response = [this](std::array<uint8_t, 2> resp) {
                                     uint8_t checksum = resp[0];
                                     uint8_t value = resp[1];

                                     // checksum is calculated by (memory + address + value) & 0xFF

                                     uint8_t checksum_calc = (this->get_memory_hex_() + this->address_ + value) & 0xFF;
                                     if (checksum_calc != checksum) {
                                       ESP_LOGW(TAG, "CRC invalid. Skipping update");
                                       this->hub_->reset_input_buffer();
                                     } else {
                                       this->on_read_response(int(value));
                                     }
                                   }};
  this->hub_->add_request(request);
}

}  // namespace extraflame
}  // namespace esphome
