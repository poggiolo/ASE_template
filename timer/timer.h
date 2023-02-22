#include "lpc17xx.h"
#include "../led/led.h"
#include "../joystick/joystick.h"

#define TIM_MS_TO_TICKS(MS, PR, FREQ) ((uint32_t)(((uint64_t)(MS)) * (FREQ) / ((PR)+1)))
#define TIM_MS_TO_TICKS_SIMPLE(MS) TIM_MS_TO_TICKS((MS), 0, 25000)

#define TIMER_INTERRUPT_MR 1
#define TIMER_RESET_MR 2
#define TIMER_STOP_MR 4

#define TIMER_0 0 
#define TIMER_1 1
#define TIMER_2 2
#define TIMER_3 3

#define PRIO_0 0
#define PRIO_1 1
#define PRIO_2 2
#define PRIO_3 3
#define PRIO_4 4
#define PRIO_5 5

#define IR_MR0 1
#define IR_MR1 2
#define IR_MR2 4
#define IR_MR3 8

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
void init_timer_simplified(int timer_n, int prescale, int mr0, int mr1, int conf_mr0, int conf_mr1);
void reset_timer(uint8_t timer_num);

/* IRQ_timer.c */
void TIMER0_IRQHandler (void);
void TIMER1_IRQHandler (void);
void TIMER2_IRQHandler (void);
void TIMER3_IRQHandler (void);

/*****************************************************************************
**                            End Of File
******************************************************************************/
