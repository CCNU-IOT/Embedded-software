#include "key.h"
#include "delay.h"
#include "stm32f1xx_hal_gpio.h"
#define DEBOUNCE_DELAY_MS 20
#define LONG_PRESS_DELAY_MS 1000

void key_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // ʹ��GPIOAʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOA, ENABLE);

    // ���ð�������Ϊ����ģʽ
    GPIO_InitStruct.Pin = KEY_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT; // ʹ���ڲ���������
    GPIO_Init(KEY_PORT, &GPIO_InitStruct);
}

uint8_t key_pressed(void)
{
    static uint8_t previousState = 1; // ��һ������״̬����ʼ״̬Ϊδ����
    static uint32_t debounceTimer = 0; // ����������ʱ��
    static uint32_t longPressTimer = 0; // ������ʱ��

    uint32_t currentTimer = 0; // ��ǰʱ��
    uint8_t currentState = 1; // ��ǰ����״̬��Ĭ��δ����

    currentTimer = millis(); // ��ȡ��ǰʱ��

    // ��������
    if ((currentTimer - debounceTimer) >= DEBOUNCE_DELAY_MS)
    {
        currentState = GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN);
        
        // ��ⰴ��״̬�仯
        if (currentState != previousState)
        {
            debounceTimer = currentTimer; // ���°���������ʱ��
        }
        else
        {
            // ��ⰴ������һ��ʱ����״̬
            if ((currentState == 0) && ((currentTimer - debounceTimer) >= LONG_PRESS_DELAY_MS))
            {
                // ��⵽����
                longPressTimer = currentTimer;
                // ִ�г�������
            }
        }

        previousState = currentState; // ������һ������״̬
    }

    // ���̰�
    if (currentState == 0 && (currentTimer - debounceTimer) < LONG_PRESS_DELAY_MS)
    {
        // ��⵽�̰�
        // ִ�ж̰�����
    }

    return currentState;
}
