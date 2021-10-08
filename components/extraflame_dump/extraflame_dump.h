#pragma once

#include "esphome/core/component.h"
#include "esphome/core/defines.h"
#include "esphome/core/helpers.h"
#include "esphome/components/api/custom_api_device.h"
//#include "esphome/components/http_request/http_request.h"
#include "../extraflame/extraflame.h"

namespace esphome {
namespace extraflame {


class ExtraflameDump : public ExtraflameComponent,
                       public api::CustomAPIDevice
{
 public:
  // initialize with dummy values
  explicit ExtraflameDump() : ExtraflameComponent(0xFF, 0xFF) {}
  /*ExtraflameDump(http_request::HttpRequestComponent *http_request) {
    this->http_request_ = http_request;
  }*/

  void setup() override;

  void dump_config() override;

  void update() override;

  void on_read_response(int value) override;

 protected:

  void on_dump_memory_(std::string memory, int start, int end);
  void dump_address_(uint8_t address);
  void dump_config_internal_() override;

  //http_request::HttpRequestComponent *http_request_;
  std::string dump_;
  uint8_t address_max_{0xFF};
};

}  // namespace extraflame
}  // namespace esphome
