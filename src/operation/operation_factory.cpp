#include <cstdio>
#include <cstdint>

#include "context.h"
#include "operation/operations.h"
#include "operation/operation_factory.h"

OperationFactory::Operation OperationFactory::getOperation(Context &ctx) {
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