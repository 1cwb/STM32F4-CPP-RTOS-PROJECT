#include "stm32f4xx_hal.h"
#include "sys.h"
#include <stdio.h>
#include <stdlib.h>
#include "delay.h"
#include "mplatform.hpp"
#include "mdevice.hpp"
#include "mleddrv.hpp"
#include "workqueue.hpp"
#include "workqueuemanager.hpp"

using namespace  std;
int main(void)
{
    mDev::mLed* led0 = (mDev::mLed*)mDev::mPlatform::getInstance()->getDevice("led0");
    printf("==========================================================\n");
    workItem* sysInfoWorkItem = new workItem("sysinfo", 2000, 30, [&](void* param){
        led0->toggle();
    }, nullptr);
    workQueueManager::getInstance()->find(WORKQUEUE_LP_WORK)->scheduleWork(sysInfoWorkItem);
    mthread* IMUCALTHREAD = mthread::create("IMUTHREAD",1024,0,20,[&](void* p){
        uint32_t test = 0;
        while(1)
        {
            printf("%s()%d\r\n",__FUNCTION__,__LINE__);
            mthread::threadDelay(10);
        }
    },nullptr);
    if(IMUCALTHREAD)
    {
        IMUCALTHREAD->startup();
    }
    while(1)
    {
        led0->toggle();
        mthread::threadDelay(800);
    }
    return 0;
}