#include "esphome/core/log.h"
#include "extraflame_sensor.h"

namespace esphome {
namespace extraflame {

static const char *TAG = "extraflame.sensor";

void ExtraflameSensor::on_read_response(int value) {
  ESP_LOGD(TAG, "Got value: %d", value);
  this->publish_state(value);
}

void ExtraflameSensor::dump_config_internal_() { LOG_SENSOR("  ", "Sensor", this); }

}  // namespace extraflame
}  // namespace esphome
