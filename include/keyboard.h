#ifndef __CHIP8_KEYBOARD_H__
#define __CHIP8_KEYBOARD_H__

class Keyboard {
private:
    bool keys[16];
public:
    Keyboard();
    bool isPressed(uint8_t key);
    uint8_t waitKey();
};

#endif
