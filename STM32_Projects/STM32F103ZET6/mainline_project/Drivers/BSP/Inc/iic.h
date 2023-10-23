#ifndef __IIC_H__
#define __IIC_H__
#include "main.h"

void I2C_Init(void);
void I2C_set_SCL(uint8_t);
void I2C_set_SDA(uint8_t);
void I2C_Start(void);
void I2C_Stop(void);
// HAL_StatusTypeDef I2C_SendData(uint8_t address, uint8_t* data, uint16_t size);
// HAL_StatusTypeDef I2C_ReceiveData(uint8_t address, uint8_t* data, uint16_t size);

#endif /* __IIC_H__ */

