#pragma once

#include "esphome/components/sensor/sensor.h"
#include "../extraflame.h"

namespace esphome
{
  namespace extraflame
  {

    class ExtraflameSensor : public ExtraflameComponent, public sensor::Sensor
    {
    public:
      explicit ExtraflameSensor(uint8_t memory, uint8_t address) : ExtraflameComponent(memory, address) {}

      float get_setup_priority() const override { return setup_priority::LATE; }

      void on_read_response(uint8_t value) override;

    protected:
      void dump_config_internal_() override;
    };

  } // namespace extraflame
} // namespace esphome
