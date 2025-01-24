#ifndef __RIT_H
#define __RIT_H

#include "LPC17xx.h"
#include "../led/led.h"
#include  "../timer/timer.h"

/**
* @brief return ticks for the RIT timer initialization give milliseconds
* @param MS RIT period in milliseconds
* @note base frequency of RIT is 100MHz
*/
#define RIT_MS_TO_TICKS(MS) TIM_MS_TO_TICKS(MS, 0, 100000000)

uint32_t init_RIT( uint32_t RITInterval );
void enable_RIT( void );
void disable_RIT( void );
void reset_RIT( void );

extern void RIT_IRQHandler (void);

#endif 

/******************************************************************************
**                            End Of File
******************************************************************************/
