#ifndef __DELAY_H__
#define __DELAY_H__
#include "main.h"
void delay_init(uint16_t sysclk);       /* ��ʼ���ӳٺ��� */
void delay_ms(uint16_t nms);            /* ��ʱnms */
void delay_us(uint32_t nus);            /* ��ʱnus */

#if (!SYS_SUPPORT_OS)                   /* �����֧��OS */
    void HAL_Delay(uint32_t Delay);     /* HAL�����ʱ������HAL���ڲ��õ� */
#endif

#endif /* __DELAY_H__ */





























