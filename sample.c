#include "include.h"
#include "common.h"

// Private Variables
static volatile uint32_t Sys_Tick = 0;

// Local Functions Prototypes
static void InitSysTick(void);
void SysTick_Handler(void);
void Delay_SysTick(uint32_t SysTicks);

// Exported variables
volatile state_t state;

// Imported Variables
extern volatile uint8_t joystick_flag;
extern volatile uint8_t btn_flag;

// Imported Functions
extern void ASM_func(uint32_t VETT[], uint32_t n);
	
// Local Global Variables
uint32_t VETT[N];
uint32_t i;
uint32_t VAR;

int main (void) {
	// Imperative Inits
	SystemInit();
	InitSysTick();
	
	// Initialize Variables
	state = STATE_IDLE;
	memset(VETT, 0, sizeof(VETT));
	i = 0;
	VAR = 0;
	
	// Other peripherals Init
	LED_init();
	joystick_init();
	//LCD_Initialization();
	//ADC_init();
	
	// BUTTON_init:
	//		1: which button
	//		2: priority of the associated interrupt
	
	BUTTON_init(BUTTON_0, PRIO_3);
	BUTTON_init(BUTTON_1, PRIO_3);
	BUTTON_init(BUTTON_2, PRIO_3);
	
	// RIT WORKS WITH CLOCK = 100MHZ
	// ONE INTERRUPT EVERY 50ms
	
	init_RIT(RIT_MS_TO_TICKS(RIT_PERIOD_MS)); enable_RIT();
	
	/* TIMER INSTRUCTIONS
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
	*/
	// init_timer_simplified(TIMER_0, prescale, mr0, mr1, conf_mr0, conf_mr1); enable_timer(TIMER_0, PRIO_3);
		
	//init_timer_simplified(TIMER_0, 0, TIM_MS_TO_TICKS_SIMPLE(1000), 0, TIMER_INTERRUPT_MR | TIMER_RESET_MR | TIMER_STOP_MR, 0, timer0_callback);
	//enable_timer(TIMER_0, PRIO_3);
	
	/* Example: do stuff every 500ms ms for 10000ms */
	//init_repetitive_timer_simplified(TIMER_1, 0, TIM_MS_TO_TICKS_SIMPLE(500), 10000, timer1_callback);
	//enable_timer(1, PRIO_3);
	
	/* Example: LEDs on for 250ms and off for 750ms */
	//init_infinite_timer_pwm(2, 0.25, 1000, timer2s_callback);
	//enable_timer(2, PRIO_3);
	
	/* Example: LEDs on for 250ms and off for 750ms for 10000ms  */
	//init_finite_timer_pwm(3, 0.25, 1000, 10000, timer3_callback);
	//enable_timer(3, PRIO_3);
	
	// power control register
	LPC_SC->PCON |= 0x1;			// PM0=1
	LPC_SC->PCON &= 0xFFFFFFFFD;	// PM1=0
	//execution of wfi or wfe assembly enters Power-Down mode when SLEEPDEEP is on
	
	// call asm function
	// ASM_func(VETT, N);
			
	while (1) {
		
		/*Finite State Machine*/
		switch(state){
			case STATE_IDLE:
			break;
			case STATE_RESET:
			break;
		}

		__ASM("wfi");
	}
}

/*
		if(btn_flag & FLAG_BUTTON_0_SHORT) {
			btn_flag &= ~FLAG_BUTTON_0_SHORT;
			// do stuff
		}
		if(btn_flag & FLAG_BUTTON_0_LONG) {
			btn_flag &= ~FLAG_BUTTON_0_LONG;
			// do stuff
		}
		if(btn_flag & FLAG_BUTTON_1_SHORT) {
			btn_flag &= ~FLAG_BUTTON_1_SHORT;
			// do stuff
		}
		if(btn_flag & FLAG_BUTTON_1_LONG) {
			btn_flag &= ~FLAG_BUTTON_1_LONG;
			// do stuff
		}
		if(btn_flag & FLAG_BUTTON_2_SHORT) {
			btn_flag &= ~FLAG_BUTTON_2_SHORT;
			// do stuff
		}
		if(btn_flag & FLAG_BUTTON_2_LONG) {
			btn_flag &= ~FLAG_BUTTON_2_LONG;
			// do stuff
		}
*/

/*
		// Joystick cmd, flags set at first edge
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
		// Buttons, flags set when released
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

/* Initialize SysTick using CMSIS Core_CM4 function */
static void InitSysTick(void){
	SysTick_Config(SystemFrequency/1000U); /* Configure the SysTick timer */
}
/* SysTick Interrupt Handler */
void SysTick_Handler(void){
	Sys_Tick++; /* increment timer */
}
/* Delay Function based on SysTick Counter */
void Delay_SysTick(uint32_t SysTicks){
	uint32_t DelayTimer_SysTick = Sys_GetTick() + SysTicks; /* Get End Tick */
	while(Sys_GetTick() < DelayTimer_SysTick); 				/* wait for timer */
}
/*Get Current Elapsed Ticks*/
uint32_t Sys_GetTick(void){
	return Sys_Tick;
}