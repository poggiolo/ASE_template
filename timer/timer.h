#include "LPC17xx.h"
#include "../led/led.h"
#include "../joystick/joystick.h"
#include <stdio.h>

#ifndef __TIMER_H
#define __TIMER_H

#define TIM_MS_TO_TICKS(MS, PR, FREQ_HZ) ((uint32_t)(((uint64_t)(MS)) * (FREQ_HZ/1000U) / ((PR)+1U)))
#define TIM_MS_TO_TICKS_SIMPLE(MS) TIM_MS_TO_TICKS((MS), 0U, 25000000U)
#define TIM_TICKS_TO_MS(TICKS, PR, FREQ_HZ) ((uint32_t)(((uint64_t)(TICKS)) * ((PR)+1U)) / (FREQ_HZ/1000U))
#define TIM_TICKS_TO_MS_SIMPLE(TICKS) TIM_TICKS_TO_MS((TICKS), 0U, 25000000U)

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

typedef void (*timer_callback_t)(uint8_t);

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

struct repetitive_timer_configuration{
	uint8_t timer_n;
	uint32_t prescale;
	uint32_t mr0;
	uint32_t duration_ms;
};

struct finite_pwm_timer_configuration{
	uint8_t timer_n;
	uint32_t prescale;
	uint32_t mr0;
	uint8_t configuration_mr0;
	uint32_t mr1;
	uint8_t configuration_mr1;
	uint32_t duration_ms;
};

struct timer_info {
  int count;
  int max_count;
  timer_callback_t callback;
};

/* init_timer.c */
uint32_t timer_get_counter(uint8_t timer_num);
void enable_timer(uint8_t timer_n, uint8_t prio);
void disable_timer(uint8_t timer_n);
void init_timer (struct timer_configuration* tm, timer_callback_t callback);
void init_infinite_timer_pwm(uint8_t timer_n, float duty, uint32_t period_ms, timer_callback_t callback);
void init_timer_simplified(uint8_t timer_n, uint32_t prescale, uint32_t mr0, uint32_t mr1, 
														uint8_t conf_mr0, uint8_t conf_mr1, timer_callback_t callback);
void reset_timer(uint8_t timer_num);
void init_repetitive_timer (struct repetitive_timer_configuration* tm, timer_callback_t callback);
void init_repetitive_timer_simplified(uint8_t timer_n, uint32_t prescale, uint32_t mr0, uint32_t duration_ms, timer_callback_t callback);
void init_finite_timer_pwm(uint8_t timer_n, float duty, uint32_t period_ms, uint32_t duration_ms, timer_callback_t callback);

/* IRQ_timer.c */
void timer0_callback(uint8_t irq_src);
void timer1_callback(uint8_t irq_src);
void timer2_callback(uint8_t irq_src);
void timer3_callback(uint8_t irq_src);

#endif
/*****************************************************************************
**                            End Of File
******************************************************************************/
