#include "timer.h"
#include "../common.h"

// DEFAULT TIMER CLOCK SOURCE IS PCLK/4 = 25 MHz

struct timer_info timers_info[4];

uint32_t timer_get_counter(uint8_t timer_num) {
	switch(timer_num) {
		case TIMER_0: return LPC_TIM0->TC;
		case TIMER_1: return LPC_TIM1->TC;
		case TIMER_2: return LPC_TIM2->TC;
		case TIMER_3: return LPC_TIM3->TC;
		default: return 0;
	}
}

void enable_timer( uint8_t timer_num, uint8_t priority){
	if (timer_num == TIMER_0){
		LPC_TIM0->TCR = 1;
		NVIC_EnableIRQ(TIMER0_IRQn);
		NVIC_SetPriority(TIMER0_IRQn, priority);
	}
	else if(timer_num == TIMER_1){
		LPC_TIM1->TCR = 1;
		NVIC_EnableIRQ(TIMER1_IRQn);
		NVIC_SetPriority(TIMER1_IRQn, priority);
	}
	else if(timer_num == TIMER_2){
		LPC_TIM2->TCR = 1;
		NVIC_EnableIRQ(TIMER2_IRQn);
		NVIC_SetPriority(TIMER2_IRQn, priority);
	}
	else if(timer_num == TIMER_3){
		LPC_TIM3->TCR = 1;
		NVIC_EnableIRQ(TIMER3_IRQn);
		NVIC_SetPriority(TIMER3_IRQn, priority);
	}
	return;
}

// RESET TIMER ALSO STOPS THE TIMER: NEED TO USE ENABLE_TIMER AGAIN!
void reset_timer(uint8_t timer_num){
	if (timer_num == TIMER_0) LPC_TIM0->TCR |= 0x02;
	else if (timer_num == TIMER_1) LPC_TIM1->TCR |= 0x02;
	else if (timer_num == TIMER_2) LPC_TIM2->TCR |= 0x02;
	else if (timer_num == TIMER_3) LPC_TIM3->TCR |= 0x02;
}

void disable_timer( uint8_t timer_num ){
	if     (timer_num == TIMER_0) LPC_TIM0->TCR = 0;
	else if(timer_num == TIMER_1) LPC_TIM1->TCR = 0;
	else if(timer_num == TIMER_2) LPC_TIM2->TCR = 0;
	else if(timer_num == TIMER_3) LPC_TIM3->TCR = 0;
	return;
}

void init_infinite_timer_pwm(uint8_t timer_n, float duty, uint32_t period_ms, timer_callback_t callback) {
	uint32_t mr1 = TIM_MS_TO_TICKS_SIMPLE(period_ms);
	init_timer_simplified(timer_n, 0, duty*mr1, mr1, TIMER_INTERRUPT_MR, TIMER_INTERRUPT_MR|TIMER_RESET_MR, callback); 
}

static void _init_repetitive_timer_pwm (struct finite_pwm_timer_configuration* tm, timer_callback_t callback){
	LPC_TIM_TypeDef* timer = NULL;

	if (tm->timer_n == TIMER_0){
		LPC_SC->PCONP |= (1 << 1);
		timer = (LPC_TIM_TypeDef*)LPC_TIM0_BASE;
	}
  	else if(tm->timer_n == TIMER_1){
		LPC_SC->PCONP |= (1 << 2);
		timer = (LPC_TIM_TypeDef*)LPC_TIM1_BASE;
	}
	else if(tm->timer_n == TIMER_2){
		LPC_SC->PCONP |= (1 << 22);
		timer = (LPC_TIM_TypeDef*)LPC_TIM2_BASE;
	}
	else if(tm->timer_n == TIMER_3){
		LPC_SC->PCONP |= (1 << 23);
		timer = (LPC_TIM_TypeDef*)LPC_TIM3_BASE;
	}

	timer->IR = timer->IR; // reset irq flag
	
	timer->PR = tm->prescale;
	
	timer->MR0 = tm->mr0;
	timer->MR1 = tm->mr1;
	
	timer->MCR = (
		(tm->configuration_mr0 << 0) |
		(tm->configuration_mr1 << 3)
	);
	
	timers_info[tm->timer_n].max_count = (tm->duration_ms)/TIM_TICKS_TO_MS_SIMPLE(tm->mr1);
  timers_info[tm->timer_n].callback = callback;
  timers_info[tm->timer_n].count = 0;
}

void init_finite_timer_pwm(uint8_t timer_n, float duty, uint32_t period_ms, uint32_t duration_ms, timer_callback_t callback){
	uint32_t mr1 = TIM_MS_TO_TICKS_SIMPLE(period_ms);
	
	struct finite_pwm_timer_configuration fptm = {0}; 
	
	fptm.timer_n = timer_n;
	fptm.prescale = 0;
	fptm.configuration_mr0 = TIMER_INTERRUPT_MR;
	fptm.mr0 = duty*mr1;
	fptm.configuration_mr1 = TIMER_INTERRUPT_MR|TIMER_RESET_MR,
	fptm.mr1 = mr1,
	fptm.duration_ms = duration_ms;
	
	_init_repetitive_timer_pwm(&fptm, callback);
}

