#include "relay.h"

void Relay_Init(void) {
    __HAL_RCC_GPIOE_CLK_ENABLE(); // 使能GPIOE时钟
	GPIO_InitTypeDef gpio_init_struct;
    gpio_init_struct.Pin = RELAY_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP; // 推挽输出模式
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(RELAY_PORT, &gpio_init_struct);
    Relay_Off();
}

void Relay_On(void) {
    HAL_GPIO_WritePin(RELAY_PORT, RELAY_PIN, GPIO_PIN_RESET);
}

void Relay_Off(void) {
    HAL_GPIO_WritePin(RELAY_PORT, RELAY_PIN, GPIO_PIN_SET);
}
