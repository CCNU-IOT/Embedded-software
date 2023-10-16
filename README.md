# Embedded-software

<img src="https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/vsgif_com_lonely-spongebob-meme_.3422626.gif" alt="vsgif_com_lonely-spongebob-meme_.3422626"  />

## STM32F103ZET6：

#### 1. 定时器原理图分配：

- **TIM1——高级定时器**：

  - **TIM1_CH1  <---------->  PA8**
    - 同时，**USART1_CLK**会使用**PA8**。

  - **TIM1_CH2  <---------->  PA9**
    - 同时，**USART1_TX**会使用**PA9**。
  - **TIM1_CH3  <----------> PA10**
    - 同时，**USART1_RX**会使用**PA10**。

  - **TIM1_CH4  <---------->  PA11**
    - 同时，**CAN_RX/USB D-**会使用**PA11**。

  - **TIM1_ETR  <---------->  PA12**
    - 同时，**CAN_TX/USB D+**会使用**PA12**。
  - **TIM1_BKIN  <---------->  PB12**
    - 同时，**USART3_CLK**会使用**PB12**。
  - **TIM1_CH1N  <---------->  PB13**
    - 同时，**USART3_CTS**会使用**PB13**。
  - **TIM1_CH2N  <---------->  PB14**
    - 同时，**USART3_RTS**会使用**PB13**。
  - **TIM1_CH3N  <---------->  PB15**

- **TIM2——通用定时器**：

  - **TIM2_CH1  <----------> PA0**
    - 同时，**WK_UP/TIM5_CH1/TIM2_ETR/TIM8_ETR**会使用**PA0**。
  - **TIM2_CH2  <---------->  PA1**
    - 同时，**TIM5_CH2**会使用**PA1**。
  - **TIM2_CH3  <----------> PA2**
    - 同时，**TIM5_CH3/USART2_TX**会使用**PA2**。
  - **TIM2_CH4  <---------->  PA3**
    - 同时，**TIM5_CH4/USART2_RX**会使用**PA3**。
  - **TIM2_ETR  <---------->  PA0**
    - 不多说......
  - 合着TIM2和TIM5只有一个能用是吧，STM32你真是可以:ok_man:。

- **TIM3——通用定时器**：

  - **TIM3_CH1  <---------->  PA6**
    - 同时，**TIM8_BKIN**会使用**PA6**。
  - **TIM3_CH2  <---------->  PA7**
    - 同时，**TIM8_CH1N**会使用**PA7**。
  - **TIM3_CH3  <---------->  PB0**
    - 同时，**TIM8_CH2**会使用**PB0**。

  - **TIM3_CH4  <---------->  PB1**
    - 同时，**TIM8_CH3**会使用**PB1**。
  - **TIM3_ETR  <---------->  PD2**
    - 同时**UART_RX**会使用**PD2**。

- **TIM4——通用定时器**：

  - **TIM4_CH1  <---------->  PB6**
  - **TIM4_CH2  <---------->  PB7**
  - **TIM4_CH3  <---------->  PB8**
  - **TIM4_CH4  <---------->  PB9**
  - **TIM4_ETR  <---------->  PE0**

- **TIM5——通用定时器**：

  - **TIM2_CH1  <----------> PA0**
  - **TIM2_CH2  <---------->  PA1**
  - **TIM2_CH3  <----------> PA2**
  - **TIM2_CH4  <---------->  PA3**

- **TIM8——高级定时器**：

  - **TIM8_CH1  <---------->  PC6**
  - **TIM8_CH2  <---------->  PC7**
  - **TIM8_CH3  <---------->  PC8**
  - **TIM8_CH4  <---------->  PC9**
  - **TIM8_CH1N  <---------->  PA7**
    - 同时，**TIM3_CH2**使用**PA7**。
  - **TIM8_CH2N  <---------->  PB0**
    - 同时，**TIM3_CH3**使用**PB0**。

  - **TIM8_CH3N  <---------->  PB1**
    - 同时，**TIM3_CH4**使用**PB1**。
