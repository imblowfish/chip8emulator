#include <cstdint>
#include <cstring>
#include <iostream>

#include "device/display.h"

namespace Device {
    Display::Display() : width(64), height(32), buf{0} {

    }

    void Display::clearScreen() {
        memset(buf, 0, sizeof(buf));
    }

    bool Display::draw(uint8_t x, uint8_t y, uint8_t row, uint8_t spriteLine) {
        (void)x;
        (void)y;
        (void)row;
        (void)spriteLine;
        size_t idx = (y + row) * width + x; 
        for(unsigned int i=0; i < 8; i++) {
            buf[idx + i] ^= spriteLine >> (8 - i - 1) & 0x1;    
        }
        return false;
    }

    void Display::show() {
        std::string screenImage;
        for(unsigned int i=0; i < height; i++) {
            for(unsigned int j=0; j < width; j++) {
                size_t idx = i * width + j;
                screenImage += buf[idx] ? '#' : ' ';
            }
            screenImage += '\n';
        }
        std::cout << screenImage;
    }
} // namespace Device