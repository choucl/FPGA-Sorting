#include "sorting_AXI.h"

u32 sort(UINTPTR baseAddr, u32 data){
    u32 result;
    mWriteReg(baseAddr, SORTING_AXI_S00_AXI_SLV_REG0_OFFSET, data);
    mWriteReg(baseAddr, SORTING_AXI_S00_AXI_SLV_REG1_OFFSET, STRAT);
    while (!mReadReg(baseAddr, SORTING_AXI_S00_AXI_SLV_REG3_OFFSET)); // until data is valid
    result = mReadReg(baseAddr,SORTING_AXI_S00_AXI_SLV_REG2_OFFSET);
    mWriteReg(baseAddr, SORTING_AXI_S00_AXI_SLV_REG1_OFFSET, CLEAR);

    return result;
}

