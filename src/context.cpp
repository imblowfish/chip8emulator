
#include "context.h"

#include <fmt/core.h>

Context::Context(const uint16_t opcode) : opcode(opcode) {
  head   = (opcode & 0xF000) >> 12;
  x      = (opcode & 0x0F00) >> 8;
  y      = (opcode & 0x00F0) >> 4;
  nibble = opcode & 0x000F;
  kk     = opcode & 0x00FF;
  addr   = opcode & 0x0FFF;
}

void Context::print() {
  fmt::println("==============");
  fmt::println("   Context:   ");
  fmt::println("==============");
  fmt::println("opcode: 0x{:X}", opcode);
  fmt::println("nibble: 0x{:X}", nibble);
  fmt::println("x:      0x{:X}", x);
  fmt::println("y:      0x{:X}", y);
  fmt::println("kk:     0x{:X}", kk);
  fmt::println("head:   0x{:X}", head);
  fmt::println("==============");
}
