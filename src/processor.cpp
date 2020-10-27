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
                         I(0) {
    memset(memory, 0, sizeof(memory));
    memset(V, 0, sizeof(V));
    memset(stack, 0, sizeof(stack));
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
void *a;
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
    Context ctx(opcode);
    OperationFactory::Operation op = OperationFactory::getOperation(ctx);
    if(!op) {
        printf("Wrong ocpode %04X\n", opcode);
        return;
    }
    int res = op(ctx);
    if (res != 0) {
        return;
    }
    timer.start();
    while (!timer.is_finished()) {
    }
    step();
}

void Processor::end() { 
    std::cout << "Program end" << std::endl; 
}