#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/defines.h"
#ifdef USE_EXTRAFLAME_DUMP
#include "esphome/components/api/custom_api_device.h"
#endif

namespace esphome {
namespace extraflame {

struct ExtraflameRequest {
  std::vector<uint8_t> command;
  std::function<void(std::array<uint8_t, 2>)> on_response;
};

class ExtraflameHub : public Component,
                      public uart::UARTDevice
#ifdef USE_EXTRAFLAME_DUMP
    ,
                      public api::CustomAPIDevice
#endif
{
 public:
  float get_setup_priority() const override { return setup_priority::LATE; }

#ifdef USE_EXTRAFLAME_DUMP
  void setup() override;
#endif

  // void dump_config() override; todo

  void loop() override;

  void add_request(ExtraflameRequest request);

  void add_read_request(std::vector<uint8_t> command, std::function<void(uint8_t)> on_response,
                        std::function<void()> on_error);

  void reset_input_buffer();

  uint8_t get_memory_hex(std::string memory);

 protected:
  void process_request_queue_();

#ifdef USE_EXTRAFLAME_DUMP
  void on_dump_memory_(std::string memory);
  void dump_address_(uint8_t memory, uint8_t address);
#endif

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
  virtual void on_read_response(int value) = 0;

  ExtraflameHub *hub_;
  std::vector<uint8_t> command_;
  std::string memory_;
  uint8_t memory_hex_;
  uint8_t address_;
};

}  // namespace extraflame
}  // namespace esphome
