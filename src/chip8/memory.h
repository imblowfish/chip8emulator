#ifndef __MEMORY_H__
#define __MEMORY_H__

namespace chip8 {
class Memory {
private:
  size_t bs{0xEA0};
  size_t sp{bs};

  const size_t stackSize{16};

  std::array<uint8_t, 4096> data{};

public:
  const size_t programStartAddress{0x200};

  Memory();

  uint8_t &operator[](size_t idx) throw();
  void     push(uint8_t value);
  uint8_t  pop();

  void loadProgram(std::filesystem::path romPath);
};
} // namespace chip8

#endif
