#ifndef __ADC_H__
#define __ADC_H__
#include "main.h"

void ADC_Init(void);
uint16_t ADC_Read(uint32_t channel);

#endif /*__ADC_H__*/
