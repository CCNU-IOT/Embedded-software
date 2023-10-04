#ifndef __KEY_H__
#define __KEY_H__
#include "main.h"
#define KEY_PIN             GPIO_PIN_0
#define KEY_PORT            GPIOA

void key_init(void);
uint8_t key_pressed(void);

#endif /* __KEY_H__ */