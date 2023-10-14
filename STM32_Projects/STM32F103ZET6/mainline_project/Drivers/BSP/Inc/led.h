#ifndef __LED_H__
#define __LED_H__
#include "main.h"
#include "pwm.h"
#define LED_0_GPIO_PORT                                 GPIOB
#define LED_0_GPIO_PIN                                  GPIO_PIN_5
#define LED_1_GPIO_PORT                                 GPIOE
#define LED_1_GPIO_PIN                                  GPIO_PIN_5

typedef enum
{
    LED_Open = 0,
    LED_Close,
} LED_Status;
typedef enum
{
    Breath_Negative = 0,
    Breath_Positive,
} Breath_LED_Direction;

void led_init(void);
void breath_led_init(void);
void breath_led_brightness(Breath_LED_Direction *dircetion, uint32_t *duty);
void led_set_status(GPIO_TypeDef *gpiox, LED_Status status);
#endif
