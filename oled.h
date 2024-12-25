#ifndef __OLED_H
#define __OLED_H

#include "stm32f10x.h"

// GPIO definitions
#define OLED_SCL_PIN    GPIO_Pin_8    // SCL to PB8
#define OLED_SDA_PIN    GPIO_Pin_9    // SDA to PB9
#define OLED_GPIO       GPIOB
#define OLED_ADDR       0x78          // OLED I2C address

// Function declarations
void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t x, uint8_t y, char chr);
void OLED_ShowString(uint8_t x, uint8_t y, char *str);
void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len);
void OLED_ShowSignedNum(uint8_t x, uint8_t y, int32_t num, uint8_t len);
void OLED_ShowHexNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len);
void OLED_ShowBinNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len);
void OLED_Set_Pos(uint8_t x, uint8_t y);

// Helper function
uint32_t OLED_Pow(uint8_t m, uint8_t n);

#endif
