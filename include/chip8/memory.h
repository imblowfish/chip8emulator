#ifndef __MEMORY_H__
#define __MEMORY_H__

namespace Chip8 {
    class Memory {
    private:
        const size_t PROG_START;
        const size_t STACK_START;
        const size_t STACK_SIZE;
        const size_t SPRITES_START;
        size_t bs;
        size_t sp;

        uint8_t data[4096];

        void loadSprites();

    public:
        Memory();

        uint8_t &operator[](size_t idx);
        void push(uint8_t value);
        uint8_t pop();

        bool loadProgram(uint8_t *program, size_t size);
        bool loadProgram(std::vector<uint8_t> program);

        size_t getProgStartAddress();
        uint16_t getSpriteAddress(uint8_t spriteNum);
    };
} // namespace Chip8

#endif
