#include "adc.h"

// ��ʼ��ADC
void ADC_Init(void) {
    ADC_HandleTypeDef hadc;

    // ����ADCʱ��
    __HAL_RCC_ADC1_CLK_ENABLE();

    hadc.Instance = ADC1;

    // ADC��ʼ���ṹ������
    hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc.Init.ScanConvMode = DISABLE; // ��ͨ��ģʽ
    hadc.Init.ContinuousConvMode = DISABLE; // ����ת��
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

// ��ȡADCֵ
uint16_t ADC_Read(uint32_t channel) {
    ADC_HandleTypeDef hadc;
    ADC_ChannelConfTypeDef sConfig;

    // ����ADCͨ��
    hadc.Instance = ADC1;
    sConfig.Channel = channel;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;

    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK) {
        Error_Handler();
    }

    // ����ADCת��
    if (HAL_ADC_Start(&hadc) != HAL_OK) {
        Error_Handler();
    }

    // �ȴ�ת�����
    if (HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY) != HAL_OK) {
        Error_Handler();
    }

    // ��ȡADCֵ
    return HAL_ADC_GetValue(&hadc);
}
