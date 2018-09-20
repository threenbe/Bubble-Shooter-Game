// Clear.c 

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Bubbles.h"
#include "Sound.h"
#include "SpecialCombos.h"
#define empty 0
#define redbub 1
#define yellowbub 2
#define greenbub 3
#define bluebub 4
#define whitebub 5
#define	purplebub	6
extern int16_t Bubbles[8][8];
extern uint8_t n;
extern int16_t current;
extern const unsigned short *colorpt;
extern void Delay100ms(uint32_t count);
extern int score;
extern const unsigned short black[256];

int16_t yclear[100];
int16_t xclear[100];

struct fall{
	uint16_t fallcount;
	uint16_t fallcolor[100];
	int16_t y_arr[100];
	int16_t x_arr[100];
	int8_t fall_flag1;
	int8_t fall_flag2;
};
typedef struct fall fall_t;
extern fall_t fall1;

/*****************Find_Fall*************************
After Find_Clear takes care of combos, this function
should be called in order to take care of bubbles that 
are no longer connected to the ceiling in any way, making
them fall. Bubbles that fall as opposed to getting cleared
via combos should be worth more points as well.
Inputs: count, which should be the number of bubbles cleared,
used for score calculation 
Outputs: none
*/
void Find_Fall(void){
	Delay100ms(1);
	int16_t i,k;
	int16_t ycheck1, xcheck1, ycheck2, xcheck2;
	//used to check surrounding bubbles
	int16_t yeven[6] = {-1, -1, 1, 1, 0, 0};
	int16_t xeven[6] = {0, -1, -1, 0, 1, -1};
	int16_t yodd[6] = {0, 0, -1, -1, 1, 1};
	int16_t xodd[6] = {-1, 1, 0, 1, 1, 0};
	
	int16_t ycheckarr[100];
	int16_t xcheckarr[100];
	
	//checks for bubbles that should fall
	//if coordinate is 1, it won't fall 
	int16_t FallMatrix[8][8] = {{0}};
	for(i=0;i<8;i++){
		FallMatrix[0][i] = 1;
	}
	
	uint8_t count1 = 0, count2 = 0;

	for(i=0;i<8;i++){
		ycheck1 = 0;
		xcheck1 = i;
		if(Bubbles[0][i] != 0){//if there's still a bubble in this top coordinate
			while(1){
				for(k=0;k<6;k++){
					if(ycheck1%2 == 0){
						ycheck2 = ycheck1 + yeven[k];
						xcheck2 = xcheck1 + xeven[k];
					}	else if(ycheck1%2 == 1){
						ycheck2 = ycheck1 + yodd[k];
						xcheck2 = xcheck1 + xodd[k];
					}
					//make sure coordinates are valid, contain a bubble, and haven't been checked yet
					if(ycheck2>0 && ycheck2<8 && xcheck2>-1 && xcheck2<8 && FallMatrix[ycheck2][xcheck2] == 0 && Bubbles[ycheck2][xcheck2] != 0){
						FallMatrix[ycheck2][xcheck2] = 1;
						ycheckarr[count1] = ycheck2;
						xcheckarr[count1] = xcheck2;
						count1++;
					}
				}
				if(count1 > count2){
					ycheck1 = ycheckarr[count2];
					xcheck1 = xcheckarr[count2];
					count2++;
				}	else{break;}
			}
		}
	}
	fall1.fallcount = 0;
	for(i=1;i<8;i++){//rows
		for(k=0;k<8;k++){//columns, k*16+8, (i+n)*16+15
			if(FallMatrix[i][k] == 0 && Bubbles[i][k] != 0){
				fall1.y_arr[fall1.fallcount] = (i+n)*16+15;
				if(i%2 == 0){fall1.x_arr[fall1.fallcount] = k*16;}
				else if(i%2 == 1){fall1.x_arr[fall1.fallcount] = k*16+8;}
				fall1.fallcolor[fall1.fallcount] = Bubbles[i][k];
				Bubbles[i][k] = 0;
				fall1.fallcount++;
			}
		}
	}
	
	//if there are bubbles that need to fall, set flag to trigger interrupt to
	//make it happen 
	if(fall1.fallcount){
		for(i=0;i<fall1.fallcount;i++){
		score += (i+1)*2;
		ST7735_DrawBitmap(fall1.x_arr[i], fall1.y_arr[i], black, 16, 16);
		fall1.fall_flag1 = 1;
		}
	}
}


/*****************Find_Clear************************
Take a y,x input based on where the ball ended up 
y,x will correspond to spots in the matrix
Find matches, if >2, clear, if >3, special combo
Inputs: coordinates of the bubble last fired (in terms of 
the 2D array that holds the 'state' of each bubble spot on the 
hexagonal grid)
Outputs: none
*/

void Find_Clear(int16_t y, int16_t x){
	// used to check bubbles surrounding the one last shot
	int16_t yeven[6] = {-1, -1, 1, 1, 0, 0};
	int16_t xeven[6] = {0, -1, -1, 0, 1, -1};
	int16_t yodd[6] = {0, 0, -1, -1, 1, 1};
	int16_t xodd[6] = {-1, 1, 0, 1, 1, 0};
	
	//	coordinates of bubble being checked
	int16_t ycheck1 = y;
	int16_t xcheck1 = x;	
	//	coordinates of surrounding bubbles 
	int16_t ycheck2, xcheck2;
	//	coordinates of all bubbles to clear will go here
	yclear[0] = y;
	xclear[0] = x;
/*
	count1 keeps track of how many like-color bubbles we have,
	count2 is used to ensure that all matches to the 
	original bubble get checked as well
*/
	uint8_t count1 = 1, count2 = 1;
	//2 indexes and a flag
	uint8_t i, k, a=0;

	while(1){
		for(i=0;i<6;i++){//6 positions to check
			
			// set xcheck2,ycheck2 to surrounding bubble coordinates
			if((ycheck1%2) == 0){// if y is even (e.g. row 0, 2, etc.)
				ycheck2 = ycheck1+yeven[i];
				xcheck2 = xcheck1+xeven[i];
			} else if((ycheck1%2) == 1){// else if y is odd (e.g. row 1, 3, etc.)
				ycheck2 = ycheck1+yodd[i];
				xcheck2 = xcheck1+xodd[i];
			}
			
			// make sure coordinates are valid
			if(ycheck2>-1 && ycheck2<8 && xcheck2>-1 && xcheck2<8){
				// make sure coordinates have not already been checked
				for(k=0;k<count1;k++){
						if(yclear[k] == ycheck2 && xclear[k] == xcheck2){a=1; break;}
					}
				// if the coordinates are found, skip to the next iteration of the loop
				if(a==1){a=0; continue;}
				
				//check for a match
				if(Bubbles[ycheck2][xcheck2] == Bubbles[ycheck1][xcheck1]){
					yclear[count1] = ycheck2;
					xclear[count1] = xcheck2;
					count1++;
				}
			}
		}
	/*
	if count1 is greater than count 2, then this means that
	we got some matches, so those matches need to be checked;
	if count1 == count2, then that means during our last run we
	didn't find any matches, meaning that there are no more 
	additional bubbles to check for additional matches
	*/
		if(count1 > count2){
			ycheck1 = yclear[count2];
			xcheck1 = xclear[count2];
			count2++;
		}	else {break;}
	}
	
	if(count1 == 3){
		Sound_BubblePop();
		for(i=0;i<count1;i++){
			Bubbles[yclear[i]][xclear[i]] = 0;
		}
		Display_Bubbles();
		score += count1;
	}
	if(count1 > 3){
		SpecialComboPerform(count1);
	}
}
