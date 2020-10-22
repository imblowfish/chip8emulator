#include <iostream>

class Context {
public:
    uint16_t opcode;
    uint16_t addr;
    uint8_t nibble;
    uint8_t x;
    uint8_t y;
    uint8_t kk;
    uint8_t head;

    Context(const uint16_t _opcode) {
        opcode = _opcode;
        head = (opcode & 0xF000) >> 12;
        x = (opcode & 0x0F00) >> 8;
        y = (opcode & 0x00F0) >> 4;
        nibble = opcode & 0x000F;
        kk = opcode & 0x00FF;
        addr = opcode & 0x0FFF;
    }

    void print() {
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
};

int main() {
    std::cout<<"Hello chip8"<<std::endl;
    return 0;
}