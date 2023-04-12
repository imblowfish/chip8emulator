#ifndef __CHIP8_PROCESSOR_H__
#define __CHIP8_PROCESSOR_H__

namespace chip8 {
class Chip8 {
private:
  const size_t programStartAddress{0x200};

  Ram       ram{};
  Display   display{};
  Keyboard  keyboard{};
  Registers regs{
    .pc = programStartAddress,
  };

public:
  Chip8(std::filesystem::path romPath);
  void start();
};
} // namespace chip8

#endif
