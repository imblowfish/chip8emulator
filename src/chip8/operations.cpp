#include "precompiled.hpp"
#include "types.h"
#include "chip8/operations.h"

namespace chip8 {
// https://github.com/mattmikolay/chip-8/wiki/CHIP%E2%80%908-Instruction-Set
namespace {
void clearScreen(OperationContext &ctx) { ctx.display.fill(false); }

void returnFromSubroutine(OperationContext &ctx) {
  ctx.regs.pc = ctx.regs.stack.top();
  ctx.regs.stack.pop();
}

void jumpToAddress(OperationContext &ctx) { ctx.regs.pc = ctx.addr; }

void executeSubroutineAtAddress(OperationContext &ctx) {
  ctx.regs.stack.emplace(ctx.regs.pc);
  ctx.regs.pc = ctx.addr;
}

void skipIfVxEqByte(OperationContext &ctx) {
  if (ctx.regs.V[ctx.x] != ctx.byte) {
    return;
  }
  ctx.regs.pc += 2;
}

void skipIfVxNotEqByte(OperationContext &ctx) {
  if (ctx.regs.V[ctx.x] == ctx.byte) {
    return;
  }
  ctx.regs.pc += 2;
}

void skipIfVxEqVy(OperationContext &ctx) {
  if (ctx.regs.V[ctx.x] != ctx.regs.V[ctx.y]) {
    return;
  }
  ctx.regs.pc += 2;
}

void storeByteInVx(OperationContext &ctx) { ctx.regs.V[ctx.x] = ctx.byte; }

void addByteToVx(OperationContext &ctx) { ctx.regs.V[ctx.x] += ctx.byte; }

void storeVyInVx(OperationContext &ctx) { ctx.regs.V[ctx.x] = ctx.regs.V[ctx.y]; }

void setVxOrVy(OperationContext &ctx) { ctx.regs.V[ctx.x] |= ctx.regs.V[ctx.y]; }

void setVxAndVy(OperationContext &ctx) { ctx.regs.V[ctx.x] &= ctx.regs.V[ctx.y]; }

void setVxXorVy(OperationContext &ctx) { ctx.regs.V[ctx.x] ^= ctx.regs.V[ctx.y]; }

void addVyToVx(OperationContext &ctx) {
  uint16_t sum      = ctx.regs.V[ctx.x] + ctx.regs.V[ctx.y];
  ctx.regs.V[ctx.x] = static_cast<uint8_t>(sum);
  ctx.regs.V[0xF]   = sum > 0xFF;
}

void subVyFromVx(OperationContext &ctx) {
  ctx.regs.V[0xF] = ctx.regs.V[ctx.x] > ctx.regs.V[ctx.y];
  ctx.regs.V[ctx.x] -= ctx.regs.V[ctx.y];
}

void shiftVyRightByOneAndStoreInVx(OperationContext &ctx) {
  ctx.regs.V[ctx.x] = ctx.regs.V[ctx.y] >> 1;
  ctx.regs.V[0xF]   = ctx.regs.V[ctx.x] & 0x1;
}

void subVxFromVy(OperationContext &ctx) {
  ctx.regs.V[0xF]   = ctx.regs.V[ctx.y] > ctx.regs.V[ctx.x];
  ctx.regs.V[ctx.x] = ctx.regs.V[ctx.y] - ctx.regs.V[ctx.x];
}

void shiftVyLeftByOneAndStoreInVx(OperationContext &ctx) {
  ctx.regs.V[ctx.x] = ctx.regs.V[ctx.y] << 1;
  ctx.regs.V[0xF]   = ctx.regs.V[ctx.x] & 0x1;
}

void skipIfVxNotEqVy(OperationContext &ctx) {
  if (ctx.regs.V[ctx.x] == ctx.regs.V[ctx.y]) {
    return;
  }
  ctx.regs.pc += 2;
}

void storeAddressInI(OperationContext &ctx) { ctx.regs.I = ctx.addr; }

void jumpToV0PlusAddress(OperationContext &ctx) { ctx.regs.pc = ctx.regs.V[0] + ctx.addr; }

void setVxToRandomWithByteMask(OperationContext &ctx) {
  std::random_device randomDevice;
  std::mt19937       generator(randomDevice());

  std::uniform_int_distribution<uint8_t> distribution{};

  ctx.regs.V[ctx.x] = distribution(generator) & ctx.byte;
}

void drawSpriteDataAtVxVtStartingFromI(OperationContext &ctx) {
  auto begin = ctx.ram.cbegin() + ctx.regs.I;
  auto end   = begin + ctx.nibble;

  auto displayPos = ctx.display.begin() + ctx.y * screenWidth + ctx.x;

  for (auto spriteIt = begin; spriteIt != end; ++spriteIt, ++displayPos) {
    for (ssize_t i = 7; i >= 0; --i) {
      bool spriteValue = *spriteIt >> i & 0x1;
      ctx.regs.V[0xF]  = ctx.regs.V[0xF] ? ctx.regs.V[0xF] : spriteValue && !(*displayPos);
      *displayPos      = spriteValue;
    }
  }
}

void skipIfKeyVxPressed(OperationContext &ctx) {
  uint8_t key = ctx.regs.V[ctx.x];
  if (!ctx.keyboard[key]) {
    return;
  }
  ctx.regs.pc++;
}

void skipIfKeyVxNotPressed(OperationContext &ctx) {
  uint8_t key = ctx.regs.V[ctx.x];
  if (ctx.keyboard[key]) {
    return;
  }
  ctx.regs.pc++;
}

void storeDelayTimerInVx(OperationContext &ctx) { ctx.regs.V[ctx.x] = ctx.regs.DT; }

void waitForKeyAndStoreInVx([[maybe_unused]] OperationContext &ctx) {
  // TODO
}

void setDelayTimerToVxValue(OperationContext &ctx) { ctx.regs.DT = ctx.regs.V[ctx.x]; }

void setSoundTimerToVxValue(OperationContext &ctx) { ctx.regs.ST = ctx.regs.V[ctx.x]; }

void addVxValueToI(OperationContext &ctx) { ctx.regs.I += ctx.regs.V[ctx.x]; }

void setIToSpriteAddressStoredInVx(OperationContext &ctx) { ctx.regs.I = ctx.regs.V[ctx.x]; }

void setBCDEquivalentOfVxValueAtIAddress(OperationContext &ctx) {
  std::vector<uint8_t> bcd{};
  for (size_t divider = 1000; divider > 1; divider /= 10) {
    bcd.emplace_back(ctx.regs.V[ctx.x] % divider * 10 / divider);
  }
  std::copy(bcd.cbegin(), bcd.cend(), ctx.ram.begin() + ctx.regs.I);
}

void storeValuesFromV0ToVxAtIAddress(OperationContext &ctx) {
  std::copy(ctx.regs.V.cbegin(), ctx.regs.V.cbegin() + ctx.x, ctx.ram.begin() + ctx.regs.I);
  ctx.regs.I += ctx.x + 1;
}

void fillV0ToVxWithValueAtIAddress(OperationContext &ctx) {
  std::copy(ctx.ram.cbegin() + ctx.regs.I, ctx.ram.cbegin() + ctx.regs.I + ctx.x,
            ctx.regs.V.begin() + ctx.x);
  ctx.regs.I += ctx.x + 1;
}
} // namespace

std::function<void(OperationContext &)> decode(uint16_t opcode) {
  if (0x00E0 == opcode) {
    return clearScreen;
  }
  if (0x00EE == opcode) {
    return returnFromSubroutine;
  }
  switch (opcode & 0xF000) {
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
      switch (opcode & 0x000F) {
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
          return shiftVyRightByOneAndStoreInVx;
        case 0x0007:
          return subVxFromVy;
        case 0x000E:
          return shiftVyLeftByOneAndStoreInVx;
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
      switch (opcode & 0x00FF) {
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
      switch (opcode & 0x00FF) {
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
  throw std::runtime_error(fmt::format("Unknown opcode 0x{:X}", opcode));
}
} // namespace chip8
