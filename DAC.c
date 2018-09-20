// put implementations for functions, explain how it works
// put your names here, date

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Random.h"
#include "TExaS.h"

void DAC_Init(void){uint32_t volatile delay;
	SYSCTL_RCGC2_R |= 0x02;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTB_DIR_R |= 0x3F; // bits 7-2 output
	GPIO_PORTB_AFSEL_R &= ~0x3F;
	GPIO_PORTB_DEN_R |= 0x3F;
}

void DAC_Out(uint32_t data){
	data = data;
	GPIO_PORTB_DATA_R = data;
}
