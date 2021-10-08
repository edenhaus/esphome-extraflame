#pragma once

#include "esphome/core/automation.h"
#include "extraflame.h"

namespace esphome {
namespace extraflame {

  static uint8_t memory2hex(std::string memory) {
  if (memory == "EEPROM") {
    return 0x20;
  }

  return 0x00;
}

template<typename... Ts> class ExtraflameWriteAction : public Action<Ts...>, public Parented<ExtraflameHub> {
 public:
  TEMPLATABLE_VALUE(uint8_t, address)
  TEMPLATABLE_VALUE(uint8_t, value)

  void set_memory(const std::string memory) { this->memory_ = memory2hex(memory); }

  void play_complex(Ts... x) override {
    this->num_running_++;

    auto address = this->address_.value(x...);
    auto value_write = this->value_.value(x...);

    auto request = ExtraflameRequest{.command = {this->memory_, address},
                                     .on_response = [this, address, value_write, x...](uint8_t value, bool success) {
                                       if (success) {
                                         if (value_write == value) {
                                           // values are the same, we don't need an update
                                           this->play_next_(x...);
                                         } else {
                                           uint8_t write_memory = 0x80 + this->memory_;
                                           uint8_t checksum = (write_memory + address + value_write) & 0xFF;
                                           auto write_request = ExtraflameRequest{
                                               .command = {write_memory, address, value_write, checksum},
                                               .on_response = [this, x...](uint8_t value, bool success) {
                                                 if (success) {
                                                   this->play_next_(x...);
                                                 } else {
                                                   this->stop_complex();
                                                 }
                                               }};
                                           this->parent_->add_request(write_request, true);
                                         }
                                       } else {
                                         this->stop_complex();
                                       }
                                     }};
    this->parent_->add_request(request, true);
  }

  void play(Ts... x) override { this->play_complex(x...); }

 protected:
  uint8_t memory_{};
};

}  // namespace extraflame
}  // namespace esphome
