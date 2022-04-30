#ifndef PARITY_AXI
#define PARITY_AXI

//  include files
#include "xil_types.h"
#include "xstatus.h"
#include "xil_io.h"

//  define
#define PARITY_AXI_S00_AXI_SLV_REG0_OFFSET 0
#define PARITY_AXI_S00_AXI_SLV_REG1_OFFSET 4
#define PARITY_AXI_S00_AXI_SLV_REG2_OFFSET 8
#define PARITY_AXI_S00_AXI_SLV_REG3_OFFSET 12

//  type declaration
#define mWriteReg(BaseAddress, RegOffset, Data) \
        Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

#define mReadReg(BaseAddress, RegOffset) \
        Xil_In32((BaseAddress) + (RegOffset))

//  function prototypes
XStatus PARITY_AXI_Reg_SelfTest(void * baseaddr_p);

u32 parity(UINTPTR baseAddr, u32 data);

#endif

