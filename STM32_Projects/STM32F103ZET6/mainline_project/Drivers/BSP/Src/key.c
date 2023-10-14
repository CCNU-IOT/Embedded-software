#include "key.h"
#include "btim.h"
#include "stm32f1xx_hal_gpio.h"

void key_init(void)                                 /*初始化按键*/
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_GPIOA_CLK_ENABLE();                   // 使能GPIOA时钟
    __HAL_RCC_GPIOE_CLK_ENABLE();                   // 使能GPIOE时钟

    GPIO_InitStruct.Pin = KEY_UP_PIN;               // 指定要配置的GPIO引脚为KEY_UP的引脚
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;         // 设置引脚工作模式为输入模式
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;           // 设置下拉电阻
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;        // 设置工作速度为高速
    HAL_GPIO_Init(KEY_UP_PORT, &GPIO_InitStruct);   // 初始化KEY_UP_PORT端口

    GPIO_InitStruct.Pin = KEY0_PIN;                 // 指定要配置的GPIO引脚为KEY0的引脚
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;         // 设置引脚工作模式为输入模式
    GPIO_InitStruct.Pull = GPIO_PULLUP;             // 设置上拉电阻
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;        // 设置工作速度为高速
    HAL_GPIO_Init(KEY0_PORT, &GPIO_InitStruct);     // 初始化KEY0_PORT端口

    GPIO_InitStruct.Pin = KEY1_PIN;                 // 指定要配置的GPIO引脚为KEY1的引脚
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;         // 设置引脚工作模式为输入模式
    GPIO_InitStruct.Pull = GPIO_PULLUP;             // 设置上拉电阻
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;        // 设置工作速度为高速
    HAL_GPIO_Init(KEY1_PORT, &GPIO_InitStruct);     // 初始化KEY1_PORT端口
}

uint8_t key_get_status()
{
    uint8_t keyCurrentState;
        if(KEY_UP == 1) keyCurrentState = KEY_UP_PRESSED_SHORT;
        if(KEY0 == 0) keyCurrentState = KEY0_PRESSED_SHORT;
        if(KEY1 == 0) keyCurrentState = KEY1_PRESSED_SHORT;
    return keyCurrentState;
}

uint8_t key_scan(void)
{
    static uint8_t previousState = NO_KEY_PRESSED;  // 上一个按键状态，初始为未按下
    static uint32_t debounceTimer = 0;              // 按键消抖定时器
    static uint32_t longPressTimer = 0;             // 长按定时器

    uint32_t currentTimer = 0;                      // 设置当前时间为0
    uint8_t keyCurrentState = NO_KEY_PRESSED;       // 当前按键状态，默认未按下

    currentTimer = getCurrentTime();                // 获取当前时间(仿照millis();)

    if ((currentTimer - debounceTimer) >= DEBOUNCE_DELAY_MS)        // 消抖，10MS后再读取按键状态
    {
        
        keyCurrentState = key_get_status();                         // 检测是否有按键被按下
        
        if (keyCurrentState != previousState)                       // 检测按键状态变化
        {
            debounceTimer = currentTimer;                           // 若按键状态不变，更新按键消抖定时器
        }
        else
        {                                                           // 若按键状态改变，检测按键连续一段时间后的状态
            if ((keyCurrentState != NO_KEY_PRESSED) && ((currentTimer - debounceTimer) >= LONG_PRESS_DELAY_MS))
            {
                longPressTimer = currentTimer;                      // 检测到有按键按下且为长按，更新长按定时器
                keyCurrentState += 3;                               // 将按键状态转为长按
            }
        }
        previousState = keyCurrentState;                            // 更新上一个按键状态
    }

/*    if (keyCurrentState != NO_KEY_PRESSED && (currentTimer - debounceTimer) < LONG_PRESS_DELAY_MS)
            {}                                                      // 检测短按(似乎没必要)
*/
    return keyCurrentState;
}
