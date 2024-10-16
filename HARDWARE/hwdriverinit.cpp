#include "led.hpp"
#include "mdevice.hpp"
#include "containers.hpp"
#include "mplatform.hpp"
#include "systick.hpp"
int initAllDevice()
{
    systick* msystick = new systick;
    if(msystick)
    {
        msystick->init();//do no thing
    }

    ledx* led0 = new ledx("led0");
    led0->init([](bool benable){ if(benable) __HAL_RCC_GPIOC_CLK_ENABLE(); },GPIOC,GPIO_PIN_13);
    return 0;
}
INIT_EXPORT(initAllDevice, "1");
