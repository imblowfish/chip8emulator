#ifndef __CHIP8_TYPES__
#define __CHIP8_TYPES__

namespace chip8 {
static inline constexpr size_t screenWidth{64};
static inline constexpr size_t screenHeight{32};

using Ram      = std::array<uint8_t, 0x1000>;
using Display  = std::array<bool, screenWidth * screenHeight>;
using Keyboard = std::array<bool, 16>;

struct Registers {
  std::stack<uint8_t> stack{};

  size_t   pc{};
  uint16_t I{};
  uint8_t  DT{};
  uint8_t  ST{};

  std::array<uint8_t, 16> V{};
};
} // namespace chip8

#endif
