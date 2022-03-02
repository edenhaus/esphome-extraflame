#pragma once

#include "esphome/components/number/number.h"
#include "../extraflame.h"

namespace esphome
{
    namespace extraflame
    {
        class ExtraflameNumber : public number::Number, public ExtraflameComponent
        {
        public:
            explicit ExtraflameNumber(uint8_t memory, uint8_t address) : ExtraflameComponent(memory, address) {}

            float get_setup_priority() const override { return setup_priority::LATE; }
            void on_read_response(uint8_t value) override;

            using transform_func_t = std::function<optional<float>(uint8_t)>;
            using write_transform_func_t = std::function<optional<uint8_t>(float, uint8_t)>;
            void set_template(transform_func_t &&f) { this->transform_func_ = f; }
            void set_write_template(write_transform_func_t &&f) { this->write_transform_func_ = f; }

        protected:
            void dump_config_internal_() override;
            void control(float value) override;

            optional<transform_func_t> transform_func_;
            optional<write_transform_func_t> write_transform_func_;
        };

    } // namespace extraflame
} // namespace esphome
