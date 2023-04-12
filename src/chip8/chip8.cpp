#include "precompiled.hpp"
#include "types.h"
#include "operations.h"
#include "chip8/chip8.h"

namespace chip8 {
Chip8::Chip8(std::filesystem::path romPath) {
  using namespace std::filesystem;
  if (!exists(romPath) || !is_regular_file(romPath) || is_empty(romPath)) {
    throw std::runtime_error("Can't open file");
  }

  const size_t fileSize = file_size(romPath);
  if (fileSize > ram.size() - programStartAddress) {
    throw std::runtime_error("Can't fit program in RAM");
  }

  std::ifstream romFile(romPath, std::ios::binary);
  romFile.read(reinterpret_cast<char *>(ram.data() + programStartAddress), fileSize);

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

  std::copy(sprites.cbegin(), sprites.cend(), ram.begin());
}

void Chip8::start() {
  using namespace std::chrono;
  using namespace std::chrono_literals;

  regs.pc = 0x200;

  milliseconds period{1000 / 60}; // 60Hz
  auto         start = steady_clock::now();

  while (true) {
    if (steady_clock::now() - start < period) {
      continue;
    }
    start = steady_clock::now();

    regs.DT -= regs.DT ? 1 : 0;
    regs.ST -= regs.ST ? 1 : 0;

    uint16_t opcode = ram[regs.pc] << 8 | ram[regs.pc + 1];

    auto ctx = OperationContext{
      .ram      = ram,
      .display  = display,
      .keyboard = keyboard,
      .regs     = regs,

      .addr   = static_cast<uint16_t>(opcode & 0x0FFF),
      .byte   = static_cast<uint8_t>(opcode & 0x00FF),
      .nibble = static_cast<uint8_t>(opcode & 0x000F),

      .x = static_cast<uint8_t>(opcode & 0x0F00),
      .y = static_cast<uint8_t>(opcode & 0x00F0),
    };

    fmt::println("Execute opcode 0x{:X}", opcode);
    decode(opcode)(ctx);

    // TODO: Execute operation
    // TODO: Update keyboard
    // TODO: Update display
  }
}
} // namespace chip8
