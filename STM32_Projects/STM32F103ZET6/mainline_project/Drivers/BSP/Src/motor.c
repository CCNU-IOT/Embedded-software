#include "motor.h"
BCD_MOTOR_InitTypeDef bcd_motor_init_struct;
void bcd_motor_init(uint32_t duty)
{
    bcd_motor_init_struct.speed = 0.00;
    bcd_motor_init_struct.reduction_ratio = 30;
    GPIO_InitTypeDef gpio_init_struct;//创建GPIO初始化结构体
    __HAL_RCC_GPIOG_CLK_ENABLE();

    gpio_init_struct.Pin = BCD_MOTOR_AIN_1_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;           /* GPIO输出 */
    gpio_init_struct.Pull = GPIO_NOPULL;               /**/
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;     /*高速*/
    HAL_GPIO_Init(BCD_MOTOR_AIN_1_GPIO_PORT, &gpio_init_struct);//初始化GPIOG1端口

    gpio_init_struct.Pin = BCD_MOTOR_AIN_2_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;           /* GPIO输出 */
    gpio_init_struct.Pull = GPIO_NOPULL;               /**/
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;     /*高速*/
    HAL_GPIO_Init(BCD_MOTOR_AIN_2_GPIO_PORT, &gpio_init_struct);//初始化GPIOG2端口
    bcd_motor_change_direction(Negative_Rotation);

    brushed_dc_motor_pwm_init(duty);
}
void bcd_motor_change_direction(BCD_MOTOR_Direction dir)
{
    if (dir == Positive_Rotation)
    {
        HAL_GPIO_WritePin(BCD_MOTOR_AIN_1_GPIO_PORT, BCD_MOTOR_AIN_1_GPIO_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(BCD_MOTOR_AIN_2_GPIO_PORT, BCD_MOTOR_AIN_2_GPIO_PIN, GPIO_PIN_RESET);
    }
    else if (dir == Negative_Rotation)
    {
        HAL_GPIO_WritePin(BCD_MOTOR_AIN_1_GPIO_PORT, BCD_MOTOR_AIN_1_GPIO_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(BCD_MOTOR_AIN_2_GPIO_PORT, BCD_MOTOR_AIN_2_GPIO_PIN, GPIO_PIN_SET);
    }
}
