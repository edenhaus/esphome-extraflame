#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/defines.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace extraflame {

struct ExtraflameRequest {
  std::vector<uint8_t> command;
  std::function<void(uint8_t, bool)> on_response;
};



class ExtraflameComponent;

class ExtraflameHub : public Component,
                      public uart::UARTDevice
{
 public:
  float get_setup_priority() const override { return setup_priority::LATE; }

  void dump_config() override;

  void loop() override;

  void add_request(ExtraflameRequest request, bool priority);

  void add_request(std::vector<uint8_t> command);

  void reset_input_buffer();

  void add_component(ExtraflameComponent *component);

 protected:
  enum StatusRequest { NO_REQUEST, REQUEST_SEND, REQUEST_ECHO, REQUEST_ECHO_PART2 };

  void process_request_queue_();
  void notify_components_(uint8_t memory_hex, uint8_t address, int value);
  bool is_request_echo_(std::array<uint8_t, 2> response, int request_part_num);

  std::vector<ExtraflameRequest> request_queue_;
  ExtraflameRequest request_;
  StatusRequest status_{NO_REQUEST};
  std::vector<ExtraflameComponent *> components_{};
};

class ExtraflameComponent : public PollingComponent, public Parented<ExtraflameHub> {
 public:
  explicit ExtraflameComponent(uint8_t memory, uint8_t address){
    this->memory_ = memory;
    this->address_ = address;
  }

  uint8_t get_address() const { return this->address_; }
  uint8_t get_memory() const { return this->memory_; }

  void setup() override;

  void update() override;

  void dump_config_internal();

  virtual void on_read_response(int value) = 0;

 protected:
  virtual void dump_config_internal_() = 0;

  std::vector<uint8_t> command_;
  uint8_t address_;
  uint8_t memory_;
};

}  // namespace extraflame
}  // namespace esphome
