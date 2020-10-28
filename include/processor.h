#ifndef __CHIP8_PROCESSOR_H__
#define __CHIP8_PROCESSOR_H__

#include "timer.h"
#include "display.h"
#include "keyboard.h"
#include "stack.h"

class Processor {
private:
    const size_t START_PROGRAM_ADDRESS;
    const int FREQUENCY;
    //
    Timer timer;
    Display display;
    Keyboard keyboard;
    Stack stack;
    //
    void loadSprites();
public:
    size_t pc;
    uint8_t memory[4096];
    uint8_t V[16];
    uint8_t DT;
    uint8_t ST;
    uint16_t I;

    Processor();
    ~Processor();

    int loadProgram(uint8_t *program, size_t size);
    void start();
    void step();
    void end();
    
    // gets methods
    Timer& getTimer();
    Display& getDisplay();
    Keyboard& getKeyboard();
    Stack& getStack();

    uint16_t getSprite(uint8_t spriteNum);
};

#endif
