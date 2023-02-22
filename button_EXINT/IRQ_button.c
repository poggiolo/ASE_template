#include "button.h"
#include "../RIT/RIT.h"

extern int pressed_button_0;
extern int pressed_button_1;
extern int pressed_button_2;

void EINT0_IRQHandler(void){
	// Variable set to 1	
    pressed_button_0 = 1;
	// Disable interrupt
    NVIC_DisableIRQ(EINT0_IRQn);
	// Remove interrput bit
    LPC_SC->EXTINT |= (1 << 0);
	// Change pin selection so that the button 
	// does not work any longer. 
    LPC_PINCON->PINSEL4 &= ~(1 << 20);
}

void EINT1_IRQHandler(void){
    pressed_button_1 = 1;
    NVIC_DisableIRQ(EINT1_IRQn);
    LPC_SC->EXTINT |= (1 << 1);
    LPC_PINCON->PINSEL4 &= ~(1 << 22);
}

void EINT2_IRQHandler(void){
    pressed_button_2 = 1;
    NVIC_DisableIRQ(EINT2_IRQn);
    LPC_SC->EXTINT |= (1 << 2);
    LPC_PINCON->PINSEL4 &= ~(1 << 24);
}

/******************************************************************************
**                            End Of File
******************************************************************************/
