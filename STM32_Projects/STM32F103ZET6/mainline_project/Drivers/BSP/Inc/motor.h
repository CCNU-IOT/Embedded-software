#ifndef __MOTOR_H__
#define __MOTOR_H__
#include "main.h"
#include "pwm.h"
typedef struct 
{
  uint8_t state;                        /*电机状态*/
  float current;                        /*电机电流*/
  float volatage;                       /*电机电压*/
  float power;                          /*电机功率*/
  float speed;                          /*电机实际速度*/
  int32_t motor_pwm;                    /*设置比较值大小 */
  uint8_t reduction_ratio;              /*设置电机的减速比*/
} BCD_MOTOR_InitTypeDef;
typedef enum
{
    Positive_Rotation = 0,
    Negative_Rotation,
} BCD_MOTOR_Direction;

#define BCD_MOTOR_AIN_1_GPIO_PORT                                   GPIOG
#define BCD_MOTOR_AIN_1_GPIO_PIN                                    GPIO_PIN_1
#define BCD_MOTOR_AIN_2_GPIO_PORT                                   GPIOG
#define BCD_MOTOR_AIN_2_GPIO_PIN                                    GPIO_PIN_2

void bcd_motor_init(void);
void bcd_motor_change_direction(BCD_MOTOR_Direction dir);

extern BCD_MOTOR_InitTypeDef bcd_motor_init_struct;
#endif
