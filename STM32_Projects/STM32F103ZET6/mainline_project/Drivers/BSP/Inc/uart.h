#ifndef __UART_H__
#define __UART_H__
#include "main.h"
#include "stdio.h"
#define UART_DEBUG                                          USART1
#define UART_DEBUG_TX_GPIO_PORT                             GPIOA
#define UART_DEBUG_TX_GPIO_PIN                              GPIO_PIN_9
#define UART_DEBUG_RX_GPIO_PORT                             GPIOA
#define UART_DEBUG_RX_GPIO_PIN                              GPIO_PIN_10
#define UART_DEBUG_RX_BUFFER_SIZE                           1U
#define UART_DEBUG_RX_PROTOCOL_BUFFER_SIZE                  200U
#define UART_DEBUG_LINE_FEED_FLAG                           0X0AU
#define UART_DEBUG_CARRIAGE_RETURN_FLAG                     0X0DU
#define UART_DEBUG_RX_PROTOCOL_BUFFER_COUNT                 (uart_debug_rx_status & 0X3FFF)
extern UART_HandleTypeDef uart_debug_handle;
extern uint8_t uart_debug_rx_buffer[UART_DEBUG_RX_BUFFER_SIZE];
extern uint8_t uart_debug_rx_protocol_buffer[UART_DEBUG_RX_PROTOCOL_BUFFER_SIZE];
extern uint16_t uart_debug_rx_status;

void uart_debug_init(uint32_t baudrate);
void uart_debug_tx_rxbuffer(uint16_t rxbuffer_size, uint32_t timeout);
uint8_t uart_debug_rx_complete(void);
#endif
