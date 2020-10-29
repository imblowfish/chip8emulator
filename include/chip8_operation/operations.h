#ifndef __CHIP8_OPERATIONS_H__
#define __CHIP8_OPERATIONS_H__

class Context;

namespace Chip8 {
    class Processor;
}

namespace Chip8Operation {
    class Operations {
    private:
        Operations() = delete;
        Operations(const Operations &) = delete;
        ~Operations() = delete;

    public:
#define OP_PARAMS [[maybe_unused]] Context &ctx, \
                  [[maybe_unused]] Chip8::Processor &proc

        // 0x0... operations
        static int cls(OP_PARAMS);
        static int ret(OP_PARAMS);

        // 0x8... operations
        static int shl_x_y(OP_PARAMS);
        static int ld_x_y(OP_PARAMS);
        static int or_x_y(OP_PARAMS);
        static int and_x_y(OP_PARAMS);
        static int xor_x_y(OP_PARAMS);
        static int add_x_y(OP_PARAMS);
        static int sub_x_y(OP_PARAMS);
        static int shr_x_y(OP_PARAMS);
        static int subn_x_y(OP_PARAMS);

        // 0xE... operations
        static int skp_x(OP_PARAMS);
        static int sknp_x(OP_PARAMS);

        // 0xF... operations
        static int ld_x_dt(OP_PARAMS);
        static int ld_x_key(OP_PARAMS);
        static int ld_dt_x(OP_PARAMS);
        static int ld_st_x(OP_PARAMS);
        static int add_I_x(OP_PARAMS);
        static int ld_F_x(OP_PARAMS);
        static int ld_BCD_x(OP_PARAMS);
        static int ld_Iaddr_x(OP_PARAMS);
        static int ld_x_Iaddr(OP_PARAMS);

        // another operations
        static int jp_to_addr(OP_PARAMS);
        static int call_addr(OP_PARAMS);
        static int se_x_kk(OP_PARAMS);
        static int sne_x_kk(OP_PARAMS);
        static int se_x_y(OP_PARAMS);
        static int ld_x_kk(OP_PARAMS);
        static int add_x_kk(OP_PARAMS);
        static int sne_x_y(OP_PARAMS);
        static int ld_I_addr(OP_PARAMS);
        static int jp_v0_addr(OP_PARAMS);
        static int rnd_x_kk(OP_PARAMS);
        static int drw_x_y_nibble(OP_PARAMS);
    };
} // namespace Operations

#endif
