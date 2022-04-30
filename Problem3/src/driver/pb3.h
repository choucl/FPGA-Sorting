#ifndef PB3
#define PB3

//  include files
#include "xil_types.h"
#include "xstatus.h"
#include "xil_io.h"

//  define
#define PB3_S00_AXI_SLV_REG0_OFFSET 0
#define PB3_S00_AXI_SLV_REG1_OFFSET 4
#define PB3_S00_AXI_SLV_REG2_OFFSET 8
#define PB3_S00_AXI_SLV_REG3_OFFSET 12
#define PB3_S00_AXI_SLV_REG4_OFFSET 16
#define PB3_S00_AXI_SLV_REG5_OFFSET 20
#define PB3_S00_AXI_SLV_REG6_OFFSET 24
#define PB3_S00_AXI_SLV_REG7_OFFSET 28
#define STRAT 1
#define CLEAR 0

//  type declaration
#define mWriteReg(BaseAddress, RegOffset, Data) \
        Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

#define mReadReg(BaseAddress, RegOffset) \
        Xil_In32((BaseAddress) + (RegOffset))

//  function prototypes
XStatus PB3_Reg_SelfTest(void * baseaddr_p);

u32 arithmetic(UINTPTR baseAddr, u32 operand1, u32 operand2, char op);

u32 sort(UINTPTR baseAddr, u32 data);

u32 parity(UINTPTR baseAddr, u32 data);

#endif

