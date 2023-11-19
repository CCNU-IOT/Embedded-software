# PWM脉宽调制

作者：嵌入式软件小组:pen:

## 1.什么是PWM？

#### 1.1 wikipedia：

- **PWM**简称**脉宽调制**，是用**脉冲**来输出**模拟信号**的一种技术。
  - **PWM**是一种**技术**:ok:，而不是一种**信号**。
  - **PWM**通过对一系列脉冲的**宽度**进行调制，来等效地获得所需要**波形**(含**形状**和**幅值**)。
    - 对于同一个正弦波，其**电压**是固定不变的。
  - 对于数字电路来讲，输出的电压只有两种：$U_{ON}$和$U_{OFF}$
    - 使用**PWM**技术可以等效获得处于$U_{ON}$和$U_{OFF}$之间的任意波形，即**任意电压**。
    - **任意电压**：
      - 在不改变最大电压的情况下，通过改变**最大电压出现的频率**，来改变整体的**平均电压**。
  - **电压**可以直接控制家用电器设备中的音量、LED灯的亮度等，因此可以直接使用**模拟电路**来完成。
    - 但模拟电路存在**难以调节**、**功耗大**、**易受噪声和环境干扰**等问题，因此使用**数字电路**+**PWM技术**等效调节电压。

#### 1.2  控制PWM的重要参数：

- **Frequency 频率**:tiger:：
  - 频率是周期的**相反数**，单位是**Hz**。
    - 这里的周期表示**脉冲周期**：从高电平的**起始位置**到下一次高电平的**起始位置**所花的**时间**。
    - 频率和周期的**换算**：
      - **1s        <--->     1Hz**
      - **1ms    <--->    1KHz**
      - **1us     <--->    1MHz**
      - **1ns     <--->    1GHz**
  - 选择**PWM的频率**需要综合考虑应用的需求和硬件的能力。
    - 较高的频率通常可以提供更精确的控制，但也可能导致更多的开关损耗。
    - 较低的频率可以降低开关损耗，但在某些应用中可能引入可听到的噪音。
    - **电机设备的运行特性**：
      - 较高频率的**PWM**可以提供更**平滑**的电机运动，但也会引入更多的电流谐波和损耗。
    - **LED灯的亮度控制**：
      - 较高频率的**PWM**可以提供更精确的亮度控制，同时减小了**可见闪烁**。
        - 欺骗人眼:eye:。

- **Duty Cycle 占空比**:lion:：
  - 这个参数是**PWM**技术中最重要的参数，占空比表示一个**脉冲周期**内，**高电平的时间**与整个周期时间的比例。
  - 占空比用来改变**脉冲周期**的**平均电压**。
    - ![1920px-Duty_cycle_general.svg](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/1920px-Duty_cycle_general.svg.png)
    - 如果我们考虑一个周期为$T$的脉冲波$f(t)$ ，低值$y_{min}$，高值为$y_{max}$，跟一个占空比$D$，此波的**平均值**为：
      - ![9eaf9734459b6422b6a50977da6236ae7622ef3d](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/9eaf9734459b6422b6a50977da6236ae7622ef3d.svg)
      - **展开**：
      - ![3ff6bfb695bad62cb26a2f8c5fa2d565431e5375](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/3ff6bfb695bad62cb26a2f8c5fa2d565431e5375.svg)
      - 通常，$y_{min} = 0$，$y_{max} = 3.3V/5V$，因此**平均值**仅和**占空比**有关。
- 在使用**PWM**技术的时候，首先确定`Frequency`，其次确定`Duty cycle`。

#### 1.3 PWM的实际应用：

- **呼吸灯**:b:：
  - **频率**：
    - 如果频率很小的话，人眼能够很明显的看到**闪烁**，当频率大于**50Hz**(脉冲周期**T < 20ms**)的时候，人眼就会产生**视觉暂留**，即认为**LED灯常亮**。
  - **占空比**：
    - 在**一定的频率**下，改变**占空比**，改变**LED灯**的亮度，占空比越大，**LED灯**越亮。

![giphy](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/giphy.gif)

- **舵机控制**:m:：
  - 以**180°**转动的**伺服舵机SG90**为例：
    - ![v2-26c7f03ba98dfbd6cd557a35943cb581_1440w](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/v2-26c7f03ba98dfbd6cd557a35943cb581_1440w.png)
  - **频率**：
    - 频率越高，舵机转动越平滑，通常情况下，舵机的频率为**50Hz**，即脉冲周期为**20ms**。
  - **占空比**：
    - 控制舵机的**转角**。
    - 控制关系(**高电平时间—转角**)：
      - **0.5ms   <--->   0度**
      - **1.0ms   <--->   45度**
      - **1.5ms   <--->   90度**
      - **2.0ms   <--->   135度**
      - **2.5ms   <--->   180度**

