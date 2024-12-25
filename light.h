#ifndef __LIGHT_H
#define __LIGHT_H

#include "stm32f10x.h"

// Pin definitions
#define LIGHT_DO_PIN    GPIO_Pin_0    // PA0 for digital output
#define LIGHT_AO_PIN    GPIO_Pin_1    // PA1 for analog output
#define LIGHT_GPIO      GPIOA
#define LIGHT_ADC       ADC1
#define LIGHT_ADC_CH    ADC_Channel_1 // ADC channel for PA1

// Function declarations
void Light_Init(void);
uint8_t Light_GetDO(void);           // Get digital value (0 or 1)
uint16_t Light_GetAO(void);          // Get analog value (0-4095)

#endif
