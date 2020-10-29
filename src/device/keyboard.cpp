#include <cstdint>

#include "device/keyboard.h"

namespace Device {
    Keyboard::Keyboard() : keys{0} {
    }

    bool Keyboard::isPressed(uint8_t key) {
        return keys[key];
    }

    uint8_t Keyboard::waitKey() {
        // TODO: add wait key here
        return 0;
    }
} // namespace Device