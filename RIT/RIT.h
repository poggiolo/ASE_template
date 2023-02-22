#include "lpc17xx.h"
#include "../led/led.h"

#ifndef __RIT_H
#define __RIT_H

extern uint32_t init_RIT( uint32_t RITInterval );
extern void enable_RIT( void );
extern void disable_RIT( void );
extern void reset_RIT( void );

extern void RIT_IRQHandler (void);

#endif 

/******************************************************************************
**                            End Of File
******************************************************************************/
