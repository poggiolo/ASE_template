#include "button.h"

/**
 * @brief  Function that initializes Buttons
 */
void BUTTON_init(uint8_t button, uint8_t prio) {
	if(button == 0){
		LPC_PINCON->PINSEL4    |= (1 << 20);		 /* External interrupt 0 pin selection */
		LPC_GPIO2->FIODIR      &= ~(1 << 10);    /* PORT2.10 defined as input          */
		LPC_SC->EXTMODE |= 0x01;
		NVIC_EnableIRQ(EINT0_IRQn);        
		NVIC_SetPriority(EINT0_IRQn, prio);
	}
	if(button == 1){
		LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
		LPC_GPIO2->FIODIR      &= ~(1 << 11);    /* PORT2.11 defined as input          */
		LPC_SC->EXTMODE |= 0x02;
		NVIC_EnableIRQ(EINT1_IRQn);        
		NVIC_SetPriority(EINT1_IRQn, prio);
	}
	if(button == 2){
		LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
		LPC_GPIO2->FIODIR      &= ~(1 << 12);    /* PORT2.12 defined as input          */
		LPC_SC->EXTMODE |= 0x04;
		NVIC_EnableIRQ(EINT2_IRQn);        
		NVIC_SetPriority(EINT2_IRQn, prio);
	}
}

/******************************************************************************
**                            End Of File
******************************************************************************/
