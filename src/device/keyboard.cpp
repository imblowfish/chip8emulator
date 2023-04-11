#include <cstdint>
#include "device/keyboard.h"

namespace device {
Keyboard::Keyboard() : keys{0} {}

bool Keyboard::isPressed(uint8_t key) { return keys[key]; }

uint8_t Keyboard::waitKey() {
  // TODO
  return 0;
}
} // namespace device
