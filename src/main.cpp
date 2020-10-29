#include "chip8/processor.h"

// TODO: Add program reading from file

// uint8_t testProgram[] = {
//     0x00, 0xE0, // CLS
//     0x00, 0xEE,  // RET
//     0x12, 0x22, // JP addr
//     0x22, 0x22, // CALL addr
//     0x30, 0x11, // SE Vx, byte
//     0x40, 0x11, // SNE Vx, byte
//     0x50, 0x10, // SE Vx, Vy
//     0x60, 0x11, // LD Vx, byte
//     0x70, 0x11, // ADD Vx, byte
//     0x80, 0x10, // LD Vx, Vy
//     0x80, 0x11, // OR Vx, Vy
//     0x80, 0x12, // AND Vx, Vy
//     0x80, 0x13, // XOR Vx, Vy
//     0x80, 0x14, // ADD Vx, Vy
//     0x80, 0x15, // SUB Vx, Vy
//     0x80, 0x16, // SHR Vx {, Vy}
//     0x80, 0x17, // SUBN Vx, Vy
//     0x80, 0x1E, // SHL Vx {, Vy}
//     0x90, 0x10, // SNE Vx, Vy
//     0xA1, 0x11, // LD I, addr
//     0xB1, 0x11, // JP V0, addr
//     0xC0, 0x11, // RND Vx, byte
//     0xD0, 0x11, // DRW Vx, Vy nibble
//     0xE0, 0x9E, // SKP Vx
//     0xE0, 0xA1, // SKNP Vx
//     0xF0, 0x07, // LD Vx, DT
//     0xF0, 0x0A, // LD Vx, K
//     0xF0, 0x15, // LD DT, Vx
//     0xF0, 0x18, // LD ST, Vx
//     0xF0, 0x1E, // ADD I, Vx
//     0xF0, 0x29, // LD F, Vx
//     0xF0, 0x33, // LD B, Vx
//     0xF0, 0x55, // LD [I], Vx
//     0xF0, 0x65  // LD Vx, [I]
// };

int main() {
    Chip8::Processor chip8;
    return 0;
}