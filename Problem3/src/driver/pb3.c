#include "pb3.h"

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
    mWriteReg(baseAddr, PB3_S00_AXI_SLV_REG0_OFFSET, data);
    result = mReadReg(baseAddr, PB3_S00_AXI_SLV_REG1_OFFSET);

    return result;
}

u32 sort(UINTPTR baseAddr, u32 data){
    u32 result;
    mWriteReg(baseAddr, PB3_S00_AXI_SLV_REG2_OFFSET, data);
    mWriteReg(baseAddr, PB3_S00_AXI_SLV_REG3_OFFSET, STRAT);
    while (!mReadReg(baseAddr, PB3_S00_AXI_SLV_REG5_OFFSET)); // until data is valid
    result = mReadReg(baseAddr, PB3_S00_AXI_SLV_REG4_OFFSET);
    mWriteReg(baseAddr, PB3_S00_AXI_SLV_REG3_OFFSET, CLEAR);

    return result;
}

u32 parity(UINTPTR baseAddr, u32 data){
    u32 result;
    mWriteReg(baseAddr, PB3_S00_AXI_SLV_REG6_OFFSET, data);
    result = mReadReg(baseAddr, PB3_S00_AXI_SLV_REG7_OFFSET);

    return result;
}

