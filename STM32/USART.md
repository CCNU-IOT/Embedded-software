# USART

作者：嵌入式软件:pen:

## 1.串口：

#### 1.1 什么是串口:frowning:：

- **串行通信接口——serial communication port**，简称**serial port**。
- **广义**的串口:sake:：
  - 符合串行通信的接口，例如**RS-232**、**USB**、**IIC**等......
- **狭义**的串口:dart:：
  - 符合**RS-232/RS-422/RS-485标准**的硬件接口。
    - 其中**RS-232**接口是**标准串口**。

#### 1.2 RS-232:artificial_satellite:：

- 在**计算机通信**、**单片机通信**领域，串口指的是**RS-232**标准接口。
  - 下图是早期**PC**机上常见的**COM口**(**RS-232**接口)，采用的是**DB9**格式。
  - <img src="https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/800px-Serial_port_(9-pin).jpg" alt="800px-Serial_port_(9-pin)" style="zoom:50%;" />

- **RS-232电平标准**：
  - **逻辑电平1**：-15V ~ -3V:santa:
  - **逻辑电平0**：+3V ~ +15V:face_with_head_bandage:
  - **RS-232电平**标准与**TTL/COMS电平**标准有着明显的差异：
    - **TTL电平**：
      - **TTL——Transistor Transistor Logic**，即**晶体管—晶体管逻辑**，是一种**数字电路标准**，使用**双极型晶体管(BJT)**作为基本元件，**TTL电路**在过去的几十年非常流行，但目前已被替代。
      - **逻辑电平1**：+4.75V ~ +5.25V:dancer:
      - **逻辑电平0**：0V
    - **COMS电平**：
      - **CMOS——Complementary Metal-Oxide-Semiconductor**，即**互补金属氧化物半导体**，是一种**数字电路标准**，使用**绝缘栅型场效应管(MOSFET)**作为基本元件，**CMOS电路**目前在数字电子领域得到广泛应用。
      - **逻辑电平1**：+3.3V或+5V:badminton:
      - **逻辑电平0**：0V
      - **STM32微处理器采用的就是CMOS电路标准。**
- **RS-232接口通信过程**：
  - ![image-20231010193218805](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/image-20231010193218805.png)
    - 常见的**电平转换芯片**：**MAX232**、**MAX3232**......
- **RS-232通信协议**：
  - **RS-232**规定了接口的**机械特性**、**电气特性**、**信号功能**:ice_cream:。
    - 但我们会发现，**RS-232**并没有规定通信协议，这是因为**RS-232**属于**物理层**的概念，而**通信协议**属于**数据链路层**的概念。
      - **数据链路层**之上同样有通信协议，只不过**数据链路层**是和**物理层**靠的最近的层级。
  - **异步启停编码**：
    - **异步启停编码**即是通信协议，在**串口通信**中，通常选择**异步启停**这种编码格式，这种格式通过**"帧"**实现:balloon:。
    - **数据帧格式**：
      - ![image-20231010200309788](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/image-20231010200309788.png)
      - **帧起始**：
        - **持续高电平**表示**空闲**，当数据线处于空闲状态的时候，**拉低1bit**产生**起始位**，表示数据帧的开始。
      - **帧数据**：
        - 起始位后面的**5 ~ 9bit**表示**数据位**，**LSB**表示**最低有效位(D0)**，**MSB**表示**最高有效位(D7)**，**LSB**在前，**MSB**在后。
          - 通常来讲，数据位为**8bit**，这样可以表示**1byte**数据。
      - **帧校验**：
        - 数据位后面的**1bit**表示**校验位**(也可以选择不进行帧校验，即没有校验位)。
          - 帧校验采用**奇偶校验**。
      - **帧停止**：
        - 校验位(如果没有校验，就是数据位)后面的**1/1.5/2bit**的**高电平**表示**停止位**，停止位是**一帧数据**传输结束的标志。
- **USB接口通信过程**：
  - 目前，计算机基本上裁剪掉了**RS-232接口**，取而代之的是**USB接口**，因此需要清楚**USB接口**的通信过程。
  - ![image-20231010215754084](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/image-20231010215754084.png)
    - 常见的电平转换芯片是：**CH340C**......
    - 为了在**PC机**上能够正常通信，需要安装**CH340驱动**(目的是挂载**CH340芯片**的信息)。
    - 虽然将**RS-232接口**换成了**USB接口**，但依旧是**串行通信**，即支持**异步启停**编码格式。
    - <img src="https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/OIP.jpeg" alt="OIP" style="zoom: 67%;" />

