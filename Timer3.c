//Timer3.c

#include <stdint.h>

#include "tm4c123gh6pm.h"

void (*PeriodicTask3)(void);   // user function

void Timer3_Init(void(*task)(void), uint32_t period){
	SYSCTL_RCGCTIMER_R |= 0x0008;	// 0) activate timer3
	PeriodicTask3 = task;					// user function
	TIMER3_CTL_R = 0x00000000;		// 1) disable timer3 during setup
	TIMER3_CFG_R = 0x00000000;		// 2) configure for 32-bit timer mode
	TIMER3_TAMR_R = 0x00000002;		// 3) configure for periodic mode
	TIMER3_TAILR_R = period-1;		// 4) reload value
	TIMER3_TAPR_R = 0;						// 5) 12.5ns timer3
	TIMER3_ICR_R = 0x00000001;		// 6+ clear timer3 timeout flag
	TIMER3_IMR_R = 0x00000001;		// 7) arm timeout interrupt
	NVIC_PRI8_R = (NVIC_PRI8_R&0x00FFFFFF)|0x40000000;	// 8) priority 
	NVIC_EN1_R = 1<<(35-32);			// 9) enable IRQ 35 in NVIC
	TIMER3_CTL_R |= 0x00000001;		// 10) enable timer3
}

void Timer3A_Handler(void){
	TIMER3_ICR_R = 0x00000001;		// acknowledge timer3 timeout
	(*PeriodicTask3)();
}
