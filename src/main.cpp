#include "ph.hpp"
#include "project.h"

#include "chip8/chip8.h"

int main(int argc, char **argv) {
  argparse::ArgumentParser program(project.name, project.version);

  program.add_description("Chip8 emulator");
  program.add_argument("ROM path").help("Path to Chip8 ROM file");

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error &err) {
    std::cerr << err.what() << "\n";
    std::cerr << program;
    return 1;
  }

  chip8::Chip8 chip8{program.get("ROM path")};
  chip8.start();
  return 0;
}
