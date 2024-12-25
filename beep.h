#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f10x.h"

void beep_init(void);
void beep_short(void);      // Single short beep
void beep_double(void);     // Double short beep
void beep_error(void);      // Long error beep
void beep_welcome(void);    // Welcome melody

#endif
