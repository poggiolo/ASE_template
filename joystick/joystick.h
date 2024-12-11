#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#include "LPC17xx.h"
#include "../led/led.h"

#define JOYSTICK_UP 29
#define JOYSTICK_DOWN 26
#define JOYSTICK_LEFT 27
#define JOYSTICK_RIGHT 28
#define JOYSTICK_PRESS 25

#define FLAG_JOYSTICK_UP 1
#define FLAG_JOYSTICK_DOWN 2
#define FLAG_JOYSTICK_LEFT 4
#define FLAG_JOYSTICK_RIGHT 8
#define FLAG_JOYSTICK_SELECT 16

void joystick_init(void);
int joystick_check_dir(uint32_t);

/******************************************************************************
**                            End Of File
******************************************************************************/

#endif // __JOYSTICK_H
