# J-Link

作者：嵌入式软件小组:pen:

## 1.什么是J-Link：

- **J-Link**是**SEGGER公司**生产的支持**8051**、**Cortex-M**、**Cortex-A**(32位和64位)的调试器。

<img src="https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/J-Link_Pro_Perspective_4.png" alt="J-Link_Pro_Perspective_4" style="zoom:33%;" />

## 2.J-Link的模式：

#### 2.1 JTAG模式：

- **JTAG诞生于上世纪80年代**，**JTAG**(Joint Test Action Group，联合测试行动小组)是一种**国际标准测试协议**，主要用于芯片内部测试。
  - 现在多数的高级器件都支持**JTAG协议**，如ARM、DSP、FPGA器件等。
- **J-Link**上的**20引脚**集成**JTAG模式**：
  - 选择**JTAG**的时候，通常将**20引脚**全部接线。

![image-20231003175634342](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/image-20231003175634342.png)

#### 2.2 SWD模式：

- **SWD(Serial Wire Debug)**是**ARM**公司提出的一种调试接口，作为**JTAG**的替代品。
  - **SWD**只需要四根线：
    - **VCC**：
      - 用来给**J-Link**供电，通常不需要接线，**J-Link**的**USB**侧就能够供电。
    - **GND**：
      - 公共接地。
    - **SWCLK**：
      - 串行时钟输入端口。
    - **SWDIO**：
      - 串行数据输入端口。

## 3.JTAG与SWD比较：

#### 3.1 JTAG：

- 下载速度快，接线简单(**20Pin**即可)，但增加开发板**PCB布线**难度，可能会出现**占用IO**的问题。

#### 3.2 SWD：

- 下载速度较快，需要自己**单独接线**，不会出现**占用IO**的问题，更加可靠。

## 4.J-Link版本：

- **J-Link v6**：
  - 支持**SWD**，但速度很慢。
- **J-Link v7**：
  - 支持**SWD**，下载速度是**v6**的**6倍**。
- **J-Link v8**：
  - 支持**SWD**，下载速度可达**10Mbps**。