#include "btim.h"
TIM_HandleTypeDef htim6;
uint32_t currentTime = 0;

/*****************************************************************************************
 * 要使得getCurrentTime()函数正常工作，TIM6时钟源和分频因子应当在main.c中配置如下：
 * htim6.Init.Prescaler(psc) = SystemCoreClock / 1000 - 1; // 分频因子，使计数器每毫秒增加1
 * htim6.Init.Period(arr) = 1 - 1;                         // 计数器周期为1，产生1毫秒中断
 *****************************************************************************************/ 

void TIM6_init(uint16_t arr, uint16_t psc)                 //基本定时器TIM6定时中断初始化
{
    htim6.Instance = TIM6;                                 // 基本定时器
    htim6.Init.Prescaler = psc;                            // 预分频系数
    htim6.Init.CounterMode = TIM_COUNTERMODE_UP;           // 递增计数模式
    htim6.Init.Period = arr;                               // 自动重装载值
    HAL_TIM_Base_Init(&htim6);

    HAL_TIM_Base_Start_IT(&htim6);                         // 使能定时器和定时器更新中断
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)         // 定时器底层驱动（此为重写），会被HAL_TIM_Base_Init()在最后调用
{
    if (htim->Instance == TIM6)
    {
        __HAL_RCC_TIM6_CLK_ENABLE();                       // 使能TIM时钟
        HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 3, 2);         // 设置抢占优先级为0，子优先级为0
        HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);                 // 开启TIM6中断
    }
}

void TIM6_DAC_IRQHandler(void)                             // 定时器中断入口函数
{
    HAL_TIM_IRQHandler(&htim6);                            // 定时器公共中断服务函数
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)// 定时器中断回调函数
{
    if (htim->Instance == TIM6)
    {
        currentTime++;                                     //当前时间增加1ms
    }
}

uint32_t getCurrentTime(void)                              //获取当前时间，在key_scan()函数中被调用
{
    return currentTime;
}
