#include "Drivers\BSP\Inc\adc.h"

    ADC_HandleTypeDef hadc;

void ADC_Init(void) 
{
    hadc.Instance = ADC1; //选择ADC1

    // ADC初始化结构体配置
    hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;          // 数据对齐方式设置为右对齐
    hadc.Init.ScanConvMode = DISABLE;                   // 单通道模式
    hadc.Init.ContinuousConvMode = DISABLE;             // 单次转换,非连续转换
    hadc.Init.NbrOfConversion = 1;                      // 转换的通道数为1
    hadc.Init.DiscontinuousConvMode = DISABLE;          // 不连续转换模式禁用
    hadc.Init.NbrOfDiscConversion = 1;                  // 不连续转换的通道数为1
    hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;    // 外部触发转换使用软件触发方式启动

    HAL_ADC_Init(&hadc);
    HAL_ADCEx_Calibration_Start(&hadc);
}

HAL_ADC_MspInit(ADC_HandleTypeDef* hadc) //会被HAL_ADC_Init函数所调用的MSP回调函数，用来存放使能ADC和通道对应IO的时钟和初始化IO口等代码
{
if(hadc->Instance == ADC1)
 {
    RCC_PeriphCLKInitTypeDef adc_clk_init = {0};
    GPIO_InitTypeDef gpio_init_struct;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_ADC1_CLK_ENABLE();

    // 设置 ADC 外设时钟
    adc_clk_init.PeriphClockSelection = RCC_PERIPHCLK_ADC; // 选择 ADC 外设时钟为要配置的外设时钟
    adc_clk_init.AdcClockSelection = RCC_ADCPCLK2_DIV6; // 将ADC的时钟分频设置为6，这意味着ADC的时钟频率将为主时钟（72MHz）除以6，即12MHz。
    HAL_RCCEx_PeriphCLKConfig(&adc_clk_init); // 将ADC的时钟配置应用到硬件，告诉系统使用12MHz的时钟频率来驱动ADC模块。

    // 设置 AD 采集通道对应 IO 引脚工作模式
    gpio_init_struct.Pin = GPIO_PIN_1; // 选择引脚1为要配置的GPIO引脚
    gpio_init_struct.Mode = GPIO_MODE_ANALOG; // 设置GPIO引脚的工作模式为模拟模式。在模拟模式下，该引脚将用于连接到ADC通道，以便进行模拟信号的采集
    
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);
 }
}

// 读取ADC值
uint16_t ADC_Read(ADC_HandleTypeDef hadc, uint32_t channel) 
{
    ADC_ChannelConfTypeDef sConfig; //通道配置结构体变量

    // 配置ADC通道
    hadc.Instance = ADC1;
    sConfig.Channel = channel;
    sConfig.Rank = 1; // 设置通道配置结构体的排名为1
    sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5; // 设置通道配置结构体的采样时间

    HAL_ADC_ConfigChannel(&hadc, &sConfig);
    
    // 启动ADC转换
    HAL_ADC_Start(&hadc);

    // 等待转换完成
    HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);

    // 读取ADC值
    return HAL_ADC_GetValue(&hadc);
}
