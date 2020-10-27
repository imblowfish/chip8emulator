#ifndef __CHIP8_CONTEXT_H__
#define __CHIP8_CONTEXT_H__

class Context {
public:
    uint16_t opcode;
    uint16_t addr;
    uint8_t nibble;
    uint8_t x;
    uint8_t y;
    uint8_t kk;
    uint8_t head;

    Context(const uint16_t opcode);
    void print();      
};

#endif
