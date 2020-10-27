#include "processor.h"

#include <chrono>
#include <cstdint>
#include <cstring>
#include <iostream>

#include "context.h"
#include "operation_factory.h"
#include "timer.h"

Processor::Processor() : START_PROGRAM_ADDRESS(0x200), 
                         FREQUENCY(1.0 / 60 * 1000), 
                         timer(FREQUENCY), 
                         pc(0), 
                         I(0) {
    memset(memory, 0, sizeof(memory));
    memset(V, 0, sizeof(V));
    memset(stack, 0, sizeof(stack));
}

Processor::~Processor() {}

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
    int res = op(ctx);
    if (res != 0) {
        return;
    }
    timer.start();
    while (!timer.is_finished()) {
    }
    step();
}

void Processor::end() { std::cout << "Program end" << std::endl; }