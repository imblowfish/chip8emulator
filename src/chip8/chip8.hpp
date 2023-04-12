#ifndef __CHIP8_PROCESSOR_H__
#define __CHIP8_PROCESSOR_H__

#include <filesystem>
#include "chip8/config.hpp"
#include "chip8/opcode.hpp"

namespace chip8 {
class Chip8 {
private:
  opcode::Context ctx{};

public:
  Chip8(std::filesystem::path romPath);
  [[noreturn]] void start();
};
} // namespace chip8

#endif
