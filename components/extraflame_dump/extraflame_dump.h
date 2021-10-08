#pragma once

#include "esphome/core/component.h"
#include "esphome/core/defines.h"
#include "esphome/core/helpers.h"
#include "esphome/components/api/custom_api_device.h"
//#include "esphome/components/http_request/http_request.h"
#include "../extraflame/extraflame.h"
#include <sstream>

namespace esphome {
namespace extraflame {


class ExtraflameDump :
                      public Component,
                      public api::CustomAPIDevice,
                      public Parented<ExtraflameHub>
{
 public:
  /*ExtraflameDump(http_request::HttpRequestComponent *http_request) {
    this->http_request_ = http_request;
  }*/

  void setup() override;

  void dump_config() override;

 protected:

  void on_dump_memory_(std::string memory, int start, int end);
  void dump_address_(uint8_t memory, uint8_t address, uint8_t address_max);

  //http_request::HttpRequestComponent *http_request_;
  std::stringstream dump_;
};

}  // namespace extraflame
}  // namespace esphome
