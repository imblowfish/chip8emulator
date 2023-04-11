#include "chip8/chip8.h"

#include <fmt/core.h>
#include "context.h"
#include "device/display.h"
#include "device/keyboard.h"
#include "chip8_operation/operation_factory.h"
#include "chip8/memory.h"

namespace chip8 {
Chip8::Chip8(std::filesystem::path romPath) {
  memory   = std::make_shared<Memory>();
  display  = std::make_shared<device::Display>();
  keyboard = std::make_shared<device::Keyboard>();

  memory->loadProgram(romPath);
}

void Chip8::start() {
  using namespace std::chrono;
  using namespace std::chrono_literals;

  fmt::println("Program start");

  regs.pc    = memory->programStartAddress;
  auto start = steady_clock::now();

  while (true) {
    if (steady_clock::now() - start < period) {
      continue;
    }

    start = steady_clock::now();

    if (!step()) {
      fmt::println("Program end");
      break;
    }

    display->show();
  }
}

bool Chip8::step() {
  uint16_t opcode = fetch();
  regs.pc += 2;
  if (!opcode) {
    fmt::println("Zero opcode 0x${:X}, pc={:X}", opcode, regs.pc);
    return false;
  }
  return execute(opcode);
}

uint16_t Chip8::fetch() { return (*memory)[regs.pc] << 8 | (*memory)[regs.pc + 1]; }

bool Chip8::execute(uint16_t opcode) {
  using namespace chip8Operation;
  Context                     ctx(opcode);
  OperationFactory::Operation op = OperationFactory::getOperation(ctx);
  if (!op) {
    fmt::println("Unknown opcode 9x{:X}, pc={:X}", opcode, regs.pc);
    return false;
  }
  return op(ctx, *this) == 0;
}
} // namespace chip8
