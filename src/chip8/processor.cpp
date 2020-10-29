#include <cstdint>
#include <chrono>
#include <cstring>
#include <vector>
#include <iostream>

#include "context.h"

#include "device/display.h"
#include "device/keyboard.h"

#include "chip8_operation/operation_factory.h"

#include "chip8/timer.h"
#include "chip8/memory.h"
#include "chip8/processor.h"

namespace Chip8 {
    Processor::Processor() : FREQUENCY(1.0 / 60.0 * 1000) {
        memset(&regs, 0, sizeof(regs));
        memory.reset(new Memory());
        display.reset(new Device::Display());
        keyboard.reset(new Device::Keyboard());
    }

    void Processor::start() {
        regs.pc = memory->getProgStartAddress();
        Timer timer(FREQUENCY);
        while(true) {
            timer.start();
            if(!step()) {
                break;
            }
            timer.wait();
        }
    }

    bool Processor::step() {
        uint16_t opcode = fetch();
        regs.pc += 2;
        if(!opcode) {
            return false;
        }
        return execute(opcode);
    }

    uint16_t Processor::fetch() {
        return (*memory)[regs.pc] << 8 | (*memory)[regs.pc + 1];
    }

    bool Processor::execute(uint16_t opcode) {
        using namespace Chip8Operation;
        Context ctx(opcode);
        OperationFactory::Operation op = OperationFactory::getOperation(ctx);
        if(!op) {
            return false;
        }
        return op(ctx, *this) == 0;
    }

    Memory &Processor::getMemory() {
        return *memory;
    }

    Device::Display &Processor::getDisplay() {
        return *display;
    }

    Device::Keyboard &Processor::getKeyboard() {
        return *keyboard;
    }
} // namespace Chip8