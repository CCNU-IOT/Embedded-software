#include "adc.h"

// 初始化ADC
void ADC_Init(void) {
    ADC_HandleTypeDef hadc;

    // 启用ADC时钟
    __HAL_RCC_ADC1_CLK_ENABLE();

    hadc.Instance = ADC1;

    // ADC初始化结构体配置
    hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc.Init.ScanConvMode = DISABLE; // 单通道模式
    hadc.Init.ContinuousConvMode = DISABLE; // 单次转换
    hadc.Init.NbrOfConversion = 1;
    hadc.Init.DiscontinuousConvMode = DISABLE;
    hadc.Init.NbrOfDiscConversion = 1;
    hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    hadc.Init.DMAContinuousRequests = DISABLE;
    hadc.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
    hadc.Init.OversamplingMode = DISABLE;

    if (HAL_ADC_Init(&hadc) != HAL_OK) {
        Error_Handler();
    }
}

// 读取ADC值
uint16_t ADC_Read(uint32_t channel) {
    ADC_HandleTypeDef hadc;
    ADC_ChannelConfTypeDef sConfig;

    // 配置ADC通道
    hadc.Instance = ADC1;
    sConfig.Channel = channel;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;

    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK) {
        Error_Handler();
    }

    // 启动ADC转换
    if (HAL_ADC_Start(&hadc) != HAL_OK) {
        Error_Handler();
    }

    // 等待转换完成
    if (HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY) != HAL_OK) {
        Error_Handler();
    }

    // 读取ADC值
    return HAL_ADC_GetValue(&hadc);
}
