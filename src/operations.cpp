#include <cstdint>
#include <cstdlib>

#include "context.h"
#include "processor.h"
#include "operations.h"

// 0x0... operations
int Operations::cls(OP_PARAMS) {
    proc.getDisplay().clearScreen();
    return 0;
}

int Operations::ret(OP_PARAMS) {
    // TODO: Uncomment this for test
    // proc.pc = proc.getStack().pop();
    return 0;
}

// 0x8... operations
int Operations::ld_x_y(OP_PARAMS) {
    proc.V[ctx.x] = proc.V[ctx.y];
    return 0;
}

int Operations::or_x_y(OP_PARAMS) {
    proc.V[ctx.x] |= proc.V[ctx.y];
    return 0;
}

int Operations::and_x_y(OP_PARAMS) {
    proc.V[ctx.x] &= proc.V[ctx.y];
    return 0;
}

int Operations::xor_x_y(OP_PARAMS) {
    proc.V[ctx.x] ^= proc.V[ctx.y];
    return 0;
}

int Operations::add_x_y(OP_PARAMS) {
    uint16_t sum = proc.V[ctx.x] + proc.V[ctx.y];
    proc.V[ctx.x] = sum;
    proc.V[0xF] = sum > 255;
    return 0;
}

int Operations::sub_x_y(OP_PARAMS) {
    proc.V[0xF] = proc.V[ctx.x] > proc.V[ctx.y];
    proc.V[ctx.x] -= proc.V[ctx.y];
    return 0;
}

int Operations::shr_x_y(OP_PARAMS) {
    proc.V[ctx.x] >>= ctx.y;
    proc.V[0xF] = proc.V[ctx.x] & 0x1;
    return 0;
}

int Operations::shl_x_y(OP_PARAMS) {
    proc.V[ctx.x] <<= ctx.y;
    proc.V[0xF] = proc.V[ctx.x] & 0x80; 
    return 0;
}

int Operations::subn_x_y(OP_PARAMS) {
    proc.V[0xF] = proc.V[ctx.y] > proc.V[ctx.x];
    proc.V[ctx.x] = proc.V[ctx.y] - proc.V[ctx.x];
    return 0;
}

// 0xE... operations
int Operations::skp_x(OP_PARAMS) {
    if(proc.getKeyboard().isPressed(proc.V[ctx.x])) {
        proc.pc +=2;
    }
    return 0;
}

int Operations::sknp_x(OP_PARAMS) {
    if(!proc.getKeyboard().isPressed(proc.V[ctx.x])) {
        proc.pc += 2;
    }
    return 0;
}

// 0xF... operations
int Operations::ld_x_dt(OP_PARAMS) {
    proc.V[ctx.x] = proc.DT;
    return 0;
}

int Operations::ld_x_key(OP_PARAMS) {
    proc.V[ctx.x] = proc.getKeyboard().waitKey();
    return 0;
}

int Operations::ld_dt_x(OP_PARAMS) {
    proc.DT = proc.V[ctx.x];
    return 0;
}

int Operations::ld_st_x(OP_PARAMS) {
    proc.ST = proc.V[ctx.x];
    return 0;
}

int Operations::add_I_x(OP_PARAMS) {
    proc.I += proc.V[ctx.x];
    return 0;
}

int Operations::ld_F_x(OP_PARAMS) {
    proc.I = proc.getSprite(proc.V[ctx.x]);
    return 0;
}

int Operations::ld_BCD_x(OP_PARAMS) {
    uint8_t num = proc.V[ctx.x];
    for(uint8_t i=0, divider = 10; i < 3; i++, divider *= 10) {
        proc.memory[proc.I + i] = num % divider / (divider / 10); 
    }
    return 0;
}

int Operations::ld_Iaddr_x(OP_PARAMS) {
    for(unsigned int i=0; i < proc.V[ctx.x]; i++) {
        proc.memory[proc.I + i] = proc.V[i];
    }
    return 0;
}

int Operations::ld_x_Iaddr(OP_PARAMS) {
    for(unsigned int i=0; i < proc.V[ctx.x]; i++) {
        proc.V[i] = proc.memory[proc.I + i];
    }
    return 0;
}

// another operations
int Operations::jp_to_addr(OP_PARAMS) {
    proc.pc = ctx.addr;
    return 0;
}

int Operations::call_addr(OP_PARAMS) {
    proc.getStack().push(proc.pc);
    proc.pc = ctx.addr;
    return 0;
}

int Operations::se_x_kk(OP_PARAMS) {
    if(proc.V[ctx.x] == ctx.kk) {
        proc.pc += 2;
    }
    return 0;
}

int Operations::sne_x_kk(OP_PARAMS) {
    if(proc.V[ctx.x] != ctx.kk) {
        proc.pc += 2;
    }
    return 0;
}

int Operations::se_x_y(OP_PARAMS) {
    if(proc.V[ctx.x] == proc.V[ctx.y]) {
        proc.pc += 2;
    }
    return 0;
}

int Operations::ld_x_kk(OP_PARAMS) {
    proc.V[ctx.x] = ctx.kk;
    return 0;
}

int Operations::add_x_kk(OP_PARAMS) {
    proc.V[ctx.x] += ctx.kk;
    return 0;
}

int Operations::sne_x_y(OP_PARAMS) {
    if(proc.V[ctx.x] != proc.V[ctx.y]) {
        proc.pc += 2;
    }
    return 0;
}

int Operations::ld_I_addr(OP_PARAMS) {
    proc.I = ctx.addr;
    return 0;
}

int Operations::jp_v0_addr(OP_PARAMS) {
    proc.pc = ctx.addr + proc.V[0];
    return 0;
}

int Operations::rnd_x_kk(OP_PARAMS) {
    proc.V[ctx.x] = (rand() % 256) & ctx.kk;
    return 0;
}

int Operations::drw_x_y_nibble(OP_PARAMS) {
    // draw sprite, stored from I to I + nibble
    // and draw it in Vx Vy position
    for(unsigned int i=0; i < ctx.nibble; i++) {
        uint8_t byte = proc.memory[proc.I + i];
        bool wasErased = proc.getDisplay().draw(proc.V[ctx.x], proc.V[ctx.y], i, byte);
        if(!proc.V[0xF] && wasErased) {
            proc.V[0xF] = 1;
        }
    }
    return 0;
}