void init_timer_simplified(uint8_t timer_n, uint32_t prescale, uint32_t mr0, uint32_t mr1, uint8_t conf_mr0, uint8_t conf_mr1, timer_callback_t callback)
{
	struct timer_configuration tm = {0}; 
	
	tm.timer_n = timer_n;
	tm.prescale = prescale;
	tm.configuration_mr0 = conf_mr0;
	tm.configuration_mr1 = conf_mr1;
	tm.mr0 = mr0;
	tm.mr1 = mr1;
	
	init_timer(&tm, callback);
}

void init_timer (struct timer_configuration* tm, timer_callback_t callback){
	LPC_TIM_TypeDef* timer = NULL;

	if (tm->timer_n == TIMER_0){
		LPC_SC->PCONP |= (1 << 1);
		timer = (LPC_TIM_TypeDef*)LPC_TIM0_BASE;
	}
  	else if(tm->timer_n == TIMER_1){
		LPC_SC->PCONP |= (1 << 2);
		timer = (LPC_TIM_TypeDef*)LPC_TIM1_BASE;
	}
	else if(tm->timer_n == TIMER_2){
		LPC_SC->PCONP |= (1 << 22);
		timer = (LPC_TIM_TypeDef*)LPC_TIM2_BASE;
	}
	else if(tm->timer_n == TIMER_3){
		LPC_SC->PCONP |= (1 << 23);
		timer = (LPC_TIM_TypeDef*)LPC_TIM3_BASE;
	}

	timer->IR = timer->IR; // reset irq flag
	
	timer->PR = tm->prescale;
	
	timer->MR0 = tm->mr0;
	timer->MR1 = tm->mr1;
	timer->MR2 = tm->mr2;
	timer->MR3 = tm->mr3;
	
	timer->MCR = (
		(tm->configuration_mr0 << 0) |
		(tm->configuration_mr1 << 3) |
		(tm->configuration_mr2 << 6) |
		(tm->configuration_mr3 << 9)
	);
	
	timers_info[tm->timer_n].max_count = 0;
  timers_info[tm->timer_n].callback = callback;
  timers_info[tm->timer_n].count = 0;
}


void init_repetitive_timer_simplified(uint8_t timer_n, uint32_t prescale, uint32_t mr0, uint32_t duration_ms, timer_callback_t callback)
{
	struct repetitive_timer_configuration rtm = {0}; 
	
	rtm.timer_n = timer_n;
	rtm.prescale = prescale;
	rtm.mr0 = mr0;
	rtm.duration_ms = duration_ms;
	
	init_repetitive_timer(&rtm, callback);
}

/**
* @params timer_configuration: timer config
* @params duration_ms: timer duration for ripetitive timers, set to timer time for a non-ripetitive timer
* 										 Note: make sure interrupt flags are set properly for a ripetitive timers
* @params callback: callback to be executed
**/
void init_repetitive_timer (struct repetitive_timer_configuration* tm, timer_callback_t callback){
	LPC_TIM_TypeDef* timer = NULL;

	if (tm->timer_n == TIMER_0){
		LPC_SC->PCONP |= (1 << 1);
		timer = (LPC_TIM_TypeDef*)LPC_TIM0_BASE;
	}
  	else if(tm->timer_n == TIMER_1){
		LPC_SC->PCONP |= (1 << 2);
		timer = (LPC_TIM_TypeDef*)LPC_TIM1_BASE;
	}
	else if(tm->timer_n == TIMER_2){
		LPC_SC->PCONP |= (1 << 22);
		timer = (LPC_TIM_TypeDef*)LPC_TIM2_BASE;
	}
	else if(tm->timer_n == TIMER_3){
		LPC_SC->PCONP |= (1 << 23);
		timer = (LPC_TIM_TypeDef*)LPC_TIM3_BASE;
	}

	timer->IR = timer->IR; // reset irq flag
	
	timer->PR = tm->prescale;
	
	timer->MR0 = tm->mr0;

	
	timer->MCR = (
		((TIMER_INTERRUPT_MR | TIMER_RESET_MR) << 0)
	);
	
	timers_info[tm->timer_n].max_count = (tm->duration_ms)/TIM_TICKS_TO_MS_SIMPLE(tm->mr0);
  timers_info[tm->timer_n].callback = callback;
  timers_info[tm->timer_n].count = 0;
}

/*
	in IR si deve settare il bit associato al MR di cui si vuole cancellare l'interruzione.
*/

void TIMER_IRQHandler (void){
	uint8_t irq_source;
  for (int i = 0; i < 4; i++) {
    if 			(i == 0) irq_source = LPC_TIM0->IR;
    else if (i == 1) irq_source = LPC_TIM1->IR;
    else if (i == 2) irq_source = LPC_TIM2->IR;
    else if (i == 3) irq_source = LPC_TIM3->IR;
    
    if (irq_source) {
			if(timers_info[i].max_count != 0){
				if (irq_source & IR_MR0) {
					timers_info[i].count++;
					if (timers_info[i].count >= timers_info[i].max_count) {
						disable_timer(i);
					}
				}
			}
			if (timers_info[i].callback) timers_info[i].callback(irq_source);

			// Reset IRQ Flag
			if 			(i == 0) LPC_TIM0->IR = irq_source;
			else if (i == 1) LPC_TIM1->IR = irq_source;
			else if (i == 2) LPC_TIM2->IR = irq_source;
			else if (i == 3) LPC_TIM3->IR = irq_source;
    }
  }
}


/******************************************************************************
**                            End Of File
******************************************************************************/
