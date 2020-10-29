#ifndef __CHIP8_PROCESSOR_H__
#define __CHIP8_PROCESSOR_H__

#include <cstdint>
#include <memory>

class Memory;
class Display;
class Keyboard;

class Processor {
private:
    const int FREQUENCY;

    struct Registers {
        size_t pc;
        uint8_t DT;
        uint8_t ST;
        uint16_t I;
        uint8_t V[16];
    };

    std::shared_ptr<Memory> memory;
    std::shared_ptr<Display> display;
    std::shared_ptr<Keyboard> keyboard;
public:
    Registers regs;

    Processor();

    void start();
    bool step();

    uint16_t fetch();
    bool execute(uint16_t opcode);

    Memory& getMemory();
    Display& getDisplay();
    Keyboard& getKeyboard();
};

#endif
