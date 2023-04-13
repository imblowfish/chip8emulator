#ifndef __CHIP8_COMPONENT__
#define __CHIP8_COMPONENT__

#include <array>
#include <cstddef>
#include <cstdint>

namespace {
struct Screen {
  const size_t width;
  const size_t height;

  constexpr size_t size() const {
    return width * height;
  }
};
} // namespace

namespace chip8 {
inline constexpr Screen screen{64, 32};

using Ram = std::array<uint8_t, 0x1000>;
using Display = std::array<bool, screen.size()>;
using Keyboard = std::array<bool, 16>;
} // namespace chip8

#endif
