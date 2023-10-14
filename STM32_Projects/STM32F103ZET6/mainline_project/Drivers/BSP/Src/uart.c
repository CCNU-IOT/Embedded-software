#include "uart.h"

UART_HandleTypeDef uart_debug_handle;
uint8_t uart_debug_rx_buffer[UART_DEBUG_RX_BUFFER_SIZE] = {0};                          /*HAL库所使用的接收缓冲区*/
uint8_t uart_debug_rx_protocol_buffer[UART_DEBUG_RX_PROTOCOL_BUFFER_SIZE] = {0};        /*接收协议所使用的缓冲区*/
uint16_t uart_debug_rx_status = 0;                                                       /*接收协议标志位*/   

/******************************************************************************************/
/*定义以下代码，可以直接在工程中使用printf函数(前提是初始化USART1)*/
#ifndef UART_DEBUG_PRINTF
#define UART_DEBUG_PRINTF
#if (__ARMCC_VERSION >= 6010050)            
__asm(".global __use_no_semihosting\n\t"); 
__asm(".global __ARM_use_no_argv \n\t");   

#else

#pragma import(__use_no_semihosting)

struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

#endif
FILE __stdout;

int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

void _sys_exit(int x)
{
    x = x;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}

/**
 * @brief 重写fputc函数
*/
int fputc(int ch, FILE *f)
{
    
    while (__HAL_UART_GET_FLAG(&uart_debug_handle, UART_FLAG_TC) == RESET);/*TC标志位一直为0，说明上一个字节没有发送完*/    

    UART_DEBUG->DR = (uint8_t)ch;            
    return ch;
}
#endif /*UART_DEBUG_PRINTF*/
/******************************************************************************************/


/**
 * @brief USART1(UART_DEBUG)的初始化函数
*/
void uart_debug_init(uint32_t baudrate)
{
    uart_debug_handle.Instance = UART_DEBUG;
    uart_debug_handle.Init.BaudRate = baudrate;
    uart_debug_handle.Init.WordLength = UART_WORDLENGTH_8B;
    uart_debug_handle.Init.StopBits = UART_STOPBITS_1;
    uart_debug_handle.Init.Parity = UART_PARITY_NONE;
    uart_debug_handle.Init.Mode = UART_MODE_TX_RX;
    uart_debug_handle.Init.OverSampling = UART_OVERSAMPLING_16;
    uart_debug_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;

    HAL_UART_Init(&uart_debug_handle);

    HAL_UART_Receive_IT(&uart_debug_handle, uart_debug_rx_buffer, UART_DEBUG_RX_BUFFER_SIZE); /*收到1个字节的数据之后才会产生中断*/

}

/**
 * @brief UART初始化底层回调函数
*/
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef gpio_init_struct;
    if (huart->Instance == UART_DEBUG)
    {
        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_AFIO_CLK_ENABLE();

        gpio_init_struct.Pin = UART_DEBUG_TX_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                /*复用推挽输出*/
        gpio_init_struct.Pull = GPIO_PULLUP;                                    /*发送引脚需要设置成上拉，因为空闲输出高电平*/
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(UART_DEBUG_TX_GPIO_PORT, &gpio_init_struct);

        gpio_init_struct.Pin = UART_DEBUG_RX_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;                             /*复用推挽输入*/
        gpio_init_struct.Pull = GPIO_NOPULL;                                    /*输入引脚不需要设置上下拉*/
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                          /*输入引脚不需要设置速度，但是为了看起来好看一点，还是可以设置的(但是没用)*/
        HAL_GPIO_Init(UART_DEBUG_RX_GPIO_PORT, &gpio_init_struct);

        HAL_NVIC_SetPriority(USART1_IRQn, 3, 3);                                /*设置中断优先级*/
        HAL_NVIC_EnableIRQ(USART1_IRQn);                                        /*将中断号在NVIC处挂号*/

    }
}
/**
 * @brief USART1(UART_DEBUG)中断服务函数入口
*/
void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&uart_debug_handle);                                        /*该函数会将UART接收中断除能，因此要再次使能*/
    HAL_UART_Receive_IT(&uart_debug_handle, uart_debug_rx_buffer, UART_DEBUG_RX_BUFFER_SIZE);               /*使能UART接收完成中断*/
}

/**
 * @brief 协议接收函数
*/
void uart_debug_protocol_rx(void)
{
    if (!(uart_debug_rx_status & 0x8000)) /*接收未完成，在没有打印之前，不会再次接收任何字符*/
    {
        if ((uart_debug_rx_status & 0x4000)) /*0100 0000 0000 0000 已经接收到回车符*/
        {
            if (uart_debug_rx_buffer[0] == UART_DEBUG_LINE_FEED_FLAG) /*这次接收到的是换行符*/
            {
                uart_debug_rx_status |= 0x8000;      /*1100 0000 0000 0000 一次协议接收完成*/
            }
            else    /*接收到的不是换行符，那么接收错误，重新开始接收*/ 
            {
                uart_debug_rx_status = 0;
                /*接收协议所使用的缓冲区没必要清空，只需要重写即可，因为是按照接收长度取数组中的值*/
            }
        }
        else   /*还没有接收到回车符*/ 
        {
            if (uart_debug_rx_buffer[0] == UART_DEBUG_CARRIAGE_RETURN_FLAG) /*本次接收到回车符*/
            {
                uart_debug_rx_status |= 0x4000;   /*01xx xxxx xxxx xxxx*/
            }
            else if ((uart_debug_rx_buffer[0] == UART_DEBUG_LINE_FEED_FLAG) || (UART_DEBUG_RX_PROTOCOL_BUFFER_COUNT >= UART_DEBUG_RX_PROTOCOL_BUFFER_SIZE))   /*先接收到换行符或者超出了协议缓冲区的大小，接受错误，重新开始*/
            {
                uart_debug_rx_status = 0;
            }
            else 
            {
                uart_debug_rx_protocol_buffer[UART_DEBUG_RX_PROTOCOL_BUFFER_COUNT] = uart_debug_rx_buffer[0];
                uart_debug_rx_status++;
            }
        }
    }
}
/**
 * @brief UART接收完成中断回调函数
*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == UART_DEBUG)   /*接收到一个字节的数据*/
    {
        uart_debug_protocol_rx();
    }
}

/**
 * @brief 将接收缓冲区打印: 阻塞
*/
void uart_debug_tx_rxbuffer(uint16_t rxbuffer_size, uint32_t timeout)
{
    printf("rx_buffer is:\r\n");
    HAL_UART_Transmit(&uart_debug_handle, (uint8_t*)uart_debug_rx_protocol_buffer, rxbuffer_size, timeout);
    while (__HAL_UART_GET_FLAG(&uart_debug_handle, UART_FLAG_TC) != SET); /*等待发送完成*/
    printf("\r\n");
    uart_debug_rx_status = RESET;
}
/**
 * @brief 判断接收是否完成
 * @retval 1:接收完成
 *         0:接收未完成
*/
uint8_t uart_debug_rx_complete(void)
{
    return ((uart_debug_rx_status & 0x8000) != RESET);
}
