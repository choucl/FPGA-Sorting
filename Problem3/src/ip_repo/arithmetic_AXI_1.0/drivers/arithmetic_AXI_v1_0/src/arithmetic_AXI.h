#ifndef ARITHMETIC_AXI
#define ARITHMETIC_AXI

//  include files
#include "xil_types.h"
#include "xstatus.h"
#include "xil_io.h"

//  define
#define ARITHMETIC_AXI_S00_AXI_SLV_REG0_OFFSET 0
#define ARITHMETIC_AXI_S00_AXI_SLV_REG1_OFFSET 4
#define ARITHMETIC_AXI_S00_AXI_SLV_REG2_OFFSET 8
#define ARITHMETIC_AXI_S00_AXI_SLV_REG3_OFFSET 12


//  type declaration
#define mWriteReg(BaseAddress, RegOffset, Data) \
        Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

#define mReadReg(BaseAddress, RegOffset) \
        Xil_In32((BaseAddress) + (RegOffset))

//  function prototypes
XStatus ARITHMETIC_AXI_Reg_SelfTest(void * baseaddr_p);

u32 arithmetic(UINTPTR baseAddr, u32 operand1, u32 operand2, char op);

#endif

