#ifndef __CHIP8_DISPLAY_H__
#define __CHIP8_DISPLAY_H__

#include <array>
#include <cstdint>

namespace device {
class Display {
private:
  const unsigned int width;
  const unsigned int height;
  std::array<uint16_t, 64 * 32> buf{};

public:
  Display();

  void clearScreen();
  bool draw(uint8_t x, uint8_t y, uint8_t row, uint8_t spriteLine);
  void show();
};
} // namespace device

#endif
