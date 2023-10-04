#include "key.h"
#include "delay.h"
#include "stm32f1xx_hal_gpio.h"
#define DEBOUNCE_DELAY_MS 20
#define LONG_PRESS_DELAY_MS 1000

void key_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // 使能GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOA, ENABLE);

    // 配置按键引脚为输入模式
    GPIO_InitStruct.Pin = KEY_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT; // 使用内部上拉电阻
    GPIO_Init(KEY_PORT, &GPIO_InitStruct);
}

uint8_t key_pressed(void)
{
    static uint8_t previousState = 1; // 上一个按键状态，初始状态为未按下
    static uint32_t debounceTimer = 0; // 按键消抖定时器
    static uint32_t longPressTimer = 0; // 长按定时器

    uint32_t currentTimer = 0; // 当前时间
    uint8_t currentState = 1; // 当前按键状态，默认未按下

    currentTimer = millis(); // 获取当前时间

    // 按键消抖
    if ((currentTimer - debounceTimer) >= DEBOUNCE_DELAY_MS)
    {
        currentState = GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN);
        
        // 检测按键状态变化
        if (currentState != previousState)
        {
            debounceTimer = currentTimer; // 更新按键消抖定时器
        }
        else
        {
            // 检测按键连续一段时间后的状态
            if ((currentState == 0) && ((currentTimer - debounceTimer) >= LONG_PRESS_DELAY_MS))
            {
                // 检测到长按
                longPressTimer = currentTimer;
                // 执行长按操作
            }
        }

        previousState = currentState; // 更新上一个按键状态
    }

    // 检测短按
    if (currentState == 0 && (currentTimer - debounceTimer) < LONG_PRESS_DELAY_MS)
    {
        // 检测到短按
        // 执行短按操作
    }

    return currentState;
}
