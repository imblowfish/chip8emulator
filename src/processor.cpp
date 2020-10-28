#include "processor.h"

#include <chrono>
#include <cstdint>
#include <cstring>
#include <vector>
#include <iostream>

#include "context.h"
#include "operation_factory.h"
#include "processor.h"

Processor::Processor() : START_PROGRAM_ADDRESS(0x200), 
                         FREQUENCY(1.0 / 60 * 1000), 
                         timer(FREQUENCY), 
                         pc(0),
                         DT(0),
                         ST(0),
                         I(0) {
    // TODO: Add initialization of arrays in initialize list
    memset(memory, 0, sizeof(memory));
    memset(V, 0, sizeof(V));
    loadSprites();
}

Processor::~Processor() {}

void Processor::loadSprites() {
    std::vector<std::vector<uint8_t>> sprites = {
        {0xF0, 0x90, 0x90, 0x90, 0xF0}, // 0
        {0x20, 0x60, 0x20, 0x20, 0x70}, // 1
        {0xF0, 0x10, 0xF0, 0x80, 0xF0}, // 2
        {0xF0, 0x10, 0xF0, 0x10, 0xF0}, // 3
        {0x90, 0x90, 0xF0, 0x10, 0x10}, // 4
        {0xF0, 0x80, 0xF0, 0x10, 0xF0}, // 5
        {0xF0, 0x80, 0xF0, 0x90, 0xF0}, // 6
        {0xF0, 0x10, 0x20, 0x40, 0x40}, // 7
        {0xF0, 0x90, 0xF0, 0x90, 0xF0}, // 8
        {0xF0, 0x90, 0xF0, 0x10, 0xF0}, // 9
        {0xF0, 0x90, 0xF0, 0x90, 0x90}, // A
        {0xE0, 0x90, 0xE0, 0x90, 0xE0}, // B
        {0xF0, 0x80, 0x80, 0x80, 0xF0}, // C
        {0xE0, 0x90, 0x90, 0x90, 0xE0}, // D
        {0xF0, 0x80, 0xF0, 0x80, 0xF0}, // E
        {0xF0, 0x80, 0xF0, 0x80, 0x80}  // F
    };
    size_t memoryCounter = 0x000;
    for(std::vector<uint8_t> sprite : sprites) {
        for(unsigned int i=0; i < sprite.size(); i++) {
            memory[memoryCounter++] = sprite[i];
        }
    }
}

int Processor::loadProgram(uint8_t *program, size_t size) {
    for (unsigned int i = 0; i < size; i++) {
        memory[START_PROGRAM_ADDRESS + i] = program[i];
    }
    return 0;
}

void Processor::start() {
    std::cout << "Run program" << std::endl;
    pc = START_PROGRAM_ADDRESS;
    step();
}

void Processor::step() {
    if (pc >= sizeof(memory)) {
        printf("Memory error, pc 0x%04llX, memory 0x%04llX\n", pc, sizeof(memory));
        return;
    }
    uint16_t opcode = (memory[pc] << 8) | memory[pc + 1];
    if (!opcode) {
        end();
        return;
    }
    pc += 2;
    printf("Execute %04X opcode\n", opcode);
    Context ctx(opcode);
    OperationFactory::Operation op = OperationFactory::getOperation(ctx);
    if(!op) {
        printf("Wrong opcode %04X\n", opcode);
        return;
    }
    int res = op(ctx, *this);
    if (res != 0) {
        printf("Operation res %d\n", res);
        return;
    }
    timer.wait();
    if(ST) {
        // make sound
        ST--;
    }
    if(DT) {
        // make sound
        DT--;
    }
    if(ST || DT) {
        timer.start();
    }
    step();
}

void Processor::end() { 
    std::cout << "Program end" << std::endl; 
}

Timer& Processor::getTimer() {
    return timer;
}

Display& Processor::getDisplay() {
    return display;
}

Keyboard& Processor::getKeyboard() {
    return keyboard;
}

Stack& Processor::getStack() {
    return stack;
}

uint16_t Processor::getSprite(uint8_t spriteNum) {
    return memory[spriteNum * sizeof(uint8_t)];
}