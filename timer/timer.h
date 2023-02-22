#include "lpc17xx.h"
#include "../led/led.h"
#include "../joystick/joystick.h"
#include <stdio.h>

#ifndef __TIMER_H
#define __TIMER_H

#define TIM_MS_TO_TICKS(MS, PR, FREQ_HZ) ((uint32_t)(((uint64_t)(MS)) * (FREQ_HZ/1000U) / ((PR)+1U)))
#define TIM_MS_TO_TICKS_SIMPLE(MS) TIM_MS_TO_TICKS((MS), 0U, 25000000U)

#define TIMER_INTERRUPT_MR 1U
#define TIMER_RESET_MR 2U
#define TIMER_STOP_MR 4U

#define TIMER_0 0U 
#define TIMER_1 1U
#define TIMER_2 2U
#define TIMER_3 3U

#define IR_MR0 1U
#define IR_MR1 2U
#define IR_MR2 4U
#define IR_MR3 8U

struct timer_configuration{
	uint8_t timer_n;
	
	uint32_t prescale;
	
	uint32_t mr0;
	uint32_t mr1;
	uint32_t mr2;
	uint32_t mr3;
	
	uint8_t configuration_mr0;
	uint8_t configuration_mr1;
	uint8_t configuration_mr2;
	uint8_t configuration_mr3;
};

/* init_timer.c */
uint32_t timer_get_counter(uint8_t timer_num);
void enable_timer(uint8_t timer_n, uint8_t prio);
void disable_timer(uint8_t timer_n);
void init_timer (struct timer_configuration* tm);
void init_timer_pwm(uint8_t timer_n, float duty, uint32_t period_ms);
void init_timer_simplified(uint8_t timer_n, uint32_t prescale, uint32_t mr0, uint32_t mr1, uint8_t conf_mr0, uint8_t conf_mr1);
void reset_timer(uint8_t timer_num);

/* IRQ_timer.c */
void TIMER0_IRQHandler (void);
void TIMER1_IRQHandler (void);
void TIMER2_IRQHandler (void);
void TIMER3_IRQHandler (void);

#endif
/*****************************************************************************
**                            End Of File
******************************************************************************/
