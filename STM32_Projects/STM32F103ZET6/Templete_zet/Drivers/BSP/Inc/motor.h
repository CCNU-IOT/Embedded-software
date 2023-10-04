#ifndef __MOTOR_H__
#define __MOTOR_H__
#include "main.h"
#include "pwm.h"
#define BCD_MOTOR_AIN_1_GPIO_PORT                                   GPIOG
#define BCD_MOTOR_AIN_1_GPIO_PIN                                    GPIO_PIN_1
#define BCD_MOTOR_AIN_2_GPIO_PORT                                   GPIOG
#define BCD_MOTOR_AIN_2_GPIO_PIN                                    GPIO_PIN_2

typedef enum
{
    Positive_Rotation = 0,
    Negative_Rotation,
} BCD_MOTOR_Direction;
void bcd_motor_init(void);
void bcd_motor_change_direction(BCD_MOTOR_Direction dir);
#endif
