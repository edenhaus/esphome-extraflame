#include "esphome/core/log.h"
#include "extraflame_number.h"

namespace esphome
{
    namespace extraflame
    {
        static const char *const TAG = "extraflame.number";

        void ExtraflameNumber::on_read_response(uint8_t value)
        {
            ESP_LOGD(TAG, "Got value: %d", value);
            // Is there a lambda registered call it with the value
            if (this->transform_func_.has_value())
            {
                // the lambda can parse the response itself
                auto val = (*this->transform_func_)(value);
                if (val.has_value())
                {
                    ESP_LOGD(TAG, "Lambda returned value: %d", val.value());
                    this->publish_state(val.value());
                }
                else
                {
                    ESP_LOGD(TAG, "Lambda returned no value. Ignoring this value.");
                }
            }
            else
            {
                this->publish_state(value);
            }
        }

        void ExtraflameNumber::dump_config_internal_()
        {
            LOG_NUMBER("  ", "Number", this);
        }

        void ExtraflameNumber::control(float value)
        {
            auto request = ExtraflameRequest{
                .command = {this->memory_, this->address_},
                .on_response = [this, value](uint8_t current_value, bool success) {
                    if (!success)
                    {
                        ESP_LOGE("Couldn't get number value");
                        return;
                    }

                    uint8_t value_write = (uint8_t) int(value);
                    if (this->write_transform_func_.has_value())
                    {
                        auto val = (*this->write_transform_func_)(value, current_value);
                        if (!val.has_value())
                        {
                            ESP_LOGD(TAG, "Write lambda returned no value! Don't set new value");
                            // as we do a read first, the actual value is publish by on_read_response
                            return;
                        }

                        value_write = val.value();
                    }

                    ESP_LOGD(TAG, "Writing following value: 0x%02X", value_write);

                    /*if (value_write != value)
                    {
                        // we need to update the value only if they are not the same
                        uint8_t write_memory = 0x80 + this->memory_;
                        uint8_t checksum = (write_memory + this->address_ + value_write) & 0xFF;
                        auto write_request = ExtraflameRequest{
                            .command = {write_memory, this->address_, value_write, checksum},
                            .on_response = [this](uint8_t value, bool success) {
                                if (success)
                                {
                                    this->publish_state(value);
                                }
                                else
                                {
                                    ESP_LOGE("Couldn't update number");
                                }
                            }};
                        this->parent_->add_request(write_request, true);
                    }*/
                }};
            this->parent_->add_request(request, true);
        }
    } // namespace extraflame
} // namespace esphome
