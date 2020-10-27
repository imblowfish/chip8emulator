#include <cstdint>

#include "context.h"
#include "operations.h"

// 0x0... operations
int Operations::cls(OP_PARAMS) {
    return 0;
}

int Operations::ret(OP_PARAMS) {
    return 0;
}

// 0x8... operations
int Operations::shl_x_y(OP_PARAMS) {
    return 0;
}

int Operations::ld_x_y(OP_PARAMS) {
    return 0;
}

int Operations::or_x_y(OP_PARAMS) {
    return 0;
}

int Operations::and_x_y(OP_PARAMS) {
    return 0;
}

int Operations::xor_x_y(OP_PARAMS) {
    return 0;
}

int Operations::add_x_y(OP_PARAMS) {
    return 0;
}

int Operations::sub_x_y(OP_PARAMS) {
    return 0;
}

int Operations::shr_x_y(OP_PARAMS) {
    return 0;
}

int Operations::subn_x_y(OP_PARAMS) {
    return 0;
}

// 0xE... operations
int Operations::skp_x(OP_PARAMS) {
    return 0;
}

int Operations::sknp_x(OP_PARAMS) {
    return 0;
}

// 0xF... operations
int Operations::ld_x_dt(OP_PARAMS) {
    return 0;
}

int Operations::ld_x_key(OP_PARAMS) {
    return 0;
}

int Operations::ld_dt_x(OP_PARAMS) {
    return 0;
}

int Operations::ld_st_x(OP_PARAMS) {
    return 0;
}

int Operations::add_I_x(OP_PARAMS) {
    return 0;
}

int Operations::ld_F_x(OP_PARAMS) {
    return 0;
}

int Operations::ld_BCD_x(OP_PARAMS) {
    return 0;
}

int Operations::ld_Iaddr_x(OP_PARAMS) {
    return 0;
}

int Operations::ld_x_Iaddr(OP_PARAMS) {
    return 0;
}

// another operations
int Operations::jp_to_addr(OP_PARAMS) {
    return 0;
}

int Operations::call_addr(OP_PARAMS) {
    return 0;
}

int Operations::se_x_kk(OP_PARAMS) {
    return 0;
}

int Operations::sne_x_kk(OP_PARAMS) {
    return 0;
}

int Operations::se_x_y(OP_PARAMS) {
    return 0;
}

int Operations::ld_x_kk(OP_PARAMS) {
    return 0;
}

int Operations::add_x_kk(OP_PARAMS) {
    return 0;
}

int Operations::sne_x_y(OP_PARAMS) {
    return 0;
}

int Operations::ld_I_addr(OP_PARAMS) {
    return 0;
}

int Operations::jp_v0_addr(OP_PARAMS) {
    return 0;
}

int Operations::rnd_x_kk(OP_PARAMS) {
    return 0;
}

int Operations::drw_x_y_nibble(OP_PARAMS) {
    return 0;
}



