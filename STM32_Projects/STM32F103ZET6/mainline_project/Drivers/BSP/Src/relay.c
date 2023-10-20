#include "relay.h"

void Relay_Init(void) {
    __HAL_RCC_GPIOB_CLK_ENABLE(); // ʹ��GPIOBʱ��
	GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = RELAY_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // �������ģʽ
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(RELAY_PORT, &GPIO_InitStruct);
    Relay_Off();
}

void Relay_On(void) {
    HAL_GPIO_WritePin(RELAY_PORT, RELAY_PIN, GPIO_PIN_SET);
}

void Relay_Off(void) {
    HAL_GPIO_WritePin(RELAY_PORT, RELAY_PIN, GPIO_PIN_RESET);
}
