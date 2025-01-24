#include "timer.h"
#include "../common.h"

/*
* NOTE: Repetitive timers only in MR0!
*/

void timer0_callback(uint8_t irq_src){
	if(irq_src & IR_MR0){

	} else if (irq_src & IR_MR1){
		
	} else if (irq_src & IR_MR2) {
	
	} else if (irq_src & IR_MR3){
		
	}
}

void timer1_callback(uint8_t irq_src){
	if(irq_src & IR_MR0){

	} else if (irq_src & IR_MR1){
		
	} else if (irq_src & IR_MR2) {
	
	} else if (irq_src & IR_MR3){
		
	}
}

void timer2_callback(uint8_t irq_src){
	if(irq_src & IR_MR0){

	} else if (irq_src & IR_MR1){
		
	} else if (irq_src & IR_MR2) {
	
	} else if (irq_src & IR_MR3){
		
	}
}

void timer3_callback(uint8_t irq_src){
	if(irq_src & IR_MR0){
		
	} else if (irq_src & IR_MR1){

	} else if (irq_src & IR_MR2) {
	
	} else if (irq_src & IR_MR3){
		
	}
}

/******************************************************************************
**                            End Of File
******************************************************************************/

