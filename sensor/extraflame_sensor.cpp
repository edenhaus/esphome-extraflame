#include "esphome/core/log.h"
#include "extraflame_sensor.h"

namespace esphome {
namespace extraflame {

static const char *TAG = "extraflame.sensor";

void ExtraflameSensor::on_read_response(int value) {
  ESP_LOGD(TAG, "Got value: %d", value);
  this->publish_state(value);
}

/*void ExtraflameSensor::dump_config() {
  LOG_SENSOR("", "Extraflame Sensor", this);
  ESP_LOGCONFIG(TAG, "  Sensor has datapoint ID %u", this->sensor_id_);
}*/

}  // namespace extraflame
}  // namespace esphome
