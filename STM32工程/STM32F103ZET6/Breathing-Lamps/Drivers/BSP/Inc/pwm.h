#ifndef __PWM_H__
#define __PWM_H__
#include "main.h"

#define PWM_GENERAL_TIM                                 TIM3
#define PWM_GRNERAL_TIM_CHANNEL2                        TIM_CHANNEL_2       
#define PWM_GENERAL_TIM_PSC                             (720U - 1U) /*72MHz -> 100KHz <---> 0.01ms*/
#define PWM_GENERAL_TIM_ARR                             (100U - 1U) /*pwm 100k / 100 = 1khz*/
#define PWM_GENERAL_TIM_DUTY                            (PWM_GENERAL_TIM_ARR / 2)/*DUTY 50%*/
#define PWM_GENERAL_TIM_CHANNEL2_GPIO_PORT              GPIOB
#define PWM_GENERAL_TIM_CHANNEL2_GPIO_PIN               GPIO_PIN_5
extern TIM_HandleTypeDef pwm_time_handle;
void pwm_init(void);
#endif
