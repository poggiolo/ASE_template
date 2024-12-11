#include "timer.h"
#include "../common.h"

// DEFAULT TIMER CLOCK SOURCE IS PCLK/4 = 25 MHz

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

void init_timer_pwm(uint8_t timer_n, float duty, uint32_t period_ms) {
	uint32_t mr1 = TIM_MS_TO_TICKS_SIMPLE(period_ms);
	init_timer_simplified(timer_n, 0, duty*mr1, mr1, TIMER_INTERRUPT_MR, TIMER_INTERRUPT_MR|TIMER_RESET_MR); 
}

void init_timer_simplified(uint8_t timer_n, uint32_t prescale, uint32_t mr0, uint32_t mr1, uint8_t conf_mr0, uint8_t conf_mr1){
	struct timer_configuration tm = {0}; 
	
	tm.timer_n = timer_n;
	tm.prescale = prescale;
	tm.configuration_mr0 = conf_mr0;
	tm.configuration_mr1 = conf_mr1;
	tm.mr0 = mr0;
	tm.mr1 = mr1;
	
	init_timer(&tm);
}

void init_timer (struct timer_configuration* tc){
	LPC_TIM_TypeDef* timer = NULL;

	if (tc->timer_n == TIMER_0){
		LPC_SC->PCONP |= (1 << 1);
		timer = (LPC_TIM_TypeDef*)LPC_TIM0_BASE;
	}
  	else if(tc->timer_n == TIMER_1){
		LPC_SC->PCONP |= (1 << 2);
		timer = (LPC_TIM_TypeDef*)LPC_TIM1_BASE;
	}
	else if(tc->timer_n == TIMER_2){
		LPC_SC->PCONP |= (1 << 22);
		timer = (LPC_TIM_TypeDef*)LPC_TIM2_BASE;
	}
	else if(tc->timer_n == TIMER_3){
		LPC_SC->PCONP |= (1 << 23);
		timer = (LPC_TIM_TypeDef*)LPC_TIM3_BASE;
	}

	timer->IR = timer->IR; // reset irq flag
	
	timer->PR = tc->prescale;
	
	timer->MR0 = tc->mr0;
	timer->MR1 = tc->mr1;
	timer->MR2 = tc->mr2;
	timer->MR3 = tc->mr3;
	
	timer->MCR = (
		(tc->configuration_mr0 << 0) |
		(tc->configuration_mr1 << 3) |
		(tc->configuration_mr2 << 6) |
		(tc->configuration_mr3 << 9)
	);
	
}


/******************************************************************************
**                            End Of File
******************************************************************************/
