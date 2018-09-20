#include <stdint.h>
#include "ST7735.h"
#include "TExaS.h"
#include "ADC.h"
#include "print.h"
#include "tm4c123gh6pm.h"

extern int CannonAim;
extern const unsigned short Cannon30deg;


void Aim(void){
	uint32_t Data = ADC_In();
	CannonAim = Data/316;
		
	}
