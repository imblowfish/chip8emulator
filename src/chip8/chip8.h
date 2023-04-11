#ifndef __CHIP8_PROCESSOR_H__
#define __CHIP8_PROCESSOR_H__

namespace device {
class Display;
class Keyboard;
} // namespace device

namespace chip8 {
class Memory;

class Chip8 {
private:
  std::chrono::milliseconds frequency{60}; // Hz
  std::chrono::milliseconds period{1000 / 60};

  struct Registers {
    size_t   pc{};
    uint8_t  DT{};
    uint8_t  ST{};
    uint16_t I{};
    uint8_t  V[16];
  };

  bool     step();
  uint16_t fetch();
  bool     execute(uint16_t opcode);

public:
  Registers regs;

  std::shared_ptr<Memory>           memory;
  std::shared_ptr<device::Display>  display;
  std::shared_ptr<device::Keyboard> keyboard;

  Chip8(std::filesystem::path romPath);
  void start();
};
} // namespace chip8

#endif
