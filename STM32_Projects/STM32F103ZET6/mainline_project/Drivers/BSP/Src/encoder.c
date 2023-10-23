#include "encoder.h"

Encoder_InitTypeDef encoder_init_struct;
TIM_HandleTypeDef encoder_general_tim_handle;
TIM_Encoder_InitTypeDef encoder_tim_init_struct;
TIM_HandleTypeDef encoder_base_tim_handle;
long long encoder_tim_count;/*表示产生的更新中断的次数*/
void encoder_base_tim_init(void)
{
    encoder_base_tim_handle.Instance = ENCODER_BASE_TIM;
    encoder_base_tim_handle.Init.Prescaler = ENCODER_BASE_TIM_PSC;
    encoder_base_tim_handle.Init.Period = ENCODER_BASE_TIM_ARR;
    encoder_base_tim_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    encoder_base_tim_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

    /*基本定时器初始化函数*/
    HAL_TIM_Base_Init(&encoder_base_tim_handle);
}
void bcd_encoder_init(void)
{
    /*编码器接口结构体初始化*/
    encoder_init_struct.encode_num_now = 0;
    encoder_init_struct.encode_num_old = 0;
    encoder_init_struct.speed = 0;
    encoder_init_struct.resolution = 4 * 13; /* 定时器放大倍数 * 编码器原始分辨率 */

    /*编码器定时器配置*/
    encoder_general_tim_handle.Instance = ENCODER_GENERAL_TIM;
    encoder_general_tim_handle.Init.Prescaler = ENCODER_GENERAL_TIM_PSC;
    encoder_general_tim_handle.Init.Period = ENCODER_GENERAL_TIM_ARR;
    encoder_general_tim_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    encoder_general_tim_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    /*编码器接口配置*/
    encoder_tim_init_struct.EncoderMode = TIM_ENCODERMODE_TI12;
    encoder_tim_init_struct.IC1Filter = 0;
    encoder_tim_init_struct.IC1Polarity = TIM_ENCODERINPUTPOLARITY_RISING;
    encoder_tim_init_struct.IC1Prescaler = TIM_ICPSC_DIV1;
    encoder_tim_init_struct.IC1Selection = TIM_ICSELECTION_DIRECTTI;
    encoder_tim_init_struct.IC2Filter = 0;
    encoder_tim_init_struct.IC2Polarity = TIM_ENCODERINPUTPOLARITY_RISING;
    encoder_tim_init_struct.IC2Prescaler = TIM_ICPSC_DIV1;
    encoder_tim_init_struct.IC2Selection = TIM_ICSELECTION_DIRECTTI;

    /*编码器接口初始化函数*/
    HAL_TIM_Encoder_Init(&encoder_general_tim_handle, &encoder_tim_init_struct);

    /*基本定时器初始化*/
    encoder_base_tim_init();

}
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == ENCODER_BASE_TIM)
	{
		__HAL_RCC_TIM6_CLK_ENABLE();
		HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn); /*将中断入口挂载到NVIC上*/
        HAL_TIM_Base_Start_IT(&encoder_base_tim_handle); /*使能定时器x和定时器x更新中断*/
	}
}
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == ENCODER_GENERAL_TIM)
    {
        GPIO_InitTypeDef gpio_init_struct;//创建GPIO初始化结构体
        __HAL_RCC_GPIOB_CLK_ENABLE();//开启GPIOB时钟
		__HAL_RCC_TIM4_CLK_ENABLE();//开启TIM4时钟

        gpio_init_struct.Pin = ENCODER_GENERAL_TIM_CHANNEL_1_GPIO_PIN;                
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;//复用推挽输出
        gpio_init_struct.Pull = GPIO_NOPULL;//作为编码器的输入相，不需要上拉或下拉 
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;      
        HAL_GPIO_Init(ENCODER_GENERAL_TIM_CHANNEL_1_GPIO_PORT, &gpio_init_struct);//初始化  
        
        gpio_init_struct.Pin = ENCODER_GENERAL_TIM_CHANNEL_2_GPIO_PIN;                   
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                  
        gpio_init_struct.Pull = GPIO_NOPULL;                                    
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                             
        HAL_GPIO_Init(ENCODER_GENERAL_TIM_CHANNEL_2_GPIO_PORT, &gpio_init_struct);         
      
        HAL_NVIC_SetPriority(TIM4_IRQn, 2, 0);//配置更新中断的优先级                   
        HAL_NVIC_EnableIRQ(TIM4_IRQn);//将更新中断的入口在NVIC处使能    

        /*开启编码器接口通道*/
        HAL_TIM_Encoder_Start(&encoder_general_tim_handle, ENCODER_GENERAL_TIM_CHANNEL_1);
        HAL_TIM_Encoder_Start(&encoder_general_tim_handle, ENCODER_GENERAL_TIM_CHANNEL_2);

        /*使能编码器接口对应定时器的更新中断*/
        __HAL_TIM_CLEAR_FLAG(&encoder_general_tim_handle,TIM_IT_UPDATE);//避免上一次的更新中断标志位没有清除，先清除更新中断标志位
        __HAL_TIM_ENABLE_IT(&encoder_general_tim_handle,TIM_IT_UPDATE);//使能定时器更新中断               
    }
}
/**
 * @brief encoder基本定时器的中断服务函数
*/
void TIM6_DAC_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&encoder_base_tim_handle);
}
/**
 * @brief encoder的中断服务函数
*/
void TIM4_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&encoder_general_tim_handle);/*公共中断服务函数*/
}
/**
 * @brief 更新中断回调函数
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{  
    int32_t encode_num_now = 0;
     if (htim->Instance == ENCODER_BASE_TIM)
     {
        encode_num_now = encoder_tim_get_encode_num();/*获取当前编码器的数值*/
        calculate_bcd_speed(encode_num_now);/*根据编码器的数值计算电机速度*/
     }
     else if (htim->Instance == ENCODER_GENERAL_TIM)
     {
        if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&encoder_general_tim_handle))                           /* 判断CR1的DIR位，即判断定时器是否是向下计数 */
        {
            encoder_tim_count--;                                                           /* DIR位为1，也就是递减计数 */
        }
        else
        {
            encoder_tim_count++;                                                           /* DIR位为0，也就是递增计数 */
        }
     }
}
int32_t encoder_tim_get_encode_num(void)
{
    return (int32_t)__HAL_TIM_GET_COUNTER(&encoder_general_tim_handle) + encoder_tim_count * 65536;   /* 总的编码器值 = 当前计数值 + 之前累计编码器的值 */
}
void calculate_bcd_speed(int32_t encode_num_now)
{
    /**
     * 整体思路：
     *          累计计算10次电机的速度，通过对速度进行排序，排除两侧的数据，剩下的数据求平均值，之后在进行滤波，将滤波后的速度作为输出结果。(目前不包含PID算法)
     * 如何计算电机的速度：
     *          基本定时器每1ms执行一次更新中断，因此可以得到时间差为1ms的编码器计数变化量
     *          计算1min内的编码器计数变化量
     *          计算1min内编码器的旋转圈数RPM(计数变化量/编码器放大后的分辨率)
     *          计算1min内电机的旋转圈数RPM(编码器RPM/电机减速比)
    */
    uint8_t i; /*循环变量*/
    float motor_speed_sum = 0.00; /*电机的速度和*/
    float motor_speed_avg = 0.00; /*电机的速度平均值*/
    static uint8_t k = 0; /*统计十次电机速度*/
    static float motor_speed_array[10] = {0.0}; /*存放十次电机速度的数组*/

    encoder_init_struct.encode_num_now = encode_num_now;
    encoder_init_struct.speed = (float)((encoder_init_struct.encode_num_now - encoder_init_struct.encode_num_old) * 1000 * 60 / encoder_init_struct.resolution); /*编码器的速度*/
    motor_speed_array[k++] = (float)(encoder_init_struct.speed / bcd_motor_init_struct.reduction_ratio);            /*电机的速度*/

    if (k == 10)
    {
        k = 0;
        meger_sort(motor_speed_array, 0, 9);                                                                        /* 归并排序 */
        
        for (i = 2; i < 8; i++)                                                                                     /* 去除两边高低数据 */
        {
            motor_speed_sum += motor_speed_array[i];                                                                /* 将中间数值累加 */
        }
        motor_speed_avg = motor_speed_sum / 6;                                                                      /* 计算电机的平均速度 */
        bcd_motor_init_struct.speed = first_order_low_pass_filter(motor_speed_avg, bcd_motor_init_struct.speed);    /* 一阶低通滤波 */
    }
}
float first_order_low_pass_filter(float motor_speed_now, float motor_speed_old)
{
    return (motor_speed_now * 0.3) + (motor_speed_old * 0.7);
}
void meger_sort(float array[], uint8_t start, uint8_t tail)
{
    uint8_t mid = 0;
    float asso_array[10] = {0};
    uint8_t i = 0; /*循环变量*/
    if (start == tail)
    {
        return;
    }
    else 
    {
        mid = (start + tail);
        meger_sort(array, start, mid);
        meger_sort(array, mid + 1, tail);
        meger(array, asso_array, start, mid, tail);
        for (i = start; i <= tail; i++)
            array[i] = asso_array[i];
    }
}
void meger(float array[], float asso_array[], uint8_t start, uint8_t mid, uint8_t tail)
{
    uint8_t i = start;   /*左侧循环变量*/
    uint8_t j = mid + 1; /*右侧循环变量*/
    uint8_t k = start;   /*辅助数组循环变量*/
    while (i <= mid && j <= tail)
    {
        if (array[i] < array[j])
        {
            asso_array[k++] = array[i++];
        }
        else 
        {
            asso_array[k++] = array[j++];
        }
    }
    while (i <= mid)
    {
        asso_array[k++] = array[i++];
    }
    while (j <= tail)
    {
        asso_array[k++] = array[j++];
    }
}
