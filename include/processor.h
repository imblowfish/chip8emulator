#ifndef __CHIP8_PROCESSOR_H__
#define __CHIP8_PROCESSOR_H__

#include "timer.h"
#include "display.h"

class Processor {
private:
    const size_t START_PROGRAM_ADDRESS;
    const int FREQUENCY;
    Timer timer;
    Display display;
    size_t pc;
    uint8_t memory[4096];
    uint8_t V[16];
    uint16_t I;
    uint16_t stack[16];
    void loadSprites();
public:

    Processor();
    ~Processor();

    int loadProgram(uint8_t *program, size_t size);
    void start();
    void step();
    void end();
};

#endif
