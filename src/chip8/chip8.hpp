#ifndef __CHIP8_H__
#define __CHIP8_H__

#include <filesystem>
#include "chip8/component.hpp"
#include "chip8/opcode.hpp"

namespace chip8 {
using OnLoopStepCallback = std::function<void(const Display &)>;

class Chip8 {
private:
  opcode::Context ctx{};
  OnLoopStepCallback callback;

public:
  Chip8(std::filesystem::path romPath, OnLoopStepCallback callback);
  [[noreturn]] void start();
};
} // namespace chip8

#endif
