// Bubbles.c
// This file will contain functions that randomize the initial state
// of the bubbles as well as the bubbles that are to be fired next

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Sound.h"
#define empty 0
#define redbub 1
#define yellowbub 2
#define greenbub 3
#define bluebub 4
#define whitebub 5
#define	purplebub	6
extern int16_t Bubbles[8][8];
extern int8_t n;
extern int16_t current;
extern int16_t next;
extern const unsigned short black[256];
extern const unsigned short *colorpt;
extern int8_t Level;
extern int MtDY(int x, int y);
extern int MtDX(int x, int y);
extern uint32_t Random32(void);
extern uint32_t Random(void);
extern int LevelClear(void);

void Load_Bubbles(void){
	uint32_t rand1 = Random();
	int32_t i;
	
	if(Level == 1){
		int16_t Type1 = (Random()%6)+1;
		int16_t Type2 = (Type1+3)%6+1;
		int16_t Type3 = (Type1+1)%6+1;
		Bubbles[0][0] = Type1;
		Bubbles[0][1] = Type2;
		Bubbles[0][2] = Type1;
		Bubbles[0][3] = Type1;
		Bubbles[0][4] = Type1;
		Bubbles[0][5] = Type1;
		Bubbles[0][6] = Type2;
		Bubbles[0][7] = Type1;
		Bubbles[1][2] = Type3;
		Bubbles[1][3] = Type3;
		Bubbles[1][4] = Type3;
	}
	
	else if(Level==2){
		int16_t Type1 = (Random()%6)+1;
		int16_t Type2 = (Type1+3)%6+1;
		int16_t Type3 = (Type1+1)%6+1;
		Bubbles[0][0] = Bubbles[0][1] = Bubbles[0][3] = Bubbles[0][4] = Bubbles[0][6] = Bubbles[0][7] = Type1;
		Bubbles[0][2] = Bubbles[0][5] = Type2;
		Bubbles[1][0] = Bubbles[1][3] = Bubbles[1][6] = Type3;
	}
	
	else if(Level==3){
		for(i=0;i<8;i++){
			Bubbles[0][i] = Bubbles[0][i+1] = (rand1%6)+1;
			rand1++;
		}
		Bubbles[1][2] = Bubbles[0][2];
		Bubbles[1][4] = Bubbles[0][4];
		Bubbles[1][3] = (rand1%6)+1;
	}
	
	else if(Level==4){
		uint32_t rand2 = rand1;
		for(i=1;i<7;i++){
			Bubbles[0][i] = (rand1%6)+1;
			rand1 += 1;
		}
		for(i=0;i<6;i++){
			Bubbles[1][i] = (rand2%6)+1;
			rand2 += 1;
		}
		Bubbles[0][7] = Bubbles[1][6] = Bubbles[0][1];
	}
	
	else if(Level==5){
			Bubbles[0][3] = Bubbles[0][4] = (rand1%6)+1;
	}
	
	else if(Level==6){
		for(i=0;i<6;i++){
			Bubbles[0][i] = (rand1%6)+1;
			rand1++;
		}
		Bubbles[0][6] = Bubbles[0][0];
		if(rand1%2){
			Bubbles[0][7] = Bubbles[0][2];
		} else {
			Bubbles[0][7] = Bubbles[0][4];
		}
	}
	
	else if(Level==7){
		for(i=0;i<8;i++){
			Bubbles[0][i] = (rand1%6)+1;
			rand1++;
		}
		rand1 = ((Bubbles[0][0]+2)%6)+1;
		for(i=0;i<4;i++){
			Bubbles[1][i] = (rand1%6)+1;
			rand1 += 2;
		}
		Bubbles[1][4] = Bubbles[0][0];
		Bubbles[1][5] = Bubbles[1][1];
		Bubbles[1][6] = Bubbles[0][2];
	}
	
	else if(Level==9){
		Bubbles[0][1] = Bubbles[0][4] = Bubbles[0][7] = (rand1%6)+1;
		rand1 += 2;
		for(i=0;i<8;i++){
			if(i != 1 && i!= 4 && i!= 7){
				Bubbles[0][i] = (rand1%6)+1;
			}
		}
		rand1++;
		Bubbles[1][2] = Bubbles[1][5] = (rand1%6)+1;
		rand1 += 2;
		for(i=0;i<7;i++){
			if(i != 2 && i != 5){
				Bubbles[1][i] = (rand1%6)+1;
			}
		}
		rand1 += 2;
		for(i=1;i<8;i+=2){
			Bubbles[2][i] = (rand1%6)+1;
		}
	}
	else if(Level==8 || Level==10){
		Bubbles[0][3] = (rand1%6)+1;
		Bubbles[0][4] = ((rand1+1)%6)+1;
		Bubbles[1][2] = ((rand1+5)%6)+1;
		if(Level==8){Bubbles[1][3] = ((rand1+5)%6)+1;}
		else if(Level==10){Bubbles[1][3] = ((rand1+2)%6)+1;}
		Bubbles[1][4] = ((rand1+4)%6)+1;
		Bubbles[2][3] = ((rand1+3)%6)+1;
		Bubbles[2][4] = ((rand1+2)%6)+1;
		Bubbles[3][3] = ((rand1+4)%6)+1;
		Bubbles[3][4] = ((rand1+3)%6)+1;
		if(Level==10){
			Bubbles[4][4] = (rand1%6)+1;
			Bubbles[4][3] = ((rand1+2)%6)+1;
			Bubbles[4][5] = ((rand1+1)%6)+1;
		}
	}
	
	else if(Level==11){
		Bubbles[0][1] = (rand1%6)+1;
		Bubbles[1][1] = ((rand1+1)%6)+1;
		Bubbles[2][2] = ((rand1+2)%6)+1;
		Bubbles[1][2] = ((rand1+3)%6)+1;
		Bubbles[0][3] = ((rand1+4)%6)+1;
		Bubbles[0][4] = ((rand1+5)%6)+1;
		rand1 = Bubbles[0][4];
		while(rand1 == Bubbles[0][4]){ rand1 = (Random()%6)+1; }
		Bubbles[1][4] = (rand1%6)+1;
		Bubbles[2][5] = ((rand1+1)%6)+1;
		Bubbles[1][5] = ((rand1+2)%6)+1;
		Bubbles[0][6] = ((rand1+3)%6)+1;
	}
	else if(Level==12){
		for(i=0;i<8;i++){
			Bubbles[0][i] = (rand1%6)+1;
			rand1++;
		}
		for(i=0;i<7;i++){
			Bubbles[1][i] = (rand1%6)+1;
			rand1++;
		}
	}
} 

