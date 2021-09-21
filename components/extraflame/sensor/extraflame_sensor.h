#pragma once

#include "esphome/components/extraflame/extraflame.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace extraflame {

class ExtraflameSensor : public ExtraflameComponent, public sensor::Sensor {
 public:
  explicit ExtraflameSensor(std::string memory, uint8_t address) : ExtraflameComponent(memory, address) {}

  float get_setup_priority() const override { return setup_priority::LATE; }

  void on_read_response(int value) override;

 protected:
  void dump_config_internal_() override;
};

}  // namespace extraflame
}  // namespace esphome
