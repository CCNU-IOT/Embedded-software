#ifndef __RELAY_H__
#define __RELAY_H__
#include "main.h"

//使用PE0引脚接继电器的信号触发端
#define RELAY_PIN   GPIO_PIN_0
#define RELAY_PORT  GPIOE

void Relay_Init(void);
void Relay_On(void);
void Relay_Off(void);

#endif /* __RELAY_H__ */

