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
}
void breath_led_init(void)
{
    led_init();
    pwm_init();
}
void breath_led_brightness(uint32_t duty)
{
    __HAL_TIM_SET_COMPARE(&pwm_time_handle, PWM_GRNERAL_TIM_CHANNEL2, duty);
}
