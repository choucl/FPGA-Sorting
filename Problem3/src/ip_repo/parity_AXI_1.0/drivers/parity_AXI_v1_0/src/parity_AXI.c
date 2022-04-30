#include "parity_AXI.h"

u32 parity(UINTPTR baseAddr, u32 data){
    u32 result;
    mWriteReg(baseAddr, PARITY_AXI_S00_AXI_SLV_REG0_OFFSET, data);
    result = mReadReg(baseAddr, PARITY_AXI_S00_AXI_SLV_REG1_OFFSET);

    return result;
}

