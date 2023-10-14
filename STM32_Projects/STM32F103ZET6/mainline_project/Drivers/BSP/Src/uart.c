#include "uart.h"
#if 1

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


FILE __stdout;

int fputc(int ch, FILE *f)
{
    while ((UART_DEBUG->SR & 0X40) == 0);    

    UART_DEBUG->DR = (uint8_t)ch;            
    return ch;
}
#endif
/******************************************************************************************/


UART_HandleTypeDef uart_debug_handle;
uint8_t uart_debug_rx_buffer[1] = {0};        /*串口接收缓冲区*/
uint8_t uart_debug_rx_flag = RESET;         
void uart_debug_init(void)
{
    uart_debug_handle.Instance = UART_DEBUG;
    uart_debug_handle.Init.BaudRate = 115200;
    uart_debug_handle.Init.WordLength = UART_WORDLENGTH_8B;
    uart_debug_handle.Init.StopBits = UART_STOPBITS_1;
    uart_debug_handle.Init.Parity = UART_PARITY_NONE;
    uart_debug_handle.Init.Mode = UART_MODE_TX_RX;
    uart_debug_handle.Init.OverSampling = UART_OVERSAMPLING_16;
    uart_debug_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;

    HAL_UART_Init(&uart_debug_handle);

    HAL_UART_Receive_IT(&uart_debug_handle, uart_debug_rx_buffer, 1); /*这里有一个疑问：关于接收缓冲区的大小，是否是当缓冲区满了的时候才会触发中断吗，目前觉得不是这样的*/

}
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef gpio_init_struct;
    if (huart->Instance == UART_DEBUG)
    {
        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_AFIO_CLK_ENABLE();

        gpio_init_struct.Pin = UART_DEBUG_TX_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;            /*复用推挽输出*/
        gpio_init_struct.Pull = GPIO_PULLUP;                /*F1系列在发送的时候不能设置上下拉*/
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(UART_DEBUG_TX_GPIO_PORT, &gpio_init_struct);

        gpio_init_struct.Pin = UART_DEBUG_RX_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;         /*复用推挽输入*/
        gpio_init_struct.Pull = GPIO_NOPULL;                /*空闲的时候是高电平，因此上拉*/
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;      /*输入引脚不需要设置速度，但是为了看起来好看一点，还是可以设置的(但是没用)*/
        HAL_GPIO_Init(UART_DEBUG_RX_GPIO_PORT, &gpio_init_struct);

        HAL_NVIC_SetPriority(USART1_IRQn, 3, 3);                             /*设置中断优先级*/
        HAL_NVIC_EnableIRQ(USART1_IRQn);                                     /*将中断号在NVIC处挂号*/

    }
}
void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&uart_debug_handle);                                        /*该函数会将UART接收中断除能，因此要再次使能*/
    HAL_UART_Receive_IT(&uart_debug_handle, uart_debug_rx_buffer, 1);
}
/**
 * @brief UART接收完成中断回调函数
*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == UART_DEBUG)
    {
        uart_debug_rx_flag = SET; /*接收到数据*/
    }
}
