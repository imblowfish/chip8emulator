#include <cstdint>
#include <cstdlib>
#include <vector>

#include "context.h"

#include "device/display.h"
#include "device/keyboard.h"

#include "chip8/memory.h"
#include "chip8/processor.h"

#include "chip8_operation/operations.h"

namespace Chip8Operation {
    // 0x0... operations
    int Operations::cls(OP_PARAMS) {
        proc.getDisplay().clearScreen();
        return 0;
    }

    int Operations::ret(OP_PARAMS) {
        size_t &pc = proc.regs.pc;

        pc = proc.getMemory().pop();
        return 0;
    }

    // 0x8... operations
    int Operations::ld_x_y(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        uint8_t &reg2 = proc.regs.V[ctx.y];

        reg1 = reg2;
        return 0;
    }

    int Operations::or_x_y(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        uint8_t &reg2 = proc.regs.V[ctx.y];

        reg1 |= reg2;
        return 0;
    }

    int Operations::and_x_y(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        uint8_t &reg2 = proc.regs.V[ctx.y];

        reg1 &= reg2;
        return 0;
    }

    int Operations::xor_x_y(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        uint8_t &reg2 = proc.regs.V[ctx.y];

        reg1 ^= reg2;
        return 0;
    }

    int Operations::add_x_y(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        uint8_t &reg2 = proc.regs.V[ctx.y];
        uint8_t &regF = proc.regs.V[0xF];

        uint16_t sum = reg1 + reg2;
        reg1 = sum;
        regF = sum > 255;
        return 0;
    }

    int Operations::sub_x_y(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        uint8_t &reg2 = proc.regs.V[ctx.y];
        uint8_t &regF = proc.regs.V[0xF];

        regF = reg1 > reg2;
        reg1 -= reg2;
        return 0;
    }

    int Operations::shr_x_y(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        uint8_t &regF = proc.regs.V[0xF];

        reg1 >>= ctx.y;
        regF = reg1 & 0x1;
        return 0;
    }

    int Operations::shl_x_y(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        uint8_t &regF = proc.regs.V[0xF];

        reg1 <<= ctx.y;
        regF = reg1 & 0x80;
        return 0;
    }

    int Operations::subn_x_y(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        uint8_t &reg2 = proc.regs.V[ctx.y];
        uint8_t &regF = proc.regs.V[0xF];

        regF = reg2 > reg1;
        reg1 = reg2 - reg1;
        return 0;
    }

    // 0xE... operations
    int Operations::skp_x(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        size_t &pc = proc.regs.pc;

        if(proc.getKeyboard().isPressed(reg1)) {
            pc += 2;
        }
        return 0;
    }

    int Operations::sknp_x(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        size_t &pc = proc.regs.pc;

        if(!proc.getKeyboard().isPressed(reg1)) {
            pc += 2;
        }
        return 0;
    }

    // 0xF... operations
    int Operations::ld_x_dt(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        uint8_t &DT = proc.regs.DT;

        reg1 = DT;
        return 0;
    }

    int Operations::ld_x_key(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];

        reg1 = proc.getKeyboard().waitKey();
        return 0;
    }

    int Operations::ld_dt_x(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        uint8_t &DT = proc.regs.DT;

        DT = reg1;
        return 0;
    }

    int Operations::ld_st_x(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        uint8_t &ST = proc.regs.ST;

        ST = reg1;
        return 0;
    }

    int Operations::add_I_x(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        uint16_t &I = proc.regs.I;

        I += reg1;
        return 0;
    }

    int Operations::ld_F_x(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        uint16_t &I = proc.regs.I;

        I = proc.getMemory().getSpriteAddress(reg1);
        return 0;
    }

    int Operations::ld_BCD_x(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        uint16_t &I = proc.regs.I;
        Chip8::Memory &memory = proc.getMemory();

        uint8_t num = reg1;
        for(uint8_t i = 0, divider = 10; i < 3; i++, divider *= 10) {
            memory[I + i] = num % divider / (divider / 10);
        }
        return 0;
    }

    int Operations::ld_Iaddr_x(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        uint16_t &I = proc.regs.I;
        Chip8::Memory &memory = proc.getMemory();

        for(unsigned int i = 0; i < reg1; i++) {
            uint8_t &reg2 = proc.regs.V[i];
            memory[I + i] = reg2;
        }
        return 0;
    }

    int Operations::ld_x_Iaddr(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        uint16_t &I = proc.regs.I;
        Chip8::Memory &memory = proc.getMemory();

        for(unsigned int i = 0; i < reg1; i++) {
            uint8_t &reg2 = proc.regs.V[i];
            reg2 = memory[I + i];
        }
        return 0;
    }

    // another operations
    int Operations::jp_to_addr(OP_PARAMS) {
        size_t &pc = proc.regs.pc;

        pc = ctx.addr;
        return 0;
    }

    int Operations::call_addr(OP_PARAMS) {
        size_t &pc = proc.regs.pc;

        proc.getMemory().push(pc);
        pc = ctx.addr;
        return 0;
    }

    int Operations::se_x_kk(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        size_t &pc = proc.regs.pc;

        if(reg1 == ctx.kk) {
            pc += 2;
        }
        return 0;
    }

    int Operations::sne_x_kk(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        size_t &pc = proc.regs.pc;

        if(reg1 != ctx.kk) {
            pc += 2;
        }
        return 0;
    }

    int Operations::se_x_y(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        uint8_t &reg2 = proc.regs.V[ctx.y];
        size_t &pc = proc.regs.pc;

        if(reg1 == reg2) {
            pc += 2;
        }
        return 0;
    }

    int Operations::ld_x_kk(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];

        reg1 = ctx.kk;
        return 0;
    }

    int Operations::add_x_kk(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];

        reg1 += ctx.kk;
        return 0;
    }

    int Operations::sne_x_y(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];
        uint8_t &reg2 = proc.regs.V[ctx.y];
        size_t &pc = proc.regs.pc;

        if(reg1 != reg2) {
            pc += 2;
        }
        return 0;
    }

    int Operations::ld_I_addr(OP_PARAMS) {
        uint16_t &I = proc.regs.I;

        I = ctx.addr;
        return 0;
    }

    int Operations::jp_v0_addr(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[0];
        size_t &pc = proc.regs.pc;

        pc = ctx.addr + reg1;
        return 0;
    }

    int Operations::rnd_x_kk(OP_PARAMS) {
        uint8_t &reg1 = proc.regs.V[ctx.x];

        reg1 = (rand() % 256) & ctx.kk;
        return 0;
    }

    int Operations::drw_x_y_nibble(OP_PARAMS) {
        // draw sprite, stored from I to I + nibble
        // and draw it in Vx Vy position
        uint8_t &reg1 = proc.regs.V[ctx.x];
        uint8_t &reg2 = proc.regs.V[ctx.y];
        uint8_t &regF = proc.regs.V[0xF];
        uint16_t &I = proc.regs.I;

        Chip8::Memory &memory = proc.getMemory();

        for(unsigned int i = 0; i < ctx.nibble; i++) {
            uint8_t byte = memory[I + i];
            bool wasErased = proc.getDisplay().draw(reg1, reg2, i, byte);
            if(wasErased) {
                regF = 1;
            }
        }
        return 0;
    }
} // namespace Operation
