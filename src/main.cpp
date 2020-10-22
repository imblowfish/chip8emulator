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

class Operations {
private:
    Operations() = delete;
    Operations(const Operations&) = delete;
    ~Operations() = delete;
public:
    #define OP_PARAMS Context &ctx
    #define OP_DEF(name, body) static int name (OP_PARAMS) {\
                                   body\
                                   return 0;\
                               }
    
    // 0x0... operations
    OP_DEF(cls, (void)ctx;)
    OP_DEF(ret, (void)ctx;)
    
    // 0x8... operations
    OP_DEF(shl_x_y, (void)ctx;)
    OP_DEF(ld_x_y, (void)ctx;)
    OP_DEF(or_x_y, (void)ctx;)
    OP_DEF(and_x_y, (void)ctx;)
    OP_DEF(xor_x_y, (void)ctx;)
    OP_DEF(add_x_y, (void)ctx;)
    OP_DEF(sub_x_y, (void)ctx;)
    OP_DEF(shr_x_y, (void)ctx;)
    OP_DEF(subn_x_y, (void)ctx;)
    
    // 0xE... operations
    OP_DEF(skp_x, (void)ctx;)
    OP_DEF(sknp_x, (void)ctx;)
    
    // 0xF... operations
    OP_DEF(ld_x_dt, (void)ctx;)
    OP_DEF(ld_x_key, (void)ctx;)
    OP_DEF(ld_dt_x, (void)ctx;)
    OP_DEF(ld_st_x, (void)ctx;)
    OP_DEF(add_I_x, (void)ctx;)
    OP_DEF(ld_F_x, (void)ctx;)
    OP_DEF(ld_BCD_x, (void)ctx;)
    OP_DEF(ld_Iaddr_x, (void)ctx;)
    OP_DEF(ld_x_Iaddr, (void)ctx;)

    // another operations
    OP_DEF(jp_to_addr, (void)ctx;)
    OP_DEF(call_addr, (void)ctx;)
    OP_DEF(se_x_kk, (void)ctx;)
    OP_DEF(sne_x_kk, (void)ctx;)
    OP_DEF(se_x_y, (void)ctx;)
    OP_DEF(ld_x_kk, (void)ctx;)
    OP_DEF(add_x_kk, (void)ctx;)
    OP_DEF(sne_x_y, (void)ctx;)
    OP_DEF(ld_I_addr, (void)ctx;)
    OP_DEF(jp_v0_addr, (void)ctx;)
    OP_DEF(rnd_x_kk, (void)ctx;)
    OP_DEF(drw_x_y_nibble, (void)ctx;)
};

int main() {
    std::cout<<"Hello chip8"<<std::endl;
    return 0;
}