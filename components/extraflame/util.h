static uint8_t memory2hex(std::string memory) {
  if (memory == "EEPROM") {
    return 0x20;
  }

  return 0x00;
}