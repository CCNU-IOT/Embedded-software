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
  * @brief  Set the TIM Capture Compare Register value on runtime without calling another time ConfigChannel function.
  * @param  __HANDLE__ TIM handle.
  * @param  __CHANNEL__ TIM Channels to be configured.
  *          This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
  *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
  *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
  *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
  * @param  __COMPARE__ specifies the Capture Compare register new value.
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

    if (*duty >= BREATH_LED_PWM_GENERAL_TIM_ARR)
      *direction = Breath_Negative; 
    else if (!(*duty))
      *direction = Breath_Positive; 
    __HAL_TIM_SET_COMPARE(&breath_led_pwm_time_handle, BREATH_LED_PWM_GRNERAL_TIM_CHANNEL2, *duty);
}