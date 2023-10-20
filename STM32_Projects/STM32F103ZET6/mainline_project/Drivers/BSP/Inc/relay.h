#ifndef __RELAY_H__
#define __RELAY_H__
#include "main.h"

#define RELAY_PIN   GPIO_PIN_7
#define RELAY_PORT  GPIOB

void Relay_Init(void);
void Relay_On(void);
void Relay_Off(void);

#endif /* __RELAY_H__ */

