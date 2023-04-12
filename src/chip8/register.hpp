#ifndef __CHIP8_REGISTERS__
#define __CHIP8_REGISTERS__

#include <array>
#include <cstdint>
#include <stack>

namespace chip8 {
struct Registers {
  std::stack<uint8_t> stack{};

  size_t pc{};
  uint16_t I{};
  uint8_t DT{};
  uint8_t ST{};

  std::array<uint8_t, 16> V{};
};
} // namespace chip8

#endif
