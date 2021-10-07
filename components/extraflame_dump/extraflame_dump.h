#pragma once

#include "esphome/core/component.h"
#include "esphome/core/defines.h"
#include "esphome/core/helpers.h"
#include "esphome/components/api/custom_api_device.h"

namespace esphome {
namespace extraflame {


class ExtraflameDump :
                      public api::CustomAPIDevice,
                      public Parented<ExtraflameHub>
{
 public:

  void setup() override;

  void dump_config() override;

 protected:

  void on_dump_memory_(std::string memory, int start, int end);
  void dump_address_(uint8_t memory, uint8_t address, uint8_t address_max);

};

}  // namespace extraflame
}  // namespace esphome
