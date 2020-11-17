#include <cstdint>
#include <conio.h>
#include "device/keyboard.h"

namespace Device {
    Keyboard::Keyboard() : keys{0} {
    }

    bool Keyboard::isPressed(uint8_t key) {
        return keys[key];
    }

    uint8_t Keyboard::waitKey() {
        while(true) {
            char key = getch();
            if((key >= '0' && key <= '9') ||  (key >= 'a' && key <= 'f')) {
                return key;
            }
        }
        return 0;
    }
} // namespace Device