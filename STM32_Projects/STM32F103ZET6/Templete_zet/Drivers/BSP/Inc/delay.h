#ifndef __DELAY_H__
#define __DELAY_H__
#include "main.h"
void delay_init(uint16_t sysclk);       /* 初始化延迟函数 */
void delay_ms(uint16_t nms);            /* 延时nms */
void delay_us(uint32_t nus);            /* 延时nus */

#if (!SYS_SUPPORT_OS)                   /* 如果不支持OS */
    void HAL_Delay(uint32_t Delay);     /* HAL库的延时函数，HAL库内部用到 */
#endif

#endif /* __DELAY_H__ */





























