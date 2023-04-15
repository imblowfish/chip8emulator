#ifndef __CHIP8_REGISTER__
#define __CHIP8_REGISTER__

#include <array>
#include <cstdint>
#include <stack>

namespace chip8 {
struct Registers {
  std::stack<uint16_t> stack{};

  size_t pc{};
  uint16_t I{};
  uint8_t DT{};
  uint8_t ST{};

  std::array<uint8_t, 16> V{};
};
} // namespace chip8

#endif
