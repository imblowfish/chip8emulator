#ifndef __CHIP8_OPERATION_FACTORY_H__
#define __CHIP8_OPERATION_FACTORY_H__

#include "operations.h"

namespace Chip8Operation {
    class OperationFactory {
    public:
#define OP(opname) Operations::opname
#define CASE_OP(code, opname) \
    case code:                \
        return OP(opname)
        using Operation = int (*)(OP_PARAMS);

        static Operation getOperation(const Context &ctx);
    };
} // namespace Operation

#endif
