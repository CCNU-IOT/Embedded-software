#ifndef __BTIM_H__
#define __BTIM_H__
#include "main.h"

void TIM6_init(uint16_t arr, uint16_t psc);
uint32_t getCurrentTime(void);

#endif /*__BTIM_H__*/
