#ifndef __USART1_H
#define __USART1_H

#include "stm32f10x.h"

void usart1_init(void);
void send_byte(unsigned char data);

#endif
