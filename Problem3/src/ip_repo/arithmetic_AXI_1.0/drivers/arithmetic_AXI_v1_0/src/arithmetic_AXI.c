#include "arithmetic_AXI.h"

u32 arithmetic(UINTPTR baseAddr, u32 operand1, u32 operand2, char op){
    u32 result;
    u32 data = ((operand1 & 0xff) + (operand2 << 8)) & 0xffff;
    switch (op) {
        case '+':
            break;
        case '-':
            data += 0x10000;
            break;
        case '*':
            data += 0x20000;
    }
    mWriteReg(baseAddr, ARITHMETIC_AXI_S00_AXI_SLV_REG0_OFFSET, data);
    result = mReadReg(baseAddr, ARITHMETIC_AXI_S00_AXI_SLV_REG1_OFFSET);

    return result;
}


