#include <cstdint>
#include <memory.h>
#include <string>
#include <vector>

#include "chip8/memory.h"

namespace Chip8 {
    Memory::Memory() : PROG_START(0x200),
                       STACK_START(0xEA0),
                       STACK_SIZE(16),
                       SPRITES_START(0x00),
                       bs(STACK_START),
                       sp(bs) {
        memset(data, 0, sizeof(data));
        loadSprites();
    }

    void Memory::loadSprites() {
        uint8_t sprites[] = {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };
        for(unsigned int i = 0; i < sizeof(sprites) / sizeof(uint8_t); i += 5) {
            memcpy(&data[i], &sprites[i], 5);
        }
    }

    uint8_t &Memory::operator[](size_t idx) {
        // TODO: Add limits check here
        return data[idx];
    }

    void Memory::push(uint8_t value) {
        if(sp + 1 >= STACK_START + STACK_SIZE) {
            return;
        }
        data[sp++] = value;
    }

    uint8_t Memory::pop() {
        if(sp == bs) {
            return 0;
        }
        return data[sp--];
    }

    bool Memory::loadProgram(uint8_t *program, size_t size) {
        // TODO: Add limits check here
        for(unsigned int i = 0; i < size; i++) {
            data[PROG_START + i] = program[i];
        }
        return true;
    }

    bool Memory::loadProgram(std::vector<uint8_t> program) {
        // TODO: Add limits check here
        for(unsigned int i = 0; i < program.size(); i++) {
            data[PROG_START + i] = program[i];
        }
        return true;
    }

    size_t Memory::getProgStartAddress() {
        return PROG_START;
    }

    uint16_t Memory::getSpriteAddress(uint8_t spriteNum) {
        return spriteNum * 5;
    }
} // namespace Chip8
