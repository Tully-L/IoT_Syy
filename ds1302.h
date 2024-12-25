#ifndef __DS1302_H__
#define __DS1302_H__

#include "stm32f10x.h"

#define uchar unsigned char
#define uint unsigned int

/* DS1302 Pin Configuration
 * CLK -> PA4
 * IO  -> PA6
 * CS  -> PA7
 */

#define OUT   0x01
#define IN    0x00

extern uchar label2[16];  // Time display buffer

#define DS1302_PORT   GPIOA

// GPIO Control Macros
#define CLK_Reset_0  GPIOA->BRR  = GPIO_Pin_4
#define CLK_Set_1    GPIOA->BSRR = GPIO_Pin_4

#define IO_Reset_0   GPIOA->BRR  = GPIO_Pin_6
#define IO_Set_1     GPIOA->BSRR = GPIO_Pin_6

#define CS_Reset_0   GPIOA->BRR  = GPIO_Pin_7
#define CS_Set_1     GPIOA->BSRR = GPIO_Pin_7

#define IO_Read      GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)

// DS1302 Register Addresses
#define ds1302_sec_addr    0x80    // Second register
#define ds1302_min_addr    0x82    // Minute register
#define ds1302_hour_addr   0x84    // Hour register
#define ds1302_day_addr    0x86    // Day register
#define ds1302_month_addr  0x88    // Month register
#define ds1302_year_addr   0x8c    // Year register

// Function Declarations
void DS1302_GPIOInit(void);
void DS1302_IO_GPIO(uchar FLAG);
void DS1302_delay(u8 dd);
void DS1302_Write(uchar add, uchar dat);
uchar DS1302_Read(uchar add);
void DS1302_SetTime(uchar *ad);
void DS1302_OFF(void);
void DS1302_ON(void);
void DS1302_init(uchar *time);
void DS1302_Readtime(void);

#endif
