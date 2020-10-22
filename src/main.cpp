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

class OperationFactory {
public:
    #define OP(opname) Operations::opname
    #define CASE_OP(code, opname) case code: return OP(opname)
    using Operation = int (*) (Context &ctx);

    static Operation getOperation(Context &ctx) {
        // parse here
        switch(ctx.opcode) {
            CASE_OP(0x00E0, cls);
            CASE_OP(0x00EE, ret);
        }
        switch(ctx.head) {
            case 0x8: {
                if(ctx.nibble == 0xE) {
                    return OP(shl_x_y);
                }
                Operation ariphmetics[] = {
                    OP(ld_x_y), OP(or_x_y), 
                    OP(and_x_y), OP(xor_x_y),
                    OP(add_x_y), OP(sub_x_y), 
                    OP(shr_x_y), OP(subn_x_y)
                };
                if(ctx.nibble > sizeof(ariphmetics) / sizeof(Operation)) {
                    fprintf(stderr, "Error: Wrong operation opcode 0x%04X", ctx.nibble);
                    return nullptr;
                }
                return ariphmetics[ctx.nibble];
            }
            case 0xE:
                if(ctx.kk == 0x9E) {
                    return OP(skp_x);
                } else if(ctx.kk == 0xA1) {
                    return OP(sknp_x);
                }
                return nullptr;
            case 0xF:
                switch(ctx.kk) {
                    CASE_OP(0x07, ld_x_dt);
                    CASE_OP(0x0A, ld_x_key);
                    CASE_OP(0x15, ld_dt_x);
                    CASE_OP(0x18, ld_st_x);
                    CASE_OP(0x1E, add_I_x);
                    CASE_OP(0x29, ld_F_x);
                    CASE_OP(0x33, ld_BCD_x);
                    CASE_OP(0x55, ld_Iaddr_x);
                    CASE_OP(0x65, ld_x_Iaddr);
                    default:
                        return nullptr;
                }
            CASE_OP(0x1, jp_to_addr);
            CASE_OP(0x2, call_addr);
            CASE_OP(0x3, se_x_kk);
            CASE_OP(0x4, sne_x_kk);
            CASE_OP(0x5, se_x_y);
            CASE_OP(0x6, ld_x_kk);
            CASE_OP(0x7, add_x_kk);
            CASE_OP(0x9, sne_x_y);
            CASE_OP(0xA, ld_I_addr);
            CASE_OP(0xB, jp_v0_addr);
            CASE_OP(0xC, rnd_x_kk);
            CASE_OP(0xD, drw_x_y_nibble);
        }
        return nullptr;
    }
};

class Processor {
private:
    struct Program {
        uint16_t *data;
        size_t size;
    } program;
public:
    Processor() {}
    ~Processor() {}

    int loadProgram(uint16_t *data, size_t size) {
        this->program = {
            data,
            size
        };
        std::cout << "Load program to memory" << std::endl;
        return 0;
    }

    int start() {
        std::cout<< "Program start" << std::endl;
        for(unsigned int i=0; i < program.size; i++) {
            Context ctx(*(program.data + i));
            ctx.print();
            OperationFactory::Operation op = OperationFactory::getOperation(ctx);
            if(!op) {
                fprintf(stderr, "Error: Wrong opcode 0x%04X\n", ctx.opcode);
                return -1;
            }
            op(ctx);
        }
        std::cout << "Program end" << std::endl;
        return 0;
    }
};

uint16_t testProgram[] = {
    0x00E0, // CLS
    0x00EE,  // RET
    0x1222, // JP addr
    0x2222, // CALL addr
    0x3011, // SE Vx, byte
    0x4011, // SNE Vx, byte
    0x5010, // SE Vx, Vy
    0x6011, // LD Vx, byte
    0x7011, // ADD Vx, byte
    0x8010, // LD Vx, Vy
    0x8011, // OR Vx, Vy
    0x8012, // AND Vx, Vy
    0x8013, // XOR Vx, Vy
    0x8014, // ADD Vx, Vy
    0x8015, // SUB Vx, Vy
    0x8016, // SHR Vx {, Vy}
    0x8017, // SUBN Vx, Vy
    0x801E, // SHL Vx {, Vy}
    0x9010, // SNE Vx, Vy
    0xA111, // LD I, addr
    0xB111, // JP V0, addr
    0xC011, // RND Vx, byte
    0xD011, // DRW Vx, Vy nibble
    0xE09E, // SKP Vx
    0xE0A1, // SKNP Vx
    0xF007, // LD Vx, DT
    0xF00A, // LD Vx, K
    0xF015, // LD DT, Vx
    0xF018, // LD ST, Vx
    0xF01E, // ADD I, Vx
    0xF029, // LD F, Vx
    0xF033, // LD B, Vx
    0xF055, // LD [I], Vx
    0xF065  // LD Vx, [I]
};

int main() {
    Processor proc;
    proc.loadProgram(testProgram, sizeof(testProgram) / sizeof(uint16_t));
    proc.start();
    return 0;
}