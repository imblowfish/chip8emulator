#include <string>
#include <iostream>

#include "program_reader.h"
#include "chip8/memory.h"
#include "chip8/processor.h"

void printHelp() {
    std::cout << "Chip8 emulator" << std::endl;
    std::cout << "DESCRIPTION:" << std::endl;
    std::cout << "\tsimple chip8 emulator with console display" << std::endl;
    std::cout << "SYNOPSIS" << std::endl;
    std::cout << "\tchip8 <chip8_rom_filepath>" << std::endl;
}

int main(int argc, char **argv) {
    if(argc != 2) {
        std::cout << "Error: Wrong arguments num" << std::endl;
        printHelp();
        return -1;
    }
    std::string filepath = argv[1];
    Chip8::Processor chip8;
    chip8.getMemory().loadProgram(ProgramReader::readProgram(filepath));
    chip8.start();
    return 0;
}