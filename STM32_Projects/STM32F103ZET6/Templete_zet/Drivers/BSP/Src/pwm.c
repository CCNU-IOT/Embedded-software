#include "pwm.h"
TIM_HandleTypeDef pwm_time_handle;
void pwm_init(void)
{
    TIM_OC_InitTypeDef tim_oc_init_struct;

    pwm_time_handle.Instance = PWM_GENERAL_TIM;
    pwm_time_handle.Init.Prescaler = PWM_GENERAL_TIM_PSC;
    pwm_time_handle.Init.Period = PWM_GENERAL_TIM_ARR;
    pwm_time_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    pwm_time_handle.Init.AutoReloadPreload = TIM_AUTOMATICOUTPUT_ENABLE;

    HAL_TIM_PWM_Init(&pwm_time_handle);

    tim_oc_init_struct.OCMode = TIM_OCMODE_PWM1;
    tim_oc_init_struct.Pulse = PWM_GENERAL_TIM_DUTY;
    tim_oc_init_struct.OCNPolarity = TIM_OCNPOLARITY_LOW;

    HAL_TIM_PWM_ConfigChannel(&pwm_time_handle, &tim_oc_init_struct, PWM_GRNERAL_TIM_CHANNEL2);
    HAL_TIM_PWM_Start(&pwm_time_handle, PWM_GRNERAL_TIM_CHANNEL2);
}
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == PWM_GENERAL_TIM)
    {
        GPIO_InitTypeDef gpio_init_struct;//创建GPIO初始化结构体
        __HAL_RCC_GPIOB_CLK_ENABLE();//TIM3->Channel2对应GPIOB5，开启GPIOB时钟
        __HAL_RCC_TIM3_CLK_ENABLE();//开启TIM3时钟
        
        gpio_init_struct.Pin = PWM_GENERAL_TIM_CHANNEL2_GPIO_PIN; /* 通道y的CPIO口 */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;           /* 复用推挽输出,这里作为TIM3的CH2输出，因此是复用 */
        gpio_init_struct.Pull = GPIO_PULLUP;               /* 上拉,LED灯上拉熄灭 */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;     /* 高速 */
        HAL_GPIO_Init(PWM_GENERAL_TIM_CHANNEL2_GPIO_PORT, &gpio_init_struct);//初始化GPIOB5端口
        
        /*TIM3通道重映射，具体参考定时器文章*/
        __HAL_RCC_AFIO_CLK_ENABLE();//打开AFIO时钟
        __HAL_AFIO_REMAP_TIM3_PARTIAL();//部分重映射TIM3的通道
    }
}
