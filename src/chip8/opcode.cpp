#include "chip8/opcode.hpp"

#include <random>
#include <stack>

namespace chip8 {
namespace opcode {
Opcode::Opcode(uint16_t opcode)
    : value{opcode}
    , head{static_cast<uint8_t>(opcode >> 12 & 0xF)}
    , addr{static_cast<uint16_t>(opcode & 0x0FFF)}
    , byte{static_cast<uint8_t>(opcode & 0x00FF)}
    , nibble{static_cast<uint8_t>(opcode & 0x000F)}
    , x{static_cast<uint8_t>(opcode >> 8 & 0xF)}
    , y{static_cast<uint8_t>(opcode >> 4 & 0xF)} {
}

namespace {
// https://github.com/mattmikolay/chip-8/wiki/CHIP%E2%80%908-Instruction-Set

void clearScreen([[maybe_unused]] Opcode &&op, Context &ctx) {
  ctx.display = Display{};
}

void returnFromSubroutine([[maybe_unused]] Opcode &&op, Context &ctx) {
  ctx.regs.pc = ctx.regs.stack.top();
  ctx.regs.stack.pop();
}

void jumpToAddress(Opcode &&op, Context &ctx) {
  ctx.regs.pc = op.addr;
}

void executeSubroutineAtAddress(Opcode &&op, Context &ctx) {
  ctx.regs.stack.emplace(ctx.regs.pc);
  ctx.regs.pc = op.addr;
}

void skipIfVxEqByte(Opcode &&op, Context &ctx) {
  if (ctx.regs.V[op.x] != op.byte) {
    return;
  }
  ctx.regs.pc += 2;
}

void skipIfVxNotEqByte(Opcode &&op, Context &ctx) {
  if (ctx.regs.V[op.x] == op.byte) {
    return;
  }
  ctx.regs.pc += 2;
}

void skipIfVxEqVy(Opcode &&op, Context &ctx) {
  if (ctx.regs.V[op.x] != ctx.regs.V[op.y]) {
    return;
  }
  ctx.regs.pc += 2;
}

void storeByteInVx(Opcode &&op, Context &ctx) {
  ctx.regs.V[op.x] = op.byte;
}

void addByteToVx(Opcode &&op, Context &ctx) {
  ctx.regs.V[op.x] += op.byte;
}

void storeVyInVx(Opcode &&op, Context &ctx) {
  ctx.regs.V[op.x] = ctx.regs.V[op.y];
}

void setVxOrVy(Opcode &&op, Context &ctx) {
  ctx.regs.V[op.x] |= ctx.regs.V[op.y];
}

void setVxAndVy(Opcode &&op, Context &ctx) {
  ctx.regs.V[op.x] &= ctx.regs.V[op.y];
}

void setVxXorVy(Opcode &&op, Context &ctx) {
  ctx.regs.V[op.x] ^= ctx.regs.V[op.y];
}

void addVyToVx(Opcode &&op, Context &ctx) {
  uint16_t sum = ctx.regs.V[op.x] + ctx.regs.V[op.y];

  ctx.regs.V[op.x] = static_cast<uint8_t>(sum);
  ctx.regs.V[0xF] = sum > 0xFF;
}

void subVyFromVx(Opcode &&op, Context &ctx) {
  uint8_t prevX = ctx.regs.V[op.x];
  ctx.regs.V[op.x] -= ctx.regs.V[op.y];
  ctx.regs.V[0xF] = prevX > ctx.regs.V[op.y];
}

void shiftVxRightByOne(Opcode &&op, Context &ctx) {
  ctx.regs.V[0xF] = ctx.regs.V[op.x] & 0x1;
  ctx.regs.V[op.x] = ctx.regs.V[op.x] >> 1;
}

void subVxFromVy(Opcode &&op, Context &ctx) {
  uint8_t prevX = ctx.regs.V[op.x];
  ctx.regs.V[op.x] = ctx.regs.V[op.y] - ctx.regs.V[op.x];
  ctx.regs.V[0xF] = ctx.regs.V[op.y] > prevX;
}

void shiftVxLeftByOne(Opcode &&op, Context &ctx) {
  ctx.regs.V[0xF] = ctx.regs.V[op.x] >> 7 & 0x1;
  ctx.regs.V[op.x] = ctx.regs.V[op.x] << 1;
}

void skipIfVxNotEqVy(Opcode &&op, Context &ctx) {
  if (ctx.regs.V[op.x] == ctx.regs.V[op.y]) {
    return;
  }
  ctx.regs.pc += 2;
}

void storeAddressInI(Opcode &&op, Context &ctx) {
  ctx.regs.I = op.addr;
}

void jumpToV0PlusAddress(Opcode &&op, Context &ctx) {
  ctx.regs.pc = ctx.regs.V[0] + op.addr;
}

void setVxToRandomWithByteMask(Opcode &&op, Context &ctx) {
  std::random_device randomDevice;
  std::mt19937 generator(randomDevice());
  std::uniform_int_distribution<uint8_t> distribution{};

  ctx.regs.V[op.x] = distribution(generator) & op.byte;
}

void drawSpriteDataAtVxVtStartingFromI(Opcode &&op, Context &ctx) {
  auto begin = ctx.ram.cbegin() + ctx.regs.I;
  auto end = begin + op.nibble;

  ctx.regs.V[0xF] = 0;
  for (auto sprite = begin; sprite < end; ++sprite) {
    size_t yPos = ctx.regs.V[op.y] + sprite - begin;
    for (size_t i = 0; i < 8; i++) {
      size_t xPos = ctx.regs.V[op.x] + i;

      auto displayPos = ctx.display.begin() + yPos * screen.width + xPos;
      bool spriteValue = *sprite << i & 0x80;

      if (spriteValue && *displayPos) {
        ctx.regs.V[0xF] = 1;
      }

      *displayPos ^= spriteValue;
    }
  }
}

void skipIfKeyVxPressed(Opcode &&op, Context &ctx) {
  uint8_t key = ctx.regs.V[op.x];
  if (!ctx.keyboard[key]) {
    return;
  }
  ctx.regs.pc++;
}

void skipIfKeyVxNotPressed(Opcode &&op, Context &ctx) {
  uint8_t key = ctx.regs.V[op.x];
  if (ctx.keyboard[key]) {
    return;
  }
  ctx.regs.pc++;
}

void storeDelayTimerInVx(Opcode &&op, Context &ctx) {
  ctx.regs.V[op.x] = ctx.regs.DT;
}

void waitForKeyAndStoreInVx([[maybe_unused]] Opcode &&op, [[maybe_unused]] Context &ctx) {
  // TODO
}

void setDelayTimerToVxValue(Opcode &&op, Context &ctx) {
  ctx.regs.DT = ctx.regs.V[op.x];
}

void setSoundTimerToVxValue(Opcode &&op, Context &ctx) {
  ctx.regs.ST = ctx.regs.V[op.x];
}

void addVxValueToI(Opcode &&op, Context &ctx) {
  ctx.regs.I += ctx.regs.V[op.x];
}

void setIToSpriteAddressStoredInVx(Opcode &&op, Context &ctx) {
  ctx.regs.I = ctx.regs.V[op.x];
}

void setBCDEquivalentOfVxValueAtIAddress(Opcode &&op, Context &ctx) {
  std::vector<uint8_t> bcd{};

  for (size_t divider = 1000; divider > 1; divider /= 10) {
    bcd.emplace_back(ctx.regs.V[op.x] % divider * 10 / divider);
  }

  std::copy(bcd.cbegin(), bcd.cend(), ctx.ram.begin() + ctx.regs.I);
}

void storeValuesFromV0ToVxAtIAddress(Opcode &&op, Context &ctx) {
  std::copy(ctx.regs.V.cbegin(), ctx.regs.V.cbegin() + op.x, ctx.ram.begin() + ctx.regs.I);
  ctx.regs.I += op.x + 1;
}

void fillV0ToVxWithValueAtIAddress(Opcode &&op, Context &ctx) {
  std::copy(ctx.ram.cbegin() + ctx.regs.I, ctx.ram.cbegin() + ctx.regs.I + op.x,
            ctx.regs.V.begin() + op.x);
  ctx.regs.I += op.x + 1;
}
} // namespace

Operation decode(const Opcode &opcode) {
  if (0x00E0 == opcode.value) {
    return clearScreen;
  }
  if (0x00EE == opcode.value) {
    return returnFromSubroutine;
  }
  switch (opcode.value & 0xF000) {
    case 0x1000:
      return jumpToAddress;
    case 0x2000:
      return executeSubroutineAtAddress;
    case 0x3000:
      return skipIfVxEqByte;
    case 0x4000:
      return skipIfVxNotEqByte;
    case 0x5000:
      return skipIfVxEqVy;
    case 0x6000:
      return storeByteInVx;
    case 0x7000:
      return addByteToVx;
    case 0x8000: {
      switch (opcode.nibble) {
        case 0x0000:
          return storeVyInVx;
        case 0x0001:
          return setVxOrVy;
        case 0x0002:
          return setVxAndVy;
        case 0x0003:
          return setVxXorVy;
        case 0x0004:
          return addVyToVx;
        case 0x0005:
          return subVyFromVx;
        case 0x0006:
          return shiftVxRightByOne;
        case 0x0007:
          return subVxFromVy;
        case 0x000E:
          return shiftVxLeftByOne;
        default:
          break;
      }
      break;
    }
    case 0x9000:
      return skipIfVxNotEqVy;
    case 0xA000:
      return storeAddressInI;
    case 0xB000:
      return jumpToV0PlusAddress;
    case 0xC000:
      return setVxToRandomWithByteMask;
    case 0xD000:
      return drawSpriteDataAtVxVtStartingFromI;
    case 0xE000: {
      switch (opcode.byte) {
        case 0x009E:
          return skipIfKeyVxPressed;
        case 0x00A1:
          return skipIfKeyVxNotPressed;
        default:
          break;
      }
      break;
    }
    case 0xF000: {
      switch (opcode.byte) {
        case 0x0007:
          return storeDelayTimerInVx;
        case 0x000A:
          return waitForKeyAndStoreInVx;
        case 0x0015:
          return setDelayTimerToVxValue;
        case 0x0018:
          return setSoundTimerToVxValue;
        case 0x001E:
          return addVxValueToI;
        case 0x0029:
          return setIToSpriteAddressStoredInVx;
        case 0x0033:
          return setBCDEquivalentOfVxValueAtIAddress;
        case 0x0055:
          return storeValuesFromV0ToVxAtIAddress;
        case 0x0065:
          return fillV0ToVxWithValueAtIAddress;
        default:
          break;
      }
      break;
    }
    default:
      break;
  }
  return std::nullopt;
}
} // namespace opcode
} // namespace chip8
