#include "stm32f4xx_hal.h"
#include "sys.h"
#include <stdio.h>
#include <stdlib.h>
#include "delay.h"
#include "led.h"
using namespace  std;
int main(void)
{
    led_init();
    printf("==========================================================\n");
    while(1)
    {
        led_off();
        delay_ms(100);
        led_on();
        delay_ms(100);
    }
    return 0;
}