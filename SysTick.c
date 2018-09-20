// SysTick.c 

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Sound.h"

void EnableInterrupts(void);

void SysTick_Init(uint32_t period){
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = period - 1;
	NVIC_ST_CURRENT_R = 0;
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x80000000;
	NVIC_ST_CTRL_R = 0x00000007;
	EnableInterrupts();
}

void SysTick_Handler(void){
	Sound_Play();
}
