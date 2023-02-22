#ifndef __BUTTON_H
#define __BUTTON_H

#include "lpc17xx.h"
#include "../led/led.h"

#define BUTTON_0 0
#define BUTTON_1 1
#define BUTTON_2 2

#define FLAG_BUTTON_0 (1 << BUTTON_0)
#define FLAG_BUTTON_1 (1 << BUTTON_1)
#define FLAG_BUTTON_2 (1 << BUTTON_2)

void BUTTON_init(uint8_t timer, uint8_t prio);

void EINT1_IRQHandler(void);
void EINT2_IRQHandler(void);
void EINT3_IRQHandler(void);

/******************************************************************************
**                            End Of File
******************************************************************************/

#endif // __BUTTON_H
