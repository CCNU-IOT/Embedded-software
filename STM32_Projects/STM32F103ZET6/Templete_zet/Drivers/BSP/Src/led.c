#include "led.h"
void led_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();                        

    gpio_init_struct.Pin = LED_0_GPIO_PIN;                  
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            
    gpio_init_struct.Pull = GPIO_PULLUP;                    
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;         
    HAL_GPIO_Init(LED_0_GPIO_PORT, &gpio_init_struct);      

    gpio_init_struct.Pin = LED_1_GPIO_PIN;                  
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            
    gpio_init_struct.Pull = GPIO_PULLUP;                    
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;         
    HAL_GPIO_Init(LED_1_GPIO_PORT, &gpio_init_struct);

    led_set_status(LED_0_GPIO_PORT, LED_Close);
    led_set_status(LED_1_GPIO_PORT, LED_Close);
}
void led_set_status(GPIO_TypeDef *gpiox, LED_Status status)
{
    if (gpiox == LED_0_GPIO_PORT)
    {
        HAL_GPIO_WritePin(gpiox, GPIO_PIN_5, (GPIO_PinState)status);
    }
    else if (gpiox == LED_1_GPIO_PORT)
    {
        HAL_GPIO_WritePin(gpiox, GPIO_PIN_5, (GPIO_PinState)status);
    }
    
}
void breath_led_init(void)
{
    breath_led_pwm_init();
}

/**
  * @brief  实现LED呼吸灯。
  * @param  direction: 呼吸方向。
  *            该参数可取的值如下：
  *            @arg Breath_Positive: 呼吸方向为正向。
  *            @arg Breath_Positive: 呼吸方向为负向。
  * @param  duty: 占空比。
  * @retval None
  */
void breath_led_brightness(Breath_LED_Direction *direction, uint32_t *duty)
{
    // 如果呼吸方向为正向（Breath_Positive），则增加占空比
    if (*direction == Breath_Positive)
        (*duty)++;
    // 如果呼吸方向为负向（Breath_Negative），则减小占空比
    else if (*direction == Breath_Negative)
      (*duty)--;
	  // 如果占空比超过阈值（PWM_GENERAL_TIM_ARR），则将呼吸方向设置为负向
    if (*duty >= BREATH_LED_PWM_GENERAL_TIM_ARR)
      *direction = Breath_Negative; 
    // 如果占空比为零，则将呼吸方向设置为正向
    else if (!(*duty))
      *direction = Breath_Positive; 
    __HAL_TIM_SET_COMPARE(&breath_led_pwm_time_handle, BREATH_LED_PWM_GRNERAL_TIM_CHANNEL2, *duty);
}