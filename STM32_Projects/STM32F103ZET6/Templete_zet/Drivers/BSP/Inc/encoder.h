#ifndef __ENCODER_H__
#define __ENCODER_H__
#include "main.h"
#include "motor.h"
typedef struct 
{
    int32_t encode_num_old;                  /* 上一次计数值 */
    int32_t encode_num_now;                  /* 当前计数值 */
    float speed;                             /* 编码器速度 */
    uint8_t resolution;                      /* 编码器经过定时器放大后的分辨率 */
} Encoder_InitTypeDef;

/*TIM3 -> encoder*/
#define ENCODER_GENERAL_TIM                                     TIM4
#define ENCODER_GENERAL_TIM_PSC                                 0
#define ENCODER_GENERAL_TIM_ARR                                 65535
#define ENCODER_GENERAL_TIM_CHANNEL_1                           TIM_CHANNEL_1
#define ENCODER_GENERAL_TIM_CHANNEL_2                           TIM_CHANNEL_2
#define ENCODER_GENERAL_TIM_CHANNEL_1_GPIO_PORT                 GPIOB
#define ENCODER_GENERAL_TIM_CHANNEL_1_GPIO_PIN                  GPIO_PIN_6
#define ENCODER_GENERAL_TIM_CHANNEL_2_GPIO_PORT                 GPIOB
#define ENCODER_GENERAL_TIM_CHANNEL_2_GPIO_PIN                  GPIO_PIN_7

/*TIM6 -> encoder_count*/
#define ENCODER_BASE_TIM                                        TIM6
#define ENCODER_BASE_TIM_PSC                                    (72U - 1U)/*1MHz <---> 1us*/
#define ENCODER_BASE_TIM_ARR                                    (1000U - 1U) /*1KHz <---> 1ms*/

void encoder_base_tim_init(void);
void bcd_encoder_init(void);
int32_t encoder_tim_get_encode_num(void);
void calculate_bcd_speed(int32_t encode_num_now);
void meger_sort(float array[], uint8_t start, uint8_t tail);
void meger(float array[], float asso_array[], uint8_t start, uint8_t mid, uint8_t tail);
float first_order_low_pass_filter(float motor_speed_now, float motor_speed_old);

extern Encoder_InitTypeDef encoder_init_struct;
#endif
