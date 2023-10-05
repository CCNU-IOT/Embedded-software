#ifndef __KEY_H__
#define __KEY_H__
#include "main.h"

#define KEY_UP_PIN             GPIO_PIN_0
#define KEY_UP_PORT            GPIOA
#define KEY0_PIN               GPIO_PIN_4
#define KEY0_PORT              GPIOE
#define KEY1_PIN               GPIO_PIN_3
#define KEY1_PORT              GPIOE

#define DEBOUNCE_DELAY_MS 10                        // 按键消抖延时
#define LONG_PRESS_DELAY_MS 1000                    // 按键长按时间判定阈值

#define KEY_UP HAL_GPIO_ReadPin(KEY_UP_PORT, KEY_UP_PIN)      // 将KEY_UP按键引脚的状态定义为KEY_UP宏
#define KEY0   HAL_GPIO_ReadPin(KEY0_PORT, KEY0_PIN)          // 将KEY0按键引脚的状态定义为KEY0宏
#define KEY1   HAL_GPIO_ReadPin(KEY1_PORT, KEY1_PIN)          // 将KEY1按键引脚的状态定义为KEY1宏

typedef enum
{
    KEY0_PRESSED_SHORT = 0,
    KEY1_PRESSED_SHORT,
    KEY_UP_PRESSED_SHORT,
    KEY0_PRESSED_LONG,
    KEY1_PRESSED_LONG,
    KEY_UP_PRESSED_LONG,
    NO_KEY_PRESSED

} keyStatus;

void key_init(void);
uint8_t key_get_status(void);
uint8_t key_scan(void);

#endif /* __KEY_H__ */