void Display_Bubbles(void){
	int i,k;
	int16_t color;
	for(i=0;i<(8-n);i++){
		if(i%2 == 0){//even row (e.g. 0, 2, etc.)
			for(k=0;k<8;k++){
				color = Bubbles[i][k];
				if(!color){ ST7735_DrawBitmap(MtDX(k,i), MtDY(k,i), black, 16, 16); ST7735_DrawFastHLine(0, 112, 128, 0x20FD); continue;}
				ST7735_DrawBitmap(MtDX(k,i), MtDY(k,i), (colorpt+256*(color+10)), 16, 16);
				ST7735_DrawFastHLine(0, 112, 128, 0x20FD);
			}
		} else if(i%2 == 1){//odd row (e.g. 1, 3, etc.)
				for(k=0;k<7;k++){
					color = Bubbles[i][k];
					if(!color){ ST7735_DrawBitmap(MtDX(k,i), MtDY(k,i), black, 16, 16); ST7735_DrawFastHLine(0, 112, 128, 0x20FD); continue;}
					ST7735_DrawBitmap(MtDX(k,i), MtDY(k,i), (colorpt+256*(color+10)), 16, 16);
					ST7735_DrawFastHLine(0, 112, 128, 0x20FD);
				}
			}
		
		}
		for(i=(1+n);i<8;i+=2){
		ST7735_DrawBitmap(0, ((i+1)*16)-1, black, 8, 16);
		ST7735_DrawBitmap(120, ((i+1)*16)-1, black, 8, 16);
					
	}
}

void Bubbles_Init(void){
	if(Level==5){current = 11;}
	else{current = (Random()%6)+1;}
	next = (Random()%6)+1;
	ST7735_DrawBitmap(24, 159, (colorpt+256*(current+10)), 16, 16);
	ST7735_DrawBitmap(5, 159, (colorpt+256*(next+10)), 16, 16);
}

void Bubbles_Update_Refresh(void){
	ST7735_DrawBitmap(24, 159, (colorpt+256*(current+10)), 16, 16);
	ST7735_DrawBitmap(5, 159, (colorpt+256*(next+10)), 16, 16);
}

void Bubbles_Update(void){
	int i,k;
	int b[6] = {0};
	uint8_t r;
	r = Random();
	
	current = 
	next;

/*
1 = Fire
2 = Light
3 = Earth
4 = Water
5 = Air
6 = Dark
7 = Bomb
8 = Wild
9 = Random
10 = Insertion
11 = YerraBubble
*/
	
	//special bubbles
	if(r>=60 && r<=62){next = 7;}
	else if(r>=62 && r<=65){next = 10;}
	else if(r>=126 && r<=131){next = 8;}
	else if(r>=192 && r<=194){next = 9;}
	else if(r==225){next = 11;}
	//normal bubbles
	else if(((r>0&&r<=59)||(r>=66&&r<=125)||(r>=132&&r<=191)||(r>=195&&r<=224)||(r>=226&&r<=255))&&(Level<11))
		{
		//The b array keeps track of which bubbles are still on-screen,
		//the point of this is to have the game tend to give players
		//bubbles that are actually on-screen for these earlier levels,
		//as the game can get unfair when there are only a few bubbles left
		//and the player gets unlucky and gets many unhelpful bubbles.
		//In later this is not implemented to boost difficulty.
		for(i=0;i<8;i++){
			for(k=0;k<8;k++){
				if(Bubbles[i][k] == 1){b[0] = 1;}
				else if(Bubbles[i][k] == 2){b[1] = 1;}
				else if(Bubbles[i][k] == 3){b[2] = 1;}
				else if(Bubbles[i][k] == 4){b[3] = 1;}
				else if(Bubbles[i][k] == 5){b[4] = 1;}
				else if(Bubbles[i][k] == 6){b[5] = 1;}
			}
		}
		//if there's only one type of bubble on-screen, then we do ensure
		//that there's not just one possibility for the next bubble, otherwise
		//it becomes *too* easy - we only apply this to some higher levels though
		if(Level>7){
		if((b[0]+b[1]+b[2]+b[3]+b[4]+b[5]) == 1){
			while(1){
				i = Random()%6;
				if(b[i] == 0){ 
					b[i] = 1;
					break;
				}
			}
		}}
		
		next = (r%6)+1;
		if(LevelClear()==0){
		for(i=0;i<6;i++){
			if((b[i] == 0) && (next == (i+1))){//say i=0 and b[i] is not set, this means that there are no fire bubbles so next shouldn't be fire
				next = (Random()%6)+1;
				i = -1;
			}
		}
	}}
	else{
		current = next;
		next = (r%6)+1;
	}
	
	Bubbles_Update_Refresh();
}
