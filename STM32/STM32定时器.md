# STM32定时器简介之基本定时器

### 一、基本定时器

#### 1.1 TIM6/TIM7

* ##### 主要特性

   1）16位**递增**计数器，计数值0~65535

   2）16位预分频器，分频系数1~65536

   3）在计数器溢出（更新事件）时，可产生中断/DMA请求


* ##### 溢出条件：CNT计数器 == ARR（影子）
  影子寄存器是实际起作用的寄存器，不可直接访问。

* ##### TIMx_CR1寄存器详解

  ![image-20230930163102670](https://raw.githubusercontent.com/undefined-0/image-store/main/PicGo/202309302149191.png)

  ![image-20230930163131134](https://raw.githubusercontent.com/undefined-0/image-store/main/PicGo/202309302149193.png)

  * 缓冲：
    * 没有缓冲的情况下（TIMx_CR1寄存器位7置0，ARPE失能）：操作ARR寄存器时，其值会被直接转移到ARR寄存器的影子寄存器中，从而直接生效。
    * 有缓冲的情况下（TIMx_CR1寄存器位7置1，ARPE使能）：操作ARR寄存器时，其值不会被马上转移到影子寄存器中，而是需要等待更新事件U事件的发生。更新事件发生后，ARR寄存器中的值才会转移到影子寄存器中，从而真正起作用
    * e.g.

#### 1.2 STM32定时器的**预装载值**和**预分频系数**（PSC）的确定

* 根据定时器时钟的频率，比如时钟的频率是72MHZ，可以理解为一秒钟STM32会自己数72M次，预分频系数就是将频率分割，比如预分频系数是72，则该时钟的频率会变成72MHZ/72=1MHZ，但是在设置的时候要注意，数值应该是72-1。想对时钟源进行72分频，那么预分频器的值就应该设置为71（因为达到最大值后还要再tick一次才归零）。假定分频系数是72-1，那么频率变成1MHZ，也就意味着STM32在一秒钟会数1M次，即1us数一次。接下来就是确定预装载值，比如需要定时1ms，由于1ms=1us*1000,那么预装载值就是1000-1（预装载值减一是因为重装需要一个时钟周期）；如此类推，在预分频系数确定的情况下，定时的时长就由预装载值确定了。

* 公式为定时器时钟频率先除以分频系数，得到计数频率，即1s中计数多少次。 然后用该计数频率再除以ARR（重装载值）``（谷歌上说乘以，但原子书上是除以，这里有点搞不清）``，就得到PWM的频率，即1s中会有多少高电平产生（电平变化再复原）。

#### 1.3 定时器时间计算公式

```text
Tout=((ARR+1)*(PSC+1))/Tclk
```

* Tout：TIM溢出时间 单位 us
  ARR：重装载值
  PSC：预分频系数
  Tclk（$F_t$） ： TIM 输入时钟频率 （MHZ）

* 例 ：

```c
TIM_TimeBaseStructure.TIM_ClockDivision  =  TIM_CKD_DIV1; 
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
TIM_TimeBaseStructure.TIM_Period = 4999; 		//自动装载值
TIM_TimeBaseStructure.TIM_Prescaler =7199;    //预分频值
```

Tout = （4999+1）*（7199+1）/72 = 500000
= 500 ms

#### 1.4基本定时器中断实验配置步骤

* 1. 配置定时器基础工作参数

     ```c
     HAL_TIM_Base_Init()
     ```

  2. 定时器基础MSP初始化

     ```c
     HAL_TIM_Base_Msplnit()//配置NVIC、GPIO、CLOCK等，本身是一个空函数，用于存放相关的初始化代码
     ```

     * MSP：与MCU相关的初始化
     * NVIC：Nested vectoredinterrupt controller，即嵌套向量中断控制器，控制着整个STM32芯片中断相关的功能，与Cortex-M3 内核紧密联系，是内核中的一个外设。

  3. 使能更新中断并启动计数器

     ```C
     HAL_TIM_Base_IT()
     ```

  4. 设置优先级，使能中断

     ```c
     HAL_NVIC_SetPriority()
     HAL_NVIC_EnableIRQ()
     ```

  5. 编写中断服务函数

     ```c
     TIMx_IRQHandler()
     ```

  6. 编写定时器更新中断回调函数（即：计时器溢出后需要做什么）

     ```c
     HAL_TIM_PeriodElapsedCallback()//空函数，需要自行定义 
     ```

* 相关HAL库函数介绍：
       ![image-20230923193205083](https://raw.githubusercontent.com/undefined-0/image-store/main/PicGo/202309232056572.png)

### 二、通用定时器

#### 2.1 TIM2/TIM3/TIM4/TIM5

* 主要特性

  1）16位**递增、递减、中心对齐**计数器，计数值0~65535

  2）16位预分频器，分频系数1~65536

  3）在**更新事件、触发事件、输入捕获、输出比较**时，可产生中断/DMA请求

  4）4个独立通道（用于输入捕获、输出比较、输出PWM、单脉冲模式）

  5）可以使用外部信号控制定时器，也可以使用多个定时器相互同步电路（定时器的级联）

  * 定时器的级联：使用一个定时器的一个溢出事件来给另一个定时器作为时钟源

  6）支持编码器和霍尔传感器电路

### 补充：不同定时器计数模式的溢出条件

![image-20231001211647763](https://raw.githubusercontent.com/undefined-0/image-store/main/PicGo/202310012206764.png)

【【STM32入门教程-2023】第15集 超清晰STM32时钟树动画讲解】 https://www.bilibili.com/video/BV1ph4y1e7Ey/?share_source=copy_web&vd_source=5268a7bf868ecf913cd7fb51a00205a5

【如何使用stm32单片机的定时器】 https://www.bilibili.com/video/BV15S4y1g7WT/?share_source=copy_web&vd_source=5268a7bf868ecf913cd7fb51a00205a5

STM32时钟系统中的SysTick、FCLK、SYSCLK、PCLK和HCLK - SugarlesS的文章 - 知乎 https://zhuanlan.zhihu.com/p/376894689