#include "xgpio.h"
#include "xil_printf.h"
#include "stdio.h"

#define SW_DEVICE_ID XPAR_GPIO_0_DEVICE_ID

XGpio sw_gpio;
unsigned input_arr[20];

int main()
{
    int sw_status = XGpio_Initialize(&sw_gpio, SW_DEVICE_ID);
    if (sw_status != XST_SUCCESS) {
        xil_printf("Gpio Initialization Failed\r\n");
    }
    XGpio_SetDataDirection(&sw_gpio, 1, 0x00);

    while (1) {

        int sw_state = 0;

        xil_printf("Please enter 20 positive numbers\r\n");
        for (int i = 0; i < 20; ++i) {
            scanf("%d", &input_arr[i]);
            xil_printf("%d ", input_arr[i]);
        }

        xil_printf("\r\nThe input array is: \r\n");
        for (int i = 0; i < 20; ++i) {
            xil_printf("%d ", input_arr[i]);
        }
        xil_printf("\r\n");

        sw_state = XGpio_DiscreteRead(&sw_gpio, 1);
        if (!sw_state) {
            xil_printf("Mode: small to big\r\n");
            int key, j;
            for (int i = 0; i < 20; ++i) {
                key = input_arr[i];
                j = i - 1;
                while (j >= 0 && input_arr[j] > key) {
                    input_arr[j + 1] = input_arr[j];
                    j = j - 1;
                }
                input_arr[j + 1] = key;
            }
        } else {
            xil_printf("Mode: big to small\r\n");
            int key, j;
            for (int i = 0; i < 20; ++i) {
                key = input_arr[i];
                j = i - 1;
                while (j >= 0 && input_arr[j] < key) {
                    input_arr[j + 1] = input_arr[j];
                    j = j - 1;
                }
                input_arr[j + 1] = key;
            }
        }

        xil_printf("The output array is: \r\n");
        for (int i = 0; i < 20; ++i) {
            xil_printf("%d ", input_arr[i]);
        }
        xil_printf("\r\n");

    }
    return XST_SUCCESS;
}
