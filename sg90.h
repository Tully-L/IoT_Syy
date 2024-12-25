#ifndef __SG90_H
#define __SG90_H

#include "stm32f10x.h"

// Door states and angles
#define DOOR_CLOSED    0    // Door closed state
#define DOOR_OPEN      1    // Door open state
#define ANGLE_CLOSED   0    // Servo angle for closed position
#define ANGLE_OPEN     90   // Servo angle for open position

void SG90_Init(void);
void SG90_SetAngle(uint8_t angle);
void setDoorState(uint8_t state);

#endif
