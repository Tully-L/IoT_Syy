#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f10x.h"

// DHT11 data pin definition
#define DHT11_PIN       GPIO_Pin_11
#define DHT11_PORT      GPIOA
#define DHT11_CLK       RCC_APB2Periph_GPIOA

// DHT11 data pin control macros
#define DHT11_OUT_HIGH  GPIO_SetBits(DHT11_PORT, DHT11_PIN)
#define DHT11_OUT_LOW   GPIO_ResetBits(DHT11_PORT, DHT11_PIN)
#define DHT11_IN        GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN)

// Function declarations
uint8_t DHT11_Init(void);                   // Initialize DHT11
uint8_t DHT11_Read_Data(uint8_t *temp, uint8_t *humi);  // Read temperature and humidity
void DHT11_GPIO_Init(void);                 // Initialize GPIO
void DHT11_Mode_OUT(void);                  // Set pin as output
void DHT11_Mode_IN(void);                   // Set pin as input

#endif