![在这里插入图片描述](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/20200128155221315.gif)

- **电机控制**:car:：
  - **频率**：
    - 频率越高，舵机转动越平滑。
  - **占空比**：
    - 占空比越大，电机的转速越快。

![img](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/m3508-01.76b56e4.jpg)

## 2.STM32中使用PWM：

#### 2.1 定时器与PWM：

- 在**STM32**中，使用**PWM**技术要利用**Timer**，通过**Timer**来产生频率一定，占空比不同的输出信号。
- **STM32**的通用定时器有两种方式产生**PWM信号**：**输出比较**和**PWM模式**
  - 其中，**PWM模式**是**输出比较**的**子模式**，**输出比较模式**可以输出四路**频率不同**的**PWM信号**，**PWM模式**只能输出四路**频率相同**的**PWM信号**。

- **在STM32中输出PWM信号，请充分了解STM32的通用定时器！**:hamster:

#### 2.2 PWM模式工作过程：

- 以**PWM模式**为例。
- 配置**预分频寄存器(TIMx_PSC)**的值，对定时器的**输入时钟进行分频**，分频后的时钟作为定时器的**最终输入时钟**。
- 设置定时器**自动重装载寄存器(TIMx_ARR)**的值，（以**递增计数**为例）计数器递增到自动重装载值的时间就是**PWM信号**的**脉冲周期**，进而可知**PWM信号**的**频率**。
- 设置**捕获/比较寄存器(TIMx_CCRx)**的值，(以**PWM模式1**为例)，当**计数器值**小于**比较值**的时候，通道输出**高电平**，当**计数器值**大于**比较值**的时候，通道输出**低电平**。
- 当**计数器值**达到**自动重装载值**，则产生一个**定时器溢出事件**。
  - 此时，`TIMx_CCRx / TIMx_ARR = Duty Cycle`

#### 2.3 配置PWM驱动代码：

- 配置**输出频率**是`Frequency`，**占空比**是`duty cycle`的**PWM信号**。

  - 以**TIM3的Channel2**为例。

- **第一步：创建定时器句柄**

  - 在**基本定时器**中已经详细介绍过。

  - ```c
    ***************************/*定时器句柄结构体定义*/*******************************
    typedef struct
    {
    	TIM_TypeDef *Instance; /* 外设寄存器基地址 */
    	TIM_Base_InitTypeDef Init; /* 定时器初始化结构体*/
    	HAL_TIM_ActiveChannel Channel; /* 定时器通道 */
    	DMA_HandleTypeDef *hdma[7]; /* DMA 管理结构体 */
    	HAL_LockTypeDef Lock; /* 锁定资源 */
    	__IO HAL_TIM_StateTypeDef State; /* 定时器状态 */
    }TIM_HandleTypeDef;
    //定义结构体：
    TIM_HandleTypeDef pwm_time_handle;//通常将其声明在全局区
    ***************************/*定时器初始化结构体定义*/******************************
    typedef struct 
    {
    	uint32_t Prescaler; /* 预分频系数 */
    	uint32_t CounterMode; /* 计数模式 */
    	uint32_t Period; /* 自动重载值 ARR */
    	uint32_t ClockDivision; /* 时钟分频因子 */
    	uint32_t RepetitionCounter; /* 重复计数器 */
    	uint32_t AutoReloadPreload; /* 自动重载预装载使能 */
    }TIM_Base_InitTypeDef;
    ```

  - 对于**PWM模式**来讲，定时器句柄的**Channel**参数不需要配置。

    - 后面有专门的通道配置函数。

- **第二步：初始化定时器(定时器通道)**

  - ```c
    ******************************/*调用PWM相关定时器初始化函数*/****************************
    HAL_TIM_PWM_Init(&pwm_time_handle);//接受句柄结构体指针
    ```

