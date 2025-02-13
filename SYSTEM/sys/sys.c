#include "sys.h"
#include "delay.h"
#include "usart.h"
//stm32 f411xx hclk 96MHZ hse = 25M, M=25, N=384, P=4, Q=8
//SYSCLK(系统时钟) =96MHz
//PLL 主时钟 =96MHz
//AHB 总线时钟（HCLK=SYSCLK/1） =96MHz
//APB1 总线时钟（PCLK1=HCLK/2） =48MHz
//APB2 总线时钟（PCLK2=HCLK/1） =96MHz

void Stm32_Clock_Init(uint32_t pllm, uint32_t plln, uint32_t pllp, uint32_t pllq)
{
    HAL_StatusTypeDef ret = HAL_OK;
    RCC_OscInitTypeDef RCC_OscInitStructure;
    RCC_ClkInitTypeDef RCC_ClkInitStructure;

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    do{
        RCC_OscInitStructure.OscillatorType = RCC_OSCILLATORTYPE_HSE;
        RCC_OscInitStructure.HSEState = RCC_HSE_ON;
        RCC_OscInitStructure.PLL.PLLState = RCC_PLL_ON;
        RCC_OscInitStructure.PLL.PLLSource = RCC_PLLSOURCE_HSE;
        RCC_OscInitStructure.PLL.PLLM = pllm;
        RCC_OscInitStructure.PLL.PLLN = plln;
        RCC_OscInitStructure.PLL.PLLP = pllp;
        RCC_OscInitStructure.PLL.PLLQ = pllq;
        ret=HAL_RCC_OscConfig(&RCC_OscInitStructure);
        if(ret != HAL_OK) break;

        RCC_ClkInitStructure.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
        RCC_ClkInitStructure.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
        RCC_ClkInitStructure.AHBCLKDivider = RCC_SYSCLK_DIV1;
        RCC_ClkInitStructure.APB1CLKDivider = RCC_HCLK_DIV2;
        RCC_ClkInitStructure.APB2CLKDivider = RCC_HCLK_DIV1;
        ret=HAL_RCC_ClockConfig(&RCC_ClkInitStructure, FLASH_LATENCY_3);
        if(ret != HAL_OK) break;
    }while(0);
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/THREAD_TICK_PER_SECOND);//systick时钟默认使用HCLK，可以手动设置为AHB/8
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
    if(ret!=HAL_OK) while(1);
}

void hwInit()
{
    HAL_Init(); //初始化 HAL 库
    Stm32_Clock_Init(PLLM_VALUE,PLLN_VALUE,PLLP_VALUE,PLLQ_VALUE); //设置时钟,96Mhz
    delay_init(HAL_RCC_GetHCLKFreq()/1000000);//1US跑的tick数
    uart_init(115200);
}