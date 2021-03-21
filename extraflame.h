#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace extraflame {

struct ExtraflameRequest {
  std::vector<uint8_t> command;
  std::function<void(std::array<uint8_t, 2>)> on_response;
};

class ExtraflameHub : public Component, public uart::UARTDevice {
 public:
  float get_setup_priority() const override { return setup_priority::LATE; }

  // void dump_config() override; todo

  void loop() override;

  void add_request(ExtraflameRequest request);

  void reset_input_buffer();

 protected:
  void process_request_queue_();

  std::vector<ExtraflameRequest> request_queue_;
  ExtraflameRequest request_;
  bool ongoing_request_ = false;
};

class ExtraflameComponent : public PollingComponent {
 public:
  explicit ExtraflameComponent(std::string memory, uint8_t address);

  std::string get_memory() const { return this->memory_; }
  uint8_t get_memory_hex() const { return this->memory_hex_; }
  uint8_t get_address() const { return this->address_; }

  void set_extraflame_hub(ExtraflameHub *hub) { this->hub_ = hub; }
  void update() override;

 protected:
  uint8_t get_memory_hex_();
  virtual void on_read_response(int value) = 0;

  ExtraflameHub *hub_;
  std::vector<uint8_t> command_;
  std::string memory_;
  uint8_t memory_hex_;
  uint8_t address_;
};

}  // namespace extraflame
}  // namespace esphome
