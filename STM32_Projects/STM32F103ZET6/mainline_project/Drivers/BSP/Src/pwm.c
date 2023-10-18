#include "pwm.h"
TIM_HandleTypeDef breath_led_pwm_time_handle;
TIM_HandleTypeDef brushed_dc_motor_pwm_time_handle;
void breath_led_pwm_init(void)
{
    TIM_OC_InitTypeDef tim_oc_init_struct;

    breath_led_pwm_time_handle.Instance = BREATH_LED_PWM_GENERAL_TIM;
    breath_led_pwm_time_handle.Init.Prescaler = BREATH_LED_PWM_GENERAL_TIM_PSC;
    breath_led_pwm_time_handle.Init.Period = BREATH_LED_PWM_GENERAL_TIM_ARR;
    breath_led_pwm_time_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    breath_led_pwm_time_handle.Init.AutoReloadPreload = TIM_AUTOMATICOUTPUT_ENABLE;

    HAL_TIM_PWM_Init(&breath_led_pwm_time_handle);

    tim_oc_init_struct.OCMode = TIM_OCMODE_PWM1;
    tim_oc_init_struct.Pulse = BREATH_LED_PWM_GENERAL_TIM_DUTY;
    tim_oc_init_struct.OCNPolarity = TIM_OCNPOLARITY_LOW;

    HAL_TIM_PWM_ConfigChannel(&breath_led_pwm_time_handle, &tim_oc_init_struct, BREATH_LED_PWM_GRNERAL_TIM_CHANNEL2);
    HAL_TIM_PWM_Start(&breath_led_pwm_time_handle, BREATH_LED_PWM_GRNERAL_TIM_CHANNEL2);
}
/**
 * @brief 初始化直流无刷电机
 * @param duty:PWM的占空比，用于控制转速(范围0 ~ 99)
*/
void brushed_dc_motor_pwm_init(uint32_t duty)   
{
    TIM_OC_InitTypeDef tim_oc_init_struct;

    brushed_dc_motor_pwm_time_handle.Instance = BRUSHED_DC_MOTOR_PWM_GENERAL_TIM;
    brushed_dc_motor_pwm_time_handle.Init.Prescaler = BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_PSC;
    brushed_dc_motor_pwm_time_handle.Init.Period = BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_ARR;
    brushed_dc_motor_pwm_time_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    brushed_dc_motor_pwm_time_handle.Init.AutoReloadPreload = TIM_AUTOMATICOUTPUT_ENABLE;

    HAL_TIM_PWM_Init(&brushed_dc_motor_pwm_time_handle);

    tim_oc_init_struct.OCMode = TIM_OCMODE_PWM1;
    tim_oc_init_struct.Pulse = duty;
    tim_oc_init_struct.OCNPolarity = TIM_OCNPOLARITY_HIGH;

    HAL_TIM_PWM_ConfigChannel(&brushed_dc_motor_pwm_time_handle, &tim_oc_init_struct, BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL1);
    HAL_TIM_PWM_ConfigChannel(&brushed_dc_motor_pwm_time_handle, &tim_oc_init_struct, BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL2);
    HAL_TIM_PWM_ConfigChannel(&brushed_dc_motor_pwm_time_handle, &tim_oc_init_struct, BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL3);
    HAL_TIM_PWM_ConfigChannel(&brushed_dc_motor_pwm_time_handle, &tim_oc_init_struct, BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL4);
    HAL_TIM_PWM_Start(&brushed_dc_motor_pwm_time_handle, BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL1);
    HAL_TIM_PWM_Start(&brushed_dc_motor_pwm_time_handle, BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL2);
    HAL_TIM_PWM_Start(&brushed_dc_motor_pwm_time_handle, BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL3);
    HAL_TIM_PWM_Start(&brushed_dc_motor_pwm_time_handle, BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL4);
}
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == BREATH_LED_PWM_GENERAL_TIM)
    {
        GPIO_InitTypeDef gpio_init_struct;//创建GPIO初始化结构体
        __HAL_RCC_GPIOB_CLK_ENABLE();//TIM3->Channel2对应GPIOB5，开启GPIOB时钟
        __HAL_RCC_TIM3_CLK_ENABLE();//开启TIM3时钟
        
        gpio_init_struct.Pin = BREATH_LED_PWM_GENERAL_TIM_CHANNEL2_GPIO_PIN; /* 通道y的CPIO口 */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;           /* 复用推挽输出,这里作为TIM3的CH2输出，因此是复用 */
        gpio_init_struct.Pull = GPIO_PULLUP;               /* 上拉,LED灯上拉熄灭 */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;     /* 高速 */
        HAL_GPIO_Init(BREATH_LED_PWM_GENERAL_TIM_CHANNEL2_GPIO_PORT, &gpio_init_struct);//初始化GPIOB5端口
        
        /*TIM3通道重映射，具体参考定时器文章*/
        __HAL_RCC_AFIO_CLK_ENABLE();//打开AFIO时钟
        __HAL_AFIO_REMAP_TIM3_PARTIAL();//部分重映射TIM3的通道
    }
    else if (htim->Instance == BRUSHED_DC_MOTOR_PWM_GENERAL_TIM)
    {
        GPIO_InitTypeDef gpio_init_struct;//创建GPIO初始化结构体
        __HAL_RCC_GPIOA_CLK_ENABLE();//TIM4->all_Channel对应GPIOB，开启GPIOB时钟
        __HAL_RCC_TIM2_CLK_ENABLE();//开启TIM4时钟

        gpio_init_struct.Pin = BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL1_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;           /* 复用推挽输出,这里作为TIM4的CH输出，因此是复用 */
        gpio_init_struct.Pull = GPIO_NOPULL;               /*暂时使用上拉*/
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;     /*高速*/
        HAL_GPIO_Init(BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL1_GPIO_PORT, &gpio_init_struct);//初始化GPIOB5端口

        gpio_init_struct.Pin = BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL2_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;           /* 复用推挽输出,这里作为TIM4的CH输出，因此是复用 */
        gpio_init_struct.Pull = GPIO_NOPULL;               /*暂时使用上拉*/
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;     /*高速*/
        HAL_GPIO_Init(BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL2_GPIO_PORT, &gpio_init_struct);//初始化GPIOB5端口

        gpio_init_struct.Pin = BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL3_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;           /* 复用推挽输出,这里作为TIM4的CH输出，因此是复用 */
        gpio_init_struct.Pull = GPIO_PULLUP;               /*暂时使用上拉*/
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;     /*高速*/
        HAL_GPIO_Init(BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL3_GPIO_PORT, &gpio_init_struct);//初始化GPIOB5端口
        
        gpio_init_struct.Pin = BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL4_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;           /* 复用推挽输出,这里作为TIM4的CH输出，因此是复用 */
        gpio_init_struct.Pull = GPIO_PULLUP;               /*暂时使用上拉*/
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;     /*高速*/
        HAL_GPIO_Init(BRUSHED_DC_MOTOR_PWM_GENERAL_TIM_CHANNEL4_GPIO_PORT, &gpio_init_struct);//初始化GPIOB5端口
    }
}