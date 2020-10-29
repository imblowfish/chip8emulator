#include <cstdint>
#include <cstring>
#include "device/display.h"

Display::Display() : buf{0} {

}

void Display::clearScreen() {
    memset(buf, 0, sizeof(buf));
}

bool Display::draw(uint8_t x, uint8_t y, uint8_t row, uint8_t spriteLine) {
    (void)x;
    (void)y;
    (void)row;
    (void)spriteLine;
    // TODO: implement draw
    return false;
}