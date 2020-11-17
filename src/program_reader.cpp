#include <cstdint>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "program_reader.h"

std::vector<uint8_t> ProgramReader::readProgram(const std::string &filepath) {
    std::ifstream file(filepath);
    if(!file.is_open()) {
        std::cout << "Can't open program file " << filepath << std::endl;
        return std::vector<uint8_t>();
    }
    std::vector<uint8_t> program;
    std::string line;
    while(getline(file, line)) {
        for(unsigned int i = 0; i < line.size(); i++) {
            program.push_back(line[i]);
        }
    }
    return program;
}
