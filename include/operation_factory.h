#ifndef __CHIP8_OPERATION_FACTORY_H__
#define __CHIP8_OPERATION_FACTORY_H__

class OperationFactory {
public:
    #define OP(opname) Operations::opname
    #define CASE_OP(code, opname) case code: return OP(opname)
    using Operation = int (*) (Context &ctx);

    static Operation getOperation(Context &ctx);
};

#endif

