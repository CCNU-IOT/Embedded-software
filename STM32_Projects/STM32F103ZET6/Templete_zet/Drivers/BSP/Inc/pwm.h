#ifndef __PWM_H__
#define __PWM_H__
#include "main.h"
/**
 * TIM3 -> breath-led -> one channel
 * TIM2 -> Brushed DC motors -> four channel
*/
#define BREATH_LED_PWM_GENERAL_TIM                                 TIM3
#define BREATH_LED_PWM_GRNERAL_TIM_CHANNEL2                        TIM_CHANNEL_2       
#define BREATH_LED_PWM_GENERAL_TIM_PSC                             (720U - 1U) /*72MHz -> 100KHz <---> 0.01ms*/
#define BREATH_LED_PWM_GENERAL_TIM_ARR                             (100U - 1U) /*pwm 100k / 100 = 1khz*/
#define BREATH_LED_PWM_GENERAL_TIM_DUTY                            (BREATH_LED_PWM_GENERAL_TIM_ARR / 2)/*DUTY 50%*/
#define BREATH_LED_PWM_GENERAL_TIM_CHANNEL2_GPIO_PORT              GPIOB
#define BREATH_LED_PWM_GENERAL_TIM_CHANNEL2_GPIO_PIN               GPIO_PIN_5

#define BRUSHED_DC_MOTOR_PWM_GENERAL_TIM                           TIM2
#define BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL1                  TIM_CHANNEL_1
#define BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL2                  TIM_CHANNEL_2
#define BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL3                  TIM_CHANNEL_3
#define BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL4                  TIM_CHANNEL_4
#define BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_PSC                       (72U - 1U) /*72MHz -> 1MHz <---> 1us*/
#define BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_ARR                       (100U - 1U) /*PWM 1M / 100 = 10KHz*/
#define BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_DUTY                      (BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_ARR) /*DUTY 100%*/
#define BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL1_GPIO_PORT        GPIOA
#define BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL1_GPIO_PIN         GPIO_PIN_0
#define BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL2_GPIO_PORT        GPIOA
#define BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL2_GPIO_PIN         GPIO_PIN_1
#define BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL3_GPIO_PORT        GPIOA
#define BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL3_GPIO_PIN         GPIO_PIN_2
#define BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL4_GPIO_PORT        GPIOA
#define BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL4_GPIO_PIN         GPIO_PIN_3

extern TIM_HandleTypeDef breath_led_pwm_time_handle;
extern TIM_HandleTypeDef brushed_dc_motor_pwm_time_handle;
void breath_led_pwm_init(void);
void brushed_dc_motor_pwm_init(void);
#endif
