#include <argparse/argparse.hpp>
#include <fmt/core.h>
#include <fmt/color.h>

#include "project.hpp"
#include "chip8/chip8.hpp"

int main(int argc, char **argv) {
  argparse::ArgumentParser program(project.name, project.version);

  program.add_description("Chip8 emulator");
  program.add_argument("ROM path").help("Path to Chip8 ROM file");

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error &err) {
    fmt::print(stderr, fmt::fg(fmt::color::crimson), "error: ");
    fmt::println(stderr, "{}", err.what());
    fmt::println(stderr, "{}", program.help().str());
    return -1;
  }

  try {
    chip8::Chip8 chip8{program.get("ROM path"), []([[maybe_unused]] auto &display) {
      fmt::println("Callback!");
    }};
    chip8.start();
  } catch (const std::runtime_error &err) {
    fmt::println(stderr, "{}", err.what());
    return -2;
  }

  return 0;
}
