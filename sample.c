#include "include.h"
#include "common.h"

#define N 8
#define RIT_PERIOD_MS 50

typedef enum {
	STATE_IDLE,
	STATE_RESET
} state_t;

extern void nome_molto_lungo_e_complicato(uint32_t VETT[], uint32_t n);

extern uint8_t joystick_flag;
extern uint8_t btn_flag;

state_t state;
uint32_t VETT[N];

int main (void) {
	SystemInit();
	
	// AAA: SET DEBUG ON THE BOARD
	// AAA: ADD TO WATCH THE GLOBAL VARIABLES USED
	// AAA: ADD THE BREAKPOINTS WHERE YOU PERFROM SOME ACTIONS
	// AAA: ADD THE BREAKPOINTS TO THE BEGINNING OF ASM
	
	state = STATE_IDLE;
	memset(VETT, 0, sizeof(VETT));
	
	LED_init();
	
	// LCD_Initialization();
	joystick_init();
	
	// BUTTON_init:
	//		1: which button
	//		2: priority of the associated interrupt
	
	BUTTON_init(BUTTON_0, PRIO_3);
	BUTTON_init(BUTTON_1, PRIO_3);
	BUTTON_init(BUTTON_2, PRIO_3);
	
	// RIT WORKS WITH CLOCK = 100MHZ
	// ONE INTERRUPT EACH 50ms
	
	init_RIT(RIT_MS_TO_TICKS(RIT_PERIOD_MS)); enable_RIT();
	
	//	init_timer_simplified:
	//		1: which timer
	// 		2: prescaler
	//		3: mr0
	// 		4: mr1
	//		5: configuration of MR0 (interrupt, reset and stop) ( | of TIMER_INTERRUPT_MR, TIMER_RESET_MR, TIMER_STOP_MR)
	//		6: configuration of MR1 (interrupt, reset and stop) ( | of TIMER_INTERRUPT_MR, TIMER_RESET_MR, TIMER_STOP_MR)
	
	// TIMER_0
	// f_timer_hz    = 25000000 Hz = 25MHz
	// prescaler     = 
	// MR            = 
	// f_counter_hz  = f_timer_hz / (prescaler + 1) = 
	// T_timer       = MR / f_counter_hz = 
	// MR = T_timer * f_timer_hz / (prescaler + 1) = 
	
	// USE TIM_MS_TO_TICKS_SIMPLE for default PR (=0) and f_timer_hz values
	// use TIM_MS_TO_TICKS for custom PR and f_timer_hz values
	// max ms value is 170000 (2min 50s) => TIM_MS_TO_TICKS_SIMPLE(170000)=2^31-1
	
	// init_timer_simplified(TIMER_0, prescale, mr0, mr1, conf_mr0, conf_mr1); enable_timer(TIMER_0, PRIO_3);
	
	// init_timer_pwm(TIMER_0, 0.5, 170000); enable_timer(TIMER_0, PRIO_3);
	
	ADC_init();
	
	// power control register
	LPC_SC->PCON |= 0x1;		// PM0=1
	LPC_SC->PCON &= 0xFFFFFFFFD;	// PM1=0
	//execution of wfi or wfe assembly enters Power-Down mode when SLEEPDEEP is on
	
	// call asm function
	// nome_molto_lungo_e_complicato(VETT, N);
		
	while (1) {
		/*
		if(joystick_flag & FLAG_JOYSTICK_UP) {
			joystick_flag &= ~FLAG_JOYSTICK_UP;
		}
		*/
		/*
		if(joystick_flag & FLAG_JOYSTICK_DOWN) {
			joystick_flag &= ~FLAG_JOYSTICK_DOWN;
		}
		*/
		/*
		if(joystick_flag & FLAG_JOYSTICK_LEFT) {
			joystick_flag &= ~FLAG_JOYSTICK_LEFT;
		}
		*/
		/*
		if(joystick_flag & FLAG_JOYSTICK_RIGHT) {
			joystick_flag &= ~FLAG_JOYSTICK_RIGHT;
		}
		*/
		/*
		if(joystick_flag & FLAG_JOYSTICK_SELECT) {
			joystick_flag &= ~FLAG_JOYSTICK_SELECT;
		}
		*/
		/*
		if(btn_flag & FLAG_BUTTON_0) {
			btn_flag &= ~FLAG_BUTTON_0;
		}
		*/
		/*
		if(btn_flag & FLAG_BUTTON_1) {
			btn_flag &= ~FLAG_BUTTON_1;
		}
		*/
		/*
		if(btn_flag & FLAG_BUTTON_2) {
			btn_flag &= ~FLAG_BUTTON_2;
		}
		*/
		
		__ASM("wfi");
	}
}

// ************************
// END FILE								*
// ************************
