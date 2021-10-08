#include "extraflame_dump.h"
#include "esphome/core/log.h"
#include "esphome/components/extraflame/util.h"
#include <sstream>


namespace esphome {
namespace extraflame {

static const char *TAG = "extraflame.dump";

void ExtraflameDump::setup() {
  ExtraflameComponent::setup();

  // Declare a service "dump_memory"
  //  - Service will be called "esphome.<NODE_NAME>_dump_memory" in Home Assistant.
  //  - The service has one arguments (type inferred from method definition):
  //     - memory: string
  //     - start: int (0-255) start<=end
  //     - end: int (0-255)
  //  - The function start_washer_cycle declared below will attached to the service.
  register_service(&ExtraflameDump::on_dump_memory_, "dump_memory", {"memory", "start", "end"});
}

void ExtraflameDump::update(){
  // do nothing only overriding the super method
}

void ExtraflameDump::dump_config() {
  ESP_LOGCONFIG(TAG, "ExtraflameDump:");
}

void ExtraflameDump::on_read_response(int value) {
  ESP_LOGD(TAG, "Got value for %d: %d", (int)this->address_, value);

  std::stringstream ss;
  ss << "\"" << (int)this->address_ << "\":" << value;

  auto new_address = this->get_address()+1;

  if (new_address > this->address_max_){
    ss << "}";
    this->dump_.append(ss.str());

    ESP_LOGI(TAG, "Performing http request");
    ESP_LOGD(TAG, "Dump=%s", this->dump_.c_str());
  }
  else {
    ss << ",";
    this->dump_.append(ss.str());
    this->dump_address_(new_address);
  }
}


void ExtraflameDump::on_dump_memory_(std::string memory, int start, int end) {
  ESP_LOGD(TAG, "Starting to dump config values of %s (%d - %d)", memory.c_str(), start, end);

  if (start < 0 || start > 255){
    ESP_LOGE(TAG, "'start' value is invalid!! Must be between 0 - 255 but was %d", start);
  } else if (end < 0 || end > 255){
    ESP_LOGE(TAG, "'end' value is invalid!! Must be between 0 - 255 but was %d", end);
  } else if (start > end){
    ESP_LOGE(TAG, "'start' must be lower or equal to 'end'");
  } else {
    this->dump_ = "{";

    this->address_max_ = (uint8_t) end;

    this->memory_ = memory2hex(memory);
    this->dump_address_((uint8_t) start);
  }
}

void ExtraflameDump::dump_address_(uint8_t address){
    this->address_ = address;
    auto request = ExtraflameRequest{
      .command = {this->get_memory(), address}
    };
    this->parent_->add_request(request, false);
}

void ExtraflameDump::dump_config_internal_() { }


}  // namespace extraflame
}  // namespace esphome
