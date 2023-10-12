#ifndef __UART_H__
#define __UART_H__
#include "main.h"

#define UART_DEBUG_BAUDRATE                                 115200U
#define UART_DEBUG                                          USART1
#define UART_DEBUG_TX_GPIO_PORT                             GPIOA
#define UART_DEBUG_TX_GPIO_PIN                              GPIO_PIN_9
#define UART_DEBUG_RX_GPIO_PORT                             GPIOA
#define UART_DEBUG_RX_GPIO_PIN                              GPIO_PIN_10
#endif