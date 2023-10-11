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
- **第四部分——波特率发生器**:lantern:：
  - 对UART模块的输入时钟进行分频。
  - 产生接收器和发送器的**波特率**。