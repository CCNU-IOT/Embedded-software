#include "btim.h"
TIM_HandleTypeDef htim6;
uint32_t currentTime = 0;

/*****************************************************************************************
 * ????getCurrentTime()??????????????TIM6?????????????????main.c???????????
 * htim6.Init.Prescaler(psc) = SystemCoreClock / 1000 - 1; // ????????????????????????1
 * htim6.Init.Period(arr) = 1 - 1;                         // ???????????1??????1?????��?
 *****************************************************************************************/ 

void TIM6_init(uint16_t arr, uint16_t psc)                 //?????????TIM6????��?????
{
    htim6.Instance = TIM6;                                 // ?????????
    htim6.Init.Prescaler = psc;                            // ???????
    htim6.Init.CounterMode = TIM_COUNTERMODE_UP;           // ??????????
    htim6.Init.Period = arr;                               // ?????????
    HAL_TIM_Base_Init(&htim6);

    HAL_TIM_Base_Start_IT(&htim6);                         // ??????????????????��?
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)         // ???????????????????��??????HAL_TIM_Base_Init()????????
{
    if (htim->Instance == TIM6)
    {
        __HAL_RCC_TIM6_CLK_ENABLE();                       // ???TIM???
        HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 3, 2);         // ?????????????0??????????0
        HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);                 // ????TIM6?��?
    }
}

void TIM6_DAC_IRQHandler(void)                             // ??????��???????
{
    HAL_TIM_IRQHandler(&htim6);                            // ??????????��??????
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)// ??????��???????
{
    if (htim->Instance == TIM6)
    {
        currentTime++;                                     //??????????1ms
    }
}

uint32_t getCurrentTime(void)                              //???????????key_scan()?????��?????
{
    return currentTime;
}
