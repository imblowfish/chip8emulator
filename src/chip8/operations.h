#ifndef __CHIP8_OPERATIONS__
#define __CHIP8_OPERATIONS__

namespace chip8 {
struct OperationContext {
  Ram       &ram;
  Display   &display;
  Keyboard  &keyboard;
  Registers &regs;

  const uint16_t addr;   // 0x0NNN
  const uint8_t  byte;   // 0x00NN
  const uint8_t  nibble; // 0x000N
  const uint8_t  x;      // 4 bit register identifier
  const uint8_t  y;      // 4 bit register identifier
};

std::function<void(OperationContext &)> decode(uint16_t opcode);
} // namespace chip8

#endif
