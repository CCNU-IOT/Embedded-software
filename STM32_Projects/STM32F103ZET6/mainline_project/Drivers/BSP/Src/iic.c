#include "iic.h"

I2C_HandleTypeDef hi2c;
GPIO_InitTypeDef GPIO_InitStruct;

void I2C_Init() 
{
    __HAL_RCC_GPIOB_CLK_ENABLE(); // 使能GPIOB时钟（即SCL、SDA引脚时钟）
    
    GPIO_InitStruct.Pin = GPIO_PIN_6;// SCL引脚
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // 开漏输出模式
    GPIO_InitStruct.Pull = GPIO_PULLUP; // 上拉
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH; // 高速
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7;// SDA引脚
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD; // 开漏输出模式
    GPIO_InitStruct.Pull = GPIO_PULLUP; // 上拉
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH; // 高速
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    hi2c.Instance = I2C1;
    hi2c.Init.ClockSpeed = 400000; // 设置 I2C 总线速度为 400 kHz
    hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;// 配置 I2C 时钟占空比为 2
    hi2c.Init.OwnAddress1 = 0;// 配置 I2C 本机地址
    hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;// 配置 I2C 地址模式为 7 位地址模式
    hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;// 禁用 I2C 双地址模式
    hi2c.Init.OwnAddress2 = 0;// 配置 I2C 第二本机地址
    hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;// 禁用 I2C 广播地址模式
    hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;// 禁用 I2C 时钟拉伸
    HAL_I2C_Init(&hi2c);
    HAL_Delay(100); 
}

/**
 * @brief       设置时钟线SCL的电平
 * @param       i: 1-高电平；0-低电平
 * @retval      无
 */
void I2C_set_SCL(uint8_t i) 
{   i?
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET):
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET); 
}

/**
 * @brief       设置数据线SDA的电平
 * @param       i: 1-高电平；0-低电平
 * @retval      无
 */                        
void I2C_set_SDA(uint8_t i) 
{   i?
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET):
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET); 
}

void I2C_Start(void)
{
    I2C_set_SDA(1);
    I2C_set_SCL(1);   
    HAL_Delay(1);
    I2C_set_SDA(0);
    HAL_Delay(1);
    I2C_set_SCL(0);
    HAL_Delay(1);
}

void I2C_Stop(void)
{
    I2C_set_SDA(0);
    HAL_Delay(1);
    I2C_set_SCL(1);
    HAL_Delay(1);
    I2C_set_SDA(1);
    HAL_Delay(1);
}

// HAL_StatusTypeDef I2C_SendData(uint8_t address, uint8_t* data, uint16_t size)
// {
//     return HAL_I2C_Master_Transmit(&hi2c, address, data, size, HAL_MAX_DELAY);
// }

// HAL_StatusTypeDef I2C_ReceiveData(uint8_t address, uint8_t* data, uint16_t size)
// {
//     return HAL_I2C_Master_Receive(&hi2c, address, data, size, HAL_MAX_DELAY);
// }
