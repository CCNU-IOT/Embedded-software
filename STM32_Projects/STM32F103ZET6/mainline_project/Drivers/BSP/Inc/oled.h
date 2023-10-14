#ifndef __OLED_H__
#define __OLED_H__
#include "main.h"

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

void OLED_Init(void);
void OLED_DisplayOn(void);
void OLED_DisplayOff(void);
void OLED_DisplayChar(uint8_t x, uint8_t y, char ch);


#endif /* __OLED_H__ */
