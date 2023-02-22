#include "joystick.h"

// Function use to check whether a direction of the joystick is pressed or not
int joystick_check_dir(uint32_t dir){
	if ((LPC_GPIO1->FIOPIN & ( 1 << dir)) == 0) return 1;
	return 0;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
