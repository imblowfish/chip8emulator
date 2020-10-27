#include <cstdint>
#include <cstdio>

#include "context.h"

Context::Context(const uint16_t opcode) : opcode(opcode) {
    head = (opcode & 0xF000) >> 12;
    x = (opcode & 0x0F00) >> 8;
    y = (opcode & 0x00F0) >> 4;
    nibble = opcode & 0x000F;
    kk = opcode & 0x00FF;
    addr = opcode & 0x0FFF;
}

void Context::print() {
    printf( "==============\n"
                "   Context:   \n"
                "==============\n"
                "opcode: 0x%04X\n"
                "nibble: 0x%04X\n"
                "x:      0x%04X\n"
                "y:      0x%04X\n"
                "kk:     0x%04X\n"
                "head:   0x%04X\n"
                "==============\n", 
                opcode, nibble, 
                x, y, kk, head );
}