## 2.USART：

#### 2.1 USART/UART介绍：

- **USART——Universal Synchronous Asynchronous Receiver Transmitter**，通用同步异步收发器。
- **UART——Universal Asynchronous Receiver/Transmitter**，通用异步收发器。

- **USART**相较于**UART**多了**同步**功能，我们使用的通信协议一般是**异步启停**，因此使用**UART**即可。
- **USART/UART**是计算机体系结构中的一部分，用于连接**串行通信接口**(也就是串口)，通常作为微处理器的**外围设备(peripheral)**，**USART/UART**的接口通常与**MAX232/CH340**等电平转换芯片相连，**USART/UART**作为微处理器**对外通信**的接口。

- <img src="https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/UART_8250_Microchip.jpg" alt="UART_8250_Microchip" style="zoom: 33%;" />
  - 上图是**美国国家半导体**设计的**UART-8250**芯片。

#### 2.2 STM32F103的U(S)ART简介：

- **STM32F103**有五个**U(S)ART**，其中三个**USART(兼容UART)**，两个**UART**。
  - 参考：[STM32选型手册](https://static.stmcu.com.cn/upload/Selection_Guide.pdf)
  - ![image-20231011203633080](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/image-20231011203633080.png)
- **U(S)ART主要特征**：
  - 参考：**STM32F10x英文参考手册**
    - ![image-20231011204545340](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/image-20231011204545340.png)
    - 支持**全双工异步**通信
    - 支持**单线半双工**通信
    - 具有单独的**发送器使能位**和**接收器使能位**
    - 可配置使用**DMA**
    - 可配置使用**中断**

#### 2.3 STM32F103U(S)ART结构框图：

- 该框图适用于**STM32F1**和**STM32F4**系列，我们以**STM32F1**为例：

- ![image-20230909151604790](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/image-20230909151604790.png)

- **第一部分——外部引脚**:dancers:：
  - **TX**：
    - 发送器引脚。
  - **RX**：
    - 接收器引脚。
  - **SW_RX**：
    - 芯片内部引脚，对外没有接口。
  - **nRTS、nCTS**：
    - 硬件数据流控引脚，和同步控制有关，如果使用异步控制，不需要配置。
  - **SCLK**：
    - 同步控制时钟引脚。

- **第二部分——数据寄存器**:face_with_head_bandage:：
  - **UART发送数据通路**：
    - **PWDATA**是UART的**写总线**，**PWDATA总线**可以通过**CPU或者DMA**的方式写入数据，总线上的数据会被直接写入到**数据寄存器DR**中(**发送数据寄存器TDR**对用户不可见)。
    - 由于执行的是写入操作，因此**数据寄存器DR**中的数据会被写入到**发送数据寄存器TDR**中。
    - 当发送移位寄存器为**空**的时候，**TDR**将数据写入到发送移位寄存器。
    - 发送移位寄存器受到**时钟**控制，移位发送数据，数据按位流入**IrDASIR编解码模块**，从**TX引脚**流出。
  - **UART接受数据通路**：
    - 数据按位流入**RX引脚**，随后进入**IrDASIR编解码模块**。
    - **接收移位寄存器**受到**时钟**控制，移位接受**IrDASIR编码器模块**中的数据，接收到**一定位数**的数据之后，接受移位寄存器将数据发送到**接收数据寄存器RDR**。
    - **接收数据寄存器RDR**(对用户不可见)将数据发送到**数据寄存器DR**中。
    - 可以通过**CPU或DMA**的方式通过**PRDATA总线**从数据寄存器**DR**中读取数据。

- **第三部分——寄存器控制单元**:ballot_box:：
  - **发送器控制单元**：
    - **发送器控制单元**能够通过**寄存器**的相应值产生**发送器控制信号**，控制发送器的发送逻辑。
    - **发送器时钟直接控制发送移位寄存器**。
  - **接收器控制单元**：
    - **接收器控制单元**能够通过**寄存器**的相应值产生**接收器控制信号**，控制接收器的接收逻辑。
    - **接收器时钟直接控制接收移位寄存器**。
    - 接收器控制单元受到**唤醒单元**的控制。
  - **接收器中断**：
    - **USART_CR1中的Bit5作为控制位**：
      - ![image-20231012195223677](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/image-20231012195223677.png)
      - 该位只能由**软件**设置或清除。
      - **0**：不会产生接收器中断。
      - **1**：可以产生接收器中断。
    - **USART_SR中的Bit5作为中断位**：
      - ![image-20231012195807493](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/image-20231012195807493.png)
      - 该位由**硬件设置**，由**软件清除**。
      - **当RXNEIE使能时**：
        - **0**：**USART_DR寄存器**中还没有收到数据，不能进行读取。
        - **1**：**接收移位寄存器**将接收到的**固定位**的数据发送到**USART_RDR**中，并且**USART_RDR**将数据发送到**USART_DR**中，数据准备好被读取，并且**产生中断**。
  - **发送器中断**：
    - **USART_CR1中的Bit6作为控制位**：
      - ![image-20231012200248537](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/image-20231012200248537.png)
      - 该位只能由**软件**设置或清除。
      - **0**：不会产生发送器中断。
      - **1**：可以产生发送器中断。
    - **USART_SR中的Bit6作为中断位**：
      - ![image-20231012200536249](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/image-20231012200536249.png)
      - 该位由**硬件设置**，由**软件清除**。
      - **当TCIE使能时**：
        - **0**：**发送移位寄存器**还没有将数据发送完成，或者**USART_TDR寄存器**中存有数据，此时不能向**USART_DR**中写入数据。
        - 1：**发送移位寄存器**和**USART_TDR**中都没有数据，此时发送完成，可以向**USART_DR**中写入数据，并且**产生中断**。

- **第四部分——波特率发生器**:lantern:：

  - **波特率**的计算公式：

    - $baud = \frac{f_{ck}}{16 * USARTDIV}$

      - $f_{ck}$：
        - **U(S)ART**输入时钟的**时钟频率**，我们可以查看**STM32F1**的**系统结构图**：
        - ![image-20231012143932672](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/image-20231012143932672.png)
        - **USART1**挂载在**APB2总线**上，因此**USART1**的时钟频率是**72MHz**(时钟树:christmas_tree:)。
        - **USART2、USART3、UART4、UART5**均挂载在**APB1总线**上，因此时钟频率是**36MHz**。
      - 分析一下**第四部分**的结构框图，可以发现$f_{ck}$时钟经过了**两次分频**，一次是**USARTDIV**，一次是**16**，分频后的时钟直接作为**发送器**和**接收器**的时钟信号，并且**发送器和接收器的时钟频率相同**。
      - **baud**：
        - 在单片机的世界中，**波特率**就是**比特率**，单位是**baud**，也可以说是**bps**。
        - **bps**表示**每秒接收的bit数量**，**USART**对数据进行**接收/发送**的时候，**每个时钟周期接收/发送1bit**，因此**波特率和时钟频率意义相同**。
          - 频率：**1s内，时钟周期的周期数量**:eagle:。
        - 如果波特率为**9600baud**，就需要让**发送器/接收器**的时钟频率是**9.6KHz**。
    - $USARTDIV = {DIVMantissa} + DIVFraction/16$：

      - 假设使用**USART1**，并且波特率选择**9600baud**，那么根据波特率计算公式，**USARTDIV = 468.75**。

      - 如何设置**USARTDIV**的值？通过**USART_BRR寄存器**:key:。

      - ![image-20231012152854008](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/image-20231012152854008.png)

      - **USART_BRR**寄存器是**32位**寄存器，**[31:16]位**保留，**[15:0]位**使用：

        - **[15:4]位存储USARTDIV的整数部分**：

          - ```c
            /*存储过程*/
            uint16_t mantissa = 468;
            USART_BRR = mantissa << 4;
            //mantissa使用[15:4]位域，由于mantissa是16位，因此左移4位，将低4位用0占位。
            ```

        - **[3:0]位存储USARTDIV的小数部分**：

          - ```c
            /*存储过程*/
            uint16_t fraction = (0.75 * 16 + 0.5);
            USART_BBR += fraction;
            /*如何实现的呢*/
            //0.75毋庸置疑是小数值，那么我们如何将小数值存储在整数寄存器的低4位呢，这肯定要涉及到转换
            //由于低4位可以用一位16进制数码表示，那么我们只需要找到0.75对应的16进制数x即可(0 <= x < 16)。
            //0.75 * 16找到的就是0.75对应的16进制数，得到的结果是12。
            //+0.5表示4舍5入，如果0.75对应的结果不是整数12呢：
            //12.3：12.3 + 0.5 = 12.8，放进整数中的还是12，和12.3差距不大。
            //12.6：12.6 + 0.5 = 13.1，放进整数中的是13，和12.6差距不大。
            /*放入寄存器*/
            //12对应的16进制数是0x000C,因此直接加到寄存器中没有任何问题。
            ```

        - **USART_BRR的计算公式**：

          - `USART_BRR = 468 << 4 + (0.75 * 16 + 0.5)`
            - 其中，**左移4位**和**乘16**意义相同。
          - `USART_BRR = (468 + 0.75) * 16 + 0.5`
            - 带入**USARTDIV**。
          - `USART_BRR = USARTDIV * 16 + 0.5`
            - 带入$baud = \frac{f_{ck}}{16 * USARTDIV}$
          - `USART_BRR = fck / baud + 0.5 `
  - 虽然我们推导了波特率的计算，但在使用**HAL库**的过程中，只需要简单配置即可:ok_man:。

    - 纯纯傻:dog2:。

## 3.STM32的USART驱动代码：

- 以**UART**为例，如果不使用同步通信的话，我们只需要使用**UART系列HAL函数**，**USART**和**UART**都可以被配置。

#### 3.1 创建UART句柄结构体：

- `UART_HandleTypeDef uart_debug_handle;`

  - 我们这里以**USART1**为例，**USART1**通常作为和**上位机**的**调试串口**:taco:。

  - ```c
    typedef struct __UART_HandleTypeDef
    {
      USART_TypeDef                 *Instance;        /*!< UART registers base address        */
    
      UART_InitTypeDef              Init;             /*!< UART communication parameters      */
    
      const uint8_t                 *pTxBuffPtr;      /*!< Pointer to UART Tx transfer Buffer */
    
      uint16_t                      TxXferSize;       /*!< UART Tx Transfer size              */
    
      __IO uint16_t                 TxXferCount;      /*!< UART Tx Transfer Counter           */
    
      uint8_t                       *pRxBuffPtr;      /*!< Pointer to UART Rx transfer Buffer */
    
      uint16_t                      RxXferSize;       /*!< UART Rx Transfer size              */
    
      __IO uint16_t                 RxXferCount;      /*!< UART Rx Transfer Counter           */
    
      __IO HAL_UART_RxTypeTypeDef ReceptionType;      /*!< Type of ongoing reception          */
    
      __IO HAL_UART_RxEventTypeTypeDef RxEventType;   /*!< Type of Rx Event                   */
    
      DMA_HandleTypeDef             *hdmatx;          /*!< UART Tx DMA Handle parameters      */
    
      DMA_HandleTypeDef             *hdmarx;          /*!< UART Rx DMA Handle parameters      */
    
      HAL_LockTypeDef               Lock;             /*!< Locking object                     */
    
      __IO HAL_UART_StateTypeDef    gState;           /*!< UART state information related to global Handle management
                                                           and also related to Tx operations.
                                                           This parameter can be a value of @ref HAL_UART_StateTypeDef */
    
      __IO HAL_UART_StateTypeDef    RxState;          /*!< UART state information related to Rx operations.
                                                           This parameter can be a value of @ref HAL_UART_StateTypeDef */
    
      __IO uint32_t                 ErrorCode;        /*!< UART Error code                    */
    
    
    } UART_HandleTypeDef;
    ```
    ```c
    //翻译：
    typedef struct __UART_HandleTypeDef
    {
      USART_TypeDef                 *Instance;        /*!< UART 寄存器基地址             */
    
      UART_InitTypeDef              Init;             /*!< UART 通信参数                  */
    
      const uint8_t                 *pTxBuffPtr;      /*!< 指向 UART 发送缓冲区的指针    */
    
      uint16_t                      TxXferSize;       /*!< UART 发送传输大小             */
    
      __IO uint16_t                 TxXferCount;      /*!< UART 发送传输计数器           */
    
      uint8_t                       *pRxBuffPtr;      /*!< 指向 UART 接收缓冲区的指针    */
    
      uint16_t                      RxXferSize;       /*!< UART 接收传输大小             */
    
      __IO uint16_t                 RxXferCount;      /*!< UART 接收传输计数器           */
    
      __IO HAL_UART_RxTypeTypeDef ReceptionType;      /*!< 正在进行的接收类型            */
    
      __IO HAL_UART_RxEventTypeTypeDef RxEventType;   /*!< 接收事件的类型                */
    
      DMA_HandleTypeDef             *hdmatx;          /*!< UART 发送 DMA 句柄参数        */
    
      DMA_HandleTypeDef             *hdmarx;          /*!< UART 接收 DMA 句柄参数        */
    
      HAL_LockTypeDef               Lock;             /*!< 锁对象                        */
    
      __IO HAL_UART_StateTypeDef    gState;           /*!< 与全局句柄管理以及发送操作相关的 UART 状态信息
                                                           此参数可以是 @ref HAL_UART_StateTypeDef 中的值 */
    
      __IO HAL_UART_StateTypeDef    RxState;          /*!< 与接收操作相关的 UART 状态信息
                                                           此参数可以是 @ref HAL_UART_StateTypeDef 中的值 */
    
      __IO uint32_t                 ErrorCode;        /*!< UART 错误代码                  */
    
    #if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
      void (* TxHalfCpltCallback)(struct __UART_HandleTypeDef *huart);        /*!< UART 发送一半完成回调函数       */
      void (* TxCpltCallback)(struct __UART_HandleTypeDef *huart);            /*!< UART 发送完成回调函数           */
      void (* RxHalfCpltCallback)(struct __UART_HandleTypeDef *huart);        /*!< UART 接收一半完成回调函数       */
      void (* RxCpltCallback)(struct __UART_HandleTypeDef *huart);            /*!< UART 接收完成回调函数           */
      void (* ErrorCallback)(struct __UART_HandleTypeDef *huart);             /*!< UART 错误回调函数               */
      void (* AbortCpltCallback)(struct __UART_HandleTypeDef *huart);         /*!< UART 终止完成回调函数           */
      void (* AbortTransmitCpltCallback)(struct __UART_HandleTypeDef *huart); /*!< UART 终止发送完成回调函数       */
      void (* AbortReceiveCpltCallback)(struct __UART_HandleTypeDef *huart);  /*!< UART 终止接收完成回调函数       */
      void (* WakeupCallback)(struct __UART_HandleTypeDef *huart);            /*!< UART 唤醒回调函数               */
      void (* RxEventCallback)(struct __UART_HandleTypeDef *huart, uint16_t Pos); /*!< UART 接收事件回调函数         */
    
      void (* MspInitCallback)(struct __UART_HandleTypeDef *huart);           /*!< UART Msp 初始化回调函数         */
      void (* MspDeInitCallback)(struct __UART_HandleTypeDef *huart);         /*!< UART Msp 反初始化回调函数       */
    #endif  /* USE_HAL_UART_REGISTER_CALLBACKS */
    
    } UART_HandleTypeDef;
    
    ```
    
  - 对于初始化结构体来讲，只需要关心`USART_TypeDef *Instance;`和`UART_InitTypeDef Init;`，如果使用**DMA**，需要配置**DMA**的参数。
  
  - ```c
    uart_debug_handle.Instance = USART1;						/*启用USART1*/
    uart_debug_handle.Init.BaudRate = 115200;					/*波特率设置115200baud*/
    uart_debug_handle.Init.WordLength = UART_WORDLENGTH_8B;		/*数据长度8bit*/
    uart_debug_handle.Init.StopBits = UART_STOPBITS_1;			/*停止位1bit*/
    uart_debug_handle.Init.Parity = UART_PARITY_NONE;			/*不使能校验位*/
    uart_debug_handle.Init.Mode = UART_MODE_TX_RX;				/*接收/发送模式*/
    uart_debug_handle.Init.OverSampling = UART_OVERSAMPLING_16;	/*采用过度采样，目的是实现更高的速度，stm32f10xx系列默认使用16*/
    uart_debug_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;		/*不需要设置硬件流控uint32_t HwFlowCtl，这是同步发送的参数*/
    ```

#### 3.2 初始化UART句柄结构体：

- `HAL_UART_Init(&uart_debug_handle);`

#### 3.3 重写UART底层驱动回调函数：

- `void HAL_UART_MspInit(UART_HandleTypeDef *huart)`

  ```c
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
  ```
