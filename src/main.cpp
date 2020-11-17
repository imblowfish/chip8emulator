#include <string>
#include <iostream>

#include "program_reader.h"
#include "chip8/memory.h"
#include "chip8/processor.h"

int main(int argc, char **argv) {
    if(argc != 2) {
        std::cout << "Wrong arguments num" << std::endl;
        return -1;
    }
    std::string filepath = argv[1];
    Chip8::Processor chip8;
    chip8.getMemory().loadProgram(ProgramReader::readProgram(filepath));
    chip8.start();
    return 0;
}