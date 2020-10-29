#ifndef __CHIP8_PROCESSOR_H__
#define __CHIP8_PROCESSOR_H__

#include <cstdint>
#include <memory>


class Memory;

namespace Device {
    class Display;
    class Keyboard;
}

namespace Chip8 {
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
        std::shared_ptr<Device::Display> display;
        std::shared_ptr<Device::Keyboard> keyboard;

        bool step();
        uint16_t fetch();
        bool execute(uint16_t opcode);

    public:
        Registers regs;

        Processor();
        void start();

        Memory &getMemory();
        Device::Display &getDisplay();
        Device::Keyboard &getKeyboard();
    };
} // namespace Chip8

#endif
