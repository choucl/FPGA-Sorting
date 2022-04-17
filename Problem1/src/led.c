#include "xgpio.h"
#include "xil_printf.h"

#define LED_DEVICE_ID XPAR_GPIO_0_DEVICE_ID
#define ROUND 0x1fff

XGpio LED_Gpio;
unsigned red_arr[6] = {0xff, 0xff, 0xff, 0x00, 0x00, 0x7f};
unsigned green_arr[6] = {0x00, 0x61, 0xff, 0xff, 0x00, 0x1f};
unsigned blue_arr[6] = {0x00, 0x00, 0x00, 0x00, 0xff, 0xff};

int main()
{
    int LED_status;
    unsigned LED_data = 0b100;
    LED_status = XGpio_Initialize(&LED_Gpio, LED_DEVICE_ID);
    if (LED_status != XST_SUCCESS) {
        xil_printf("Gpio Initialization Failed\r\n");
    }
    XGpio_SetDataDirection(&LED_Gpio, 1, 0x00);

    int state = 0;
    while (1) {
        xil_printf("current state = %d\r\n", state);
        for (int count = 0; count < ROUND; ++count) {
            for (int t = 0; t < 256; ++t) {
                int red_data = (t < red_arr[state])? 1 : 0;
                int green_data = (t < green_arr[state])? 1 << 1 : 0;
                int blue_data = (t < blue_arr[state])? 1 << 2 : 0;
                LED_data = red_data + green_data + blue_data;
                XGpio_DiscreteWrite(&LED_Gpio, 1, LED_data);
            }
        }
        if (state == 5) {
            state = 0;
        } else {
            state++;
        }
    }
    return XST_SUCCESS;
}