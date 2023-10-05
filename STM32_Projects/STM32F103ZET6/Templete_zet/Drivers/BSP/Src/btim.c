#include "btim.h"
TIM_HandleTypeDef htim6;
uint32_t currentTime = 0;

/*****************************************************************************************
 * Ҫʹ��getCurrentTime()��������������TIM6ʱ��Դ�ͷ�Ƶ����Ӧ����main.c���������£�
 * htim6.Init.Prescaler(psc) = SystemCoreClock / 1000 - 1; // ��Ƶ���ӣ�ʹ������ÿ��������1
 * htim6.Init.Period(arr) = 1 - 1;                         // ����������Ϊ1������1�����ж�
 *****************************************************************************************/ 

void TIM6_init(uint16_t arr, uint16_t psc)                 //������ʱ��TIM6��ʱ�жϳ�ʼ��
{
    htim6.Instance = TIM6;                                 // ������ʱ��
    htim6.Init.Prescaler = psc;                            // Ԥ��Ƶϵ��
    htim6.Init.CounterMode = TIM_COUNTERMODE_UP;           // ��������ģʽ
    htim6.Init.Period = arr;                               // �Զ���װ��ֵ
    HAL_TIM_Base_Init(&htim6);

    HAL_TIM_Base_Start_IT(&htim6);                         // ʹ�ܶ�ʱ���Ͷ�ʱ�������ж�
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)         // ��ʱ���ײ���������Ϊ��д�����ᱻHAL_TIM_Base_Init()��������
{
    if (htim->Instance == TIM6)
    {
        __HAL_RCC_TIM6_CLK_ENABLE();                       // ʹ��TIMʱ��
        HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 3, 2);         // ������ռ���ȼ�Ϊ0�������ȼ�Ϊ0
        HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);                 // ����TIM6�ж�
    }
}

void TIM6_DAC_IRQHandler(void)                             // ��ʱ���ж���ں���
{
    HAL_TIM_IRQHandler(&htim6);                            // ��ʱ�������жϷ�����
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)// ��ʱ���жϻص�����
{
    if (htim->Instance == TIM6)
    {
        currentTime++;                                     //��ǰʱ������1ms
    }
}

uint32_t getCurrentTime(void)                              //��ȡ��ǰʱ�䣬��key_scan()�����б�����
{
    return currentTime;
}
