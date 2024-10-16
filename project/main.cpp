#include "stm32f4xx_hal.h"
#include "sys.h"
#include <stdio.h>
#include <stdlib.h>
#include "delay.h"
#include "mplatform.hpp"
#include "mdevice.hpp"
#include "mleddrv.hpp"
using namespace  std;
int main(void)
{
    mDev::mLed* led0 = (mDev::mLed*)mDev::mPlatform::getInstance()->getDevice("led0");
    printf("==========================================================\n");
    while(1)
    {
        led0->off();
        delay_ms(100);
        led0->on();
        delay_ms(100);
    }
    return 0;
}