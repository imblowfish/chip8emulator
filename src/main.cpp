#include <fstream>

#include <argparse/argparse.hpp>
#include <fmt/core.h>
#include <fmt/color.h>

#include "project.hpp"
#include "chip8/chip8.hpp"
#include "chip8/component.hpp"

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
    chip8::Chip8 chip8(program.get("ROM path"), [](const chip8::Display &display) {
      std::ofstream displayDump("../display.txt");

      std::vector<char> asciiDisplay{};
      std::transform(display.cbegin(), display.cend(), std::back_inserter(asciiDisplay),
                     [](auto value) {
                       return value ? '#' : ' ';
                     });

      for (size_t i = chip8::screen.width; i < asciiDisplay.size(); i += chip8::screen.width + 1) {
        asciiDisplay.insert(asciiDisplay.cbegin() + i, '\n');
      }

      displayDump.write(asciiDisplay.data(), asciiDisplay.size());
    });
    chip8.start();
  } catch (const std::runtime_error &err) {
    fmt::println(stderr, "{}", err.what());
    return -2;
  }

  return 0;
}
