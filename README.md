# Embedded-software

<img src="https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/vsgif_com_lonely-spongebob-meme_.3422626.gif" alt="vsgif_com_lonely-spongebob-meme_.3422626"  />

## STM32F103ZET6：

#### 1. 定时器原理图分配：

- **TIM1——高级定时器**：

  - **TIM1_CH1  <---------->  PA8**
    - 同时，**USART1_CLK**会使用**PA8**。

  - **TIM1_CH2  <---------->  PA9**
    - 同时，USART1_TX会使用PA9。
  - **TIM1_CH3  <----------> PA10**
    - 同时，**USART1_RX**会使用**PA10**。

  - **TIM1_CH4  <---------->  PA11**
    - 同时，**CAN_RX/USB D-**会使用**PA11**。

  - **TIM1_ETR  <---------->  PA12**
    - 同时，**CAN_TX/USB D+**会使用**PA12**。

- **TIM2——通用定时器**：
  - **TIM2_CH1  <----------> PA0**
    - 同时，**WK_UP/TIM5_CH1/TIM2_ETR/TIM8_ETR**会使用**PA0**。
  - **TIM2_CH2  <---------->  PA1**
    - 同时，TIM5_CH2会使用PA1。
  - **TIM2_CH3  <----------> PA2**
    - 同时，**TIM5_CH3/USART2_TX**会使用**PA2**。
  - **TIM2_CH4  <---------->  PA3**
    - 同时，**TIM5_CH4/USART2_RX**会使用**PA3**。
  - 合着TIM2和TIM5只有一个能用是吧，STM32你真是可以:ok_man:。
