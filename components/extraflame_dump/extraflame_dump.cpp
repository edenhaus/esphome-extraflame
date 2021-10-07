#include "extraflame_dump.h"
#include "esphome/core/log.h"

namespace esphome {
namespace extraflame {

static const char *TAG = "extraflame.dump";


void ExtraflameDump::setup() {
  // Declare a service "dump_memory"
  //  - Service will be called "esphome.<NODE_NAME>_dump_memory" in Home Assistant.
  //  - The service has one arguments (type inferred from method definition):
  //     - memory: string
  //     - start: int (0-255) start<=end
  //     - end: int (0-255)
  //  - The function start_washer_cycle declared below will attached to the service.
  register_service(&ExtraflameDump::on_dump_memory_, "dump_memory", {"memory", "start", "end"});
}

void ExtraflameDump::dump_config() {
  ESP_LOGCONFIG(TAG, "ExtraflameDump:");
}


void ExtraflameDump::on_dump_memory_(std::string memory, int start, int end) {
  ESP_LOGD(TAG, "Starting to dump all config values of %s", memory.c_str());

  if (start < 0 || start > 255){
    ESP_LOGE(TAG, "'start' value is invalid!! Must be between 0 - 255 but was %d", start);
  } else if (end < 0 || end > 255){
    ESP_LOGE(TAG, "'end' value is invalid!! Must be between 0 - 255 but was %d", end);
  } else if (start > end){
    ESP_LOGE(TAG, "'start' must be lower or equal to 'end'");
  } else {
    this->dump_address_(memory2hex(memory), (uint8_t) start, (uint8_t) end);
  }
}

void ExtraflameDump::dump_address_(uint8_t memory, uint8_t address, uint8_t address_max) {
  auto request = ExtraflameRequest{
      .command = {memory, address}, .on_response = [this, memory, address, address_max](int value, bool success) {
        ESP_LOGI(TAG, "0x%02X; 0x%02X; 0x%02X; %d", memory, address, (uint8_t) value, value);

        if (address != address_max) {
          this->dump_address_(memory, address + 1, address_max);
        }
      }};
  this->parent_->add_request(request, false);
}


}  // namespace extraflame
}  // namespace esphome