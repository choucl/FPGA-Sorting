#ifndef SORTING_AXI
#define SORTING_AXI

//  include files
#include "xil_types.h"
#include "xstatus.h"
#include "xil_io.h"

//  define
#define SORTING_AXI_S00_AXI_SLV_REG0_OFFSET 0
#define SORTING_AXI_S00_AXI_SLV_REG1_OFFSET 4
#define SORTING_AXI_S00_AXI_SLV_REG2_OFFSET 8
#define SORTING_AXI_S00_AXI_SLV_REG3_OFFSET 12

#define STRAT 1
#define CLEAR 0

//  type declaration
#define mWriteReg(BaseAddress, RegOffset, Data) \
        Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

#define mReadReg(BaseAddress, RegOffset) \
        Xil_In32((BaseAddress) + (RegOffset))

//  function prototypes
XStatus SORTING_AXI_Reg_SelfTest(void * baseaddr_p);

u32 sort(UINTPTR baseAddr, u32 data);

#endif