- **第三步：重写定时器底层驱动函数**

  - `void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)`

    - 该函数同样是**定时器底层驱动函数**，该函数会被`HAL_TIM_PWM_Init`函数在最后调用。
    - 由于**PWM**配置过程中需要用到**GPIO**(通用定时器的通道连通IO口)，因此GPIO相关函数写在底层驱动函数中。
    - 该函数是**_weak**函数，因此可以进行**重写**。

  - ```c
    void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
    {
        if (htim->Instance == TIM3)
        {
            GPIO_InitTypeDef gpio_init_struct;//创建GPIO初始化结构体
            __HAL_RCC_GPIOB_CLK_ENABLE();//TIM3->Channel2对应GPIOB5，开启GPIOB时钟
            __HAL_RCC_TIM3_CLK_ENABLE();//开启TIM3时钟
            
            gpio_init_struct.Pin = GPIO_PIN_5; /* 通道y的CPIO口 */
            gpio_init_struct.Mode = GPIO_MODE_AF_PP;           /* 复用推挽输出,这里作为TIM3的CH2输出，因此是复用 */
            gpio_init_struct.Pull = GPIO_PULLUP;               /* 上拉 */
            gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;     /* 高速 */
            HAL_GPIO_Init(GPIOB, &gpio_init_struct);//初始化GPIOB5端口
            
            /*TIM3通道重映射，具体参考定时器文章*/
            __HAL_RCC_AFIO_CLK_ENABLE();//打开AFIO时钟
            __HAL_AFIO_REMAP_TIM3_PARTIAL();//重映射TIM3的通道
        }
    }
    ```
    

- **第四步：创建定时器输出比较结构体**

  - 该结构体用来配置定时器的**输出比较参数**。

  - ```c
    ***************************/*定时器输出比较结构体定义*/******************************
    typedef struct
    {
    	uint32_t OCMode; /* 输出比较模式选择，共8种模式 */
    	uint32_t Pulse; /* 设置比较值 */
    	uint32_t OCPolarity; /* 设置输出比较极性 */
    	uint32_t OCNPolarity; /* 设置互补输出比较极性 */
    	uint32_t OCFastMode; /* 使能或失能输出比较快速模式 */
    	uint32_t OCIdleState; /* 选择空闲状态下的非工作状态（OC1输出） */
    	uint32_t OCNIdleState; /* 设置空闲状态下的非工作状态（OC1N输出） */
    } TIM_OC_InitTypeDef;
    //定义结构体：
    TIM_OC_InitTypeDef tim_oc_init_struct;
    ```

  - 通用定时器没有互补输出，我们仅关注**前三个参数**即可。

  - **uint32_t OCMode**：

    - 对于**PWM模式**，这个参数只有两个选择：
      - **PWM模式1**：`TIM_OCMODE_PWM1`
      - **PWM模式2**：`TIM_OCMODE_PWM2`

  - **uint32_t Pulse**：

    - 设置**捕获/比较寄存器**的值。

  - **uint32_t OCPolarity**：

    - **输出极性**：
      - **TIM_OCNPolarity_High**，高极性。
      - **TIM_OCNPolarity_Low**，低极性。

    - 这个参数较为重要，我们再来回顾一下**PWM模式1**和**PWM模式2**。
    - **PWM模式1—向上计数**：
      - 当**TIMx_CNT < TIMx_CCRx**时，输出通道为**有效电平**。
      - 当**TIMx_CNT > TIMx_CCRx**时，输出通道为**无效电平**。
    - **PWM模式1—向下计数**：
      - 当**TIMx_CNT > TIMx_CCRx**时，输出通道为**无效电平**。
      - 当**TIMx_CNT < TIMx_CCRx**时，输出通道为**有效电平**。

    - **PWM模式2—向上计数**：
      - 当**TIMx_CNT < TIMx_CCRx**时，输出通道为**无效电平**。
      - 当**TIMx_CNT > TIMx_CCRx**时，输出通道为**有效电平**。

    - **PWM模式2—向下计数**：
      - 当**TIMx_CNT > TIMx_CCRx**时，输出通道为**有效电平**。
      - 当**TIMx_CNT < TIMx_CCRx**时，输出通道为**无效电平**。

    - 简而言之，**输出极性决定了有效电平**，当输出极性是高极性的时候，有效电平是高电平。
    - 假设输出极性是**高极性**：
      - ![](https://nickaljy-pictures.oss-cn-hangzhou.aliyuncs.com/image-20231003131158019.png)


- **第五步：配置定时器输出通道**
  - `HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef *sConfig, uint32_t Channel);`  
- **第六步：开启定时器PWM输出**
  - 使能定时器通道输出。
  - `HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel);  `
- **在PWM输出中，并没有对定时器溢出事件进行配置，因此不需要中断先关函数。**
  - 如果需要，请自行配置。
- 更完整和详细的代码，请参考**工程文件**和协会内部的**BSP库**。
