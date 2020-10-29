#ifndef __CHIP8_DISPLAY_H__
#define __CHIP8_DISPLAY_H__

class Display {
private:
    uint16_t buf[2048];
public:
    Display();

    void clearScreen();
    bool draw(uint8_t x, uint8_t y, uint8_t row, uint8_t spriteLine);
};

#endif
