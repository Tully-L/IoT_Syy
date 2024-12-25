#ifndef __AHT10_H
#define __AHT10_H

#include "stm32f10x.h"

// Function declarations
void AHT10_Init(void);
uint8_t AHT10_Read_Data(float *temperature, float *humidity);
void AHT10_Reset(void);

#endif
