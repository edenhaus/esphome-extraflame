#pragma once

#include "extraflame.h"
#include "esphome/core/automation.h"

namespace esphome {
namespace extraflame {

template<typename... Ts> class ExtraflameWriteAction : public Action<Ts...>, public Parented<ExtraflameHub> {
 public:
  TEMPLATABLE_VALUE(uint16_t, address)
  TEMPLATABLE_VALUE(uint16_t, value)

  void set_memory(const std::string memory) { this->memory_ = memory; }

  void play_complex(Ts... x) override {
    this->num_running_++;

    auto memory_hex = this->parent_->get_memory_hex(this->memory_);
    this->parent_->add_read_request(
        {memory_hex, this->address_},
        [this](std::array<uint8_t> resp) {
          if (this->value_ == resp) {
            // values are the same, we don't need an update
            this->play_next_(x...);
          } else {
            // todo
          }
        },
        [this]() { this->stop_complex(); });
  }

  void play(Ts... x) override {
    auto memory_hex = this->parent_->get_memory_hex(this->memory_);

    if (this->static_) {
      this->parent_->write_array(this->data_static_);
    } else {
      auto val = this->data_func_(x...);
      this->parent_->write_array(val);
    }
  }

 protected:
  std::string memory_{};
};

}  // namespace extraflame
}  // namespace esphome
