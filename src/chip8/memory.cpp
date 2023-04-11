#include <fstream>
#include <cstring>
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

#include "chip8/memory.h"

namespace chip8 {
Memory::Memory() {
  const std::vector<uint8_t> sprites = {
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

  std::copy(sprites.cbegin(), sprites.cend(), data.begin());
}

uint8_t &Memory::operator[](size_t idx) throw() { return data.at(idx); }

void Memory::push(uint8_t value) { data.at(sp++) = value; }

uint8_t Memory::pop() { return data.at(sp--); }

void Memory::loadProgram(std::filesystem::path romPath) {
  if (!std::filesystem::exists(romPath)) {
    throw new std::runtime_error("Can't open file");
  }
  if (!std::filesystem::is_regular_file(romPath)) {
    throw new std::runtime_error("Expected regular file");
  }
  if (std::filesystem::is_empty(romPath)) {
    throw new std::runtime_error("File is empty");
  }

  const size_t fileSize = std::filesystem::file_size(romPath);
  if (fileSize > data.size() - programStartAddress) {
    throw new std::runtime_error("File contain can't fit in memory");
  }

  std::ifstream romFile(romPath, std::ios::binary);
  romFile.read(reinterpret_cast<char *>(data.data()), fileSize);
}

} // namespace chip8
