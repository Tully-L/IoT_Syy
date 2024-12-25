//#include "light.h"

//void Light_Init(void)
//{
//    GPIO_InitTypeDef GPIO_InitStructure;
//    ADC_InitTypeDef ADC_InitStructure;
//    
//    // Enable GPIO and ADC clock
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
//    
//    // Configure DO pin (PA0) as input
//    GPIO_InitStructure.GPIO_Pin = LIGHT_DO_PIN;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//    GPIO_Init(LIGHT_GPIO, &GPIO_InitStructure);
//    
//    // Configure AO pin (PA1) as analog input
//    GPIO_InitStructure.GPIO_Pin = LIGHT_AO_PIN;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//    GPIO_Init(LIGHT_GPIO, &GPIO_InitStructure);
//    
//    // ADC configuration
//    ADC_DeInit(LIGHT_ADC);
//    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
//    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
//    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
//    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
//    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
//    ADC_InitStructure.ADC_NbrOfChannel = 1;
//    ADC_Init(LIGHT_ADC, &ADC_InitStructure);
//    
//    // Configure ADC channel
//    ADC_RegularChannelConfig(LIGHT_ADC, LIGHT_ADC_CH, 1, ADC_SampleTime_239Cycles5);
//    
//    // Enable ADC
//    ADC_Cmd(LIGHT_ADC, ENABLE);
//    
//    // ADC calibration
//    ADC_ResetCalibration(LIGHT_ADC);
//    while(ADC_GetResetCalibrationStatus(LIGHT_ADC));
//    ADC_StartCalibration(LIGHT_ADC);
//    while(ADC_GetCalibrationStatus(LIGHT_ADC));
//}

//uint8_t Light_GetDO(void)
//{
//    return GPIO_ReadInputDataBit(LIGHT_GPIO, LIGHT_DO_PIN);
//}

//uint16_t Light_GetAO(void)
//{
//    // Start ADC conversion
//    ADC_SoftwareStartConvCmd(LIGHT_ADC, ENABLE);
//    
//    // Wait for conversion complete
//    while(!ADC_GetFlagStatus(LIGHT_ADC, ADC_FLAG_EOC));
//    
//    // Return conversion result
//    return ADC_GetConversionValue(LIGHT_ADC);
//}
