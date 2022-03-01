#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/defines.h"
#include "esphome/core/helpers.h"
#ifdef USE_EXTRAFLAME_DUMP
#include "esphome/core/automation.h"
#endif

namespace esphome
{
  namespace extraflame
  {
    struct ExtraflameRequest
    {
      std::vector<uint8_t> command;
      std::function<void(uint8_t, bool)> on_response;
    };

#ifdef USE_EXTRAFLAME_DUMP
    struct Dump
    {
      uint8_t memory;
      uint8_t current;
      uint8_t end;
      std::string data;
    };

    class ExtraflameDumpFinishTrigger;
#endif

    class ExtraflameComponent;

    class ExtraflameHub : public Component,
                          public uart::UARTDevice
    {
    public:
      float get_setup_priority() const override { return setup_priority::LATE; }

#ifdef USE_EXTRAFLAME_DUMP
      void start_dumping(uint8_t memory, uint8_t start, uint8_t end, const std::vector<ExtraflameDumpFinishTrigger *> &finish_triggers);
      
      bool is_dumping();
#endif

      void dump_config() override;

      void loop() override;

      void add_request(ExtraflameRequest request, bool priority);

      void add_request(std::vector<uint8_t> command);

      void reset_input_buffer();

      void add_component(ExtraflameComponent *component);

    protected:
      enum StatusRequest
      {
        NO_REQUEST,
        REQUEST_SEND,
        REQUEST_ECHO,
        REQUEST_ECHO_PART2
      };

      void next_request_();
      void send_request_(ExtraflameRequest request);
      void notify_components_(uint8_t memory_hex, uint8_t address, int value);
      bool is_request_echo_(std::array<uint8_t, 2> response, int request_part_num);

#ifdef USE_EXTRAFLAME_DUMP
      Dump dump_{.memory = 0x00, .current = 0xFF, .end = 0x0, .data = std::string("")};
      std::vector<ExtraflameDumpFinishTrigger *> finish_triggers_;
#endif

      std::vector<ExtraflameRequest> request_queue_;
      ExtraflameRequest request_;
      StatusRequest status_{NO_REQUEST};
      std::vector<ExtraflameComponent *> components_{};
    };

    class ExtraflameComponent : public PollingComponent, public Parented<ExtraflameHub>
    {
    public:
      explicit ExtraflameComponent(uint8_t memory, uint8_t address);

      uint8_t get_memory() const { return this->memory_; }
      uint8_t get_address() const { return this->address_; }

      void setup() override;

      void update() override;

      void dump_config_internal();

      virtual void on_read_response(int value) = 0;

    protected:
      virtual void dump_config_internal_() = 0;

      std::vector<uint8_t> command_;
      uint8_t memory_;
      uint8_t address_;
    };

#ifdef USE_EXTRAFLAME_DUMP
    class ExtraflameDumpFinishTrigger : public Trigger<std::string>
    {
    public:
      void process(std::string value) { this->trigger(value); }
    };
#endif

  } // namespace extraflame
} // namespace esphome
