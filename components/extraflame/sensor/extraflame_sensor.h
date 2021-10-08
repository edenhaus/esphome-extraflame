#pragma once

#include "esphome/components/sensor/sensor.h"
#include "esphome/components/extraflame/extraflame.h"
#include "esphome/components/extraflame/util.h"

namespace esphome {
namespace extraflame {

class ExtraflameSensor : public ExtraflameComponent, public sensor::Sensor {
 public:
  explicit ExtraflameSensor(std::string memory_str, uint8_t address) : ExtraflameComponent(memory2hex(memory_str), address) {}

  float get_setup_priority() const override { return setup_priority::LATE; }

  void on_read_response(int value) override;

 protected:
  void dump_config_internal_() override;
};

}  // namespace extraflame
}  // namespace esphome
