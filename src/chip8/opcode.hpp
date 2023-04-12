#ifndef __CHIP8_OPERATIONS__
#define __CHIP8_OPERATIONS__

#include <functional>
#include <optional>
#include "chip8/component.hpp"
#include "chip8/register.hpp"

namespace chip8 {
namespace opcode {
struct Opcode {
  const uint16_t value; // 0xVVVV
  const uint16_t head;  // 0xH000
  const uint16_t addr;  // 0x0NNN
  const uint8_t byte;   // 0x00NN
  const uint8_t nibble; // 0x000N
  const uint8_t x;      // 0x0X00
  const uint8_t y;      // 0x00Y0

  Opcode(uint16_t opcode);

  Opcode(Opcode &&) noexcept = default;
};

struct Context {
  Ram ram;
  Display display;
  Keyboard keyboard;
  Registers regs;
};

using Operation = std::optional<std::function<void(Opcode &&, Context &)>>;

Operation decode(const Opcode &opcode);
} // namespace opcode
} // namespace chip8

#endif
