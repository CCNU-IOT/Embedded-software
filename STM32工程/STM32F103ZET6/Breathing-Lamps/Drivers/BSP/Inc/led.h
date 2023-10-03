#ifndef __LED_H__
#define __LED_H__
#include "main.h"
#include "pwm.h"
#define LED_0_GPIO_PORT                                 GPIOB
#define LED_0_GPIO_PIN                                  GPIO_PIN_5
#define LED_1_GPIO_PORT                                 GPIOE
#define LED_1_GPIO_PIN                                  GPIO_PIN_5
void led_init(void);
void breath_led_init(void);
void breath_led_brightness(uint32_t duty);
#endif
