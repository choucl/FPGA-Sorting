#include "stdio.h"
#include "xil_printf.h"
#include "xil_io.h"
#include "xparameters.h"
#include "arithmetic_AXI.h"
#include "sorting_AXI.h"
#include "parity_AXI.h"

int main(){
    u32 operand1, operand2, result;
    char op;
    u32 i;
    printf("Program Start.\n\r");
    while (getchar() != EOF) {
        printf("Input first operand:");
        scanf("%d", &operand1);
        printf(" %d\r\n", operand1);
        printf("Input second operand:");
        scanf("%d", &operand2);
        printf(" %d\r\n", operand2);
        printf("Input operator:");
        scanf("\n%c", &op);
        printf(" %c\r\n", op);

        result = arithmetic(XPAR_ARITHMETIC_0_S00_AXI_BASEADDR, operand1, operand2, op);

        if (result & 0x80) {
            printf("%d %c %d = %d\n\r", operand1, op, operand2, (result | 0xffffff00));
        } else {
            printf("%d %c %d = %d\n\r", operand1, op, operand2, (result & 0xff));
        }
        if (result & 0x100) printf("Overflow!\n\r");

        printf("Input 8 numbers: ");
        for (i = 0; i < 8; ++i) {
            operand1 = operand1 << 4;
            scanf("%d", &operand2);
            printf(" %d", operand2);
            operand1 += (operand2 & 0xf);
        }
        if (i == 8) result = sort(XPAR_SORTING_0_S00_AXI_BASEADDR, operand1);

        printf("\nSorted list:");
        for (i = 0; i < 8; ++i) {
            printf(" %d ", (result & 0xf));
            result = result >> 4;
        }
        printf("\n\r");

        printf("Input an integer: ");
        scanf("%d", &operand1);
        printf(" %d\r\n", operand1);

        result = parity(XPAR_PARITY_0_S00_AXI_BASEADDR, operand1);

        printf("The parity bit of %d is %d\n\r", operand1, result);
    }

    return 0;
}



