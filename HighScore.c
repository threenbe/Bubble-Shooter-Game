//HighScore.c
//This file has the three subroutines dealing with the high score table

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Random.h"
#include "TExaS.h"
#include "ADC.h"
#include "Sound.h"

extern int CurrentSelection;
extern int score;
extern void Delay100ms(uint32_t count);
extern const unsigned short MainMenu[];
extern const unsigned short HighScores[];

struct STable{
	char name[11];
	int highscore;
};
typedef struct STable HSTable_t;
HSTable_t HSTable[5] = {
	{{'M', 'a', 's', 't', 'e', 'r', 0, 0, 0, 0, 0}, 1000},
	{{'D', 'e', 'd', 'i', 'c', 'a', 't', 'e', 'd', 0, 0}, 750},
	{{'A', 'v', 'e', 'r', 'a', 'g', 'e', 0, 0, 0, 0}, 500},
	{{'N', 'o', 'v', 'i', 'c', 'e', 0, 0, 0, 0, 0}, 250},
	{{'N', 'o', 'o', 'b', 0, 0, 0, 0, 0, 0, 0}, 100}
};

/*****************HighScoreWrite*******************/

void HighScoreWrite(int place){//notifies player of high score, inserts score/name into HSTable
	ST7735_FillScreen(0); //highscore notif screen
	ST7735_SetCursor(5, 7);
	ST7735_SetTextColor(ST7735_CYAN);
	ST7735_OutString("High Score!");
	ST7735_SetTextColor(ST7735_YELLOW);
	//*********** add 'continue' button images***********
	ST7735_SetCursor(6, 14);
	ST7735_OutString("Continue");
	int i = 4; //moves the scores below the new score down
	while(i>place){
		int j = 0;
		while(j<10){
			HSTable[i].name[j] = HSTable[i-1].name[j];
			j++;}
		HSTable[i].highscore = HSTable[i-1].highscore;
		i--;}
	int k = 0;
	while(k<10){
		HSTable[place].name[k] = 0;
		k++;}
	HSTable[place].highscore = 0;
	
	while((GPIO_PORTE_DATA_R & 0x01) == 0){}
	while(GPIO_PORTE_DATA_R & 0x01){}
	ST7735_FillScreen(0); //sequence for entering/saving name/score
	ST7735_SetTextColor(ST7735_WHITE);
	ST7735_SetCursor(5, 1);
	ST7735_OutString("Enter your");
	ST7735_SetCursor(8, 2);
	ST7735_OutString("name:");
	ST7735_SetCursor(5, 15);
	ST7735_OutString("10 char max");
	ST7735_SetTextColor(ST7735_YELLOW);
	int count = 0;
	int LetterSelect = 0;	
	while(count<10){
		while((GPIO_PORTE_DATA_R & 0x01) == 0){
			LetterSelect = ADC_In()/152;
			if(LetterSelect != CurrentSelection){
				Sound_ScrollClick();
				CurrentSelection = LetterSelect;}
			ST7735_SetCursor(5+count, 7);
			if(LetterSelect==0){ST7735_OutChar('_');}
			else{
				if(count==0){ST7735_OutChar(LetterSelect+64);}
				else{ST7735_OutChar(LetterSelect+96);}}}
		Sound_ButtonClick();
		while(GPIO_PORTE_DATA_R & 0x01){}
		if(LetterSelect==0){
			ST7735_SetCursor(5+count, 7);
			ST7735_OutChar(' ');
			HSTable[place].name[count] = 32;}
		else{
			if(count==0){HSTable[place].name[count] = LetterSelect+64;}
			else{HSTable[place].name[count] = LetterSelect+96;}}
		Delay100ms(2);
		count++;}
	HSTable[place].highscore = score;
	ST7735_FillScreen(0);
}

/*****************HighScoreCheck*******************/

void HighScoreCheck(void){ //checks if score of recent game is a high score and returns the place (-1) it is
	int ret = -1;
	int i = 4;
	while(i>=0 && score>HSTable[i].highscore){
		ret = i;
		i--;}
	if(ret>-1){HighScoreWrite(ret);}
}


/*****************HighScoreRead*******************/

void HighScoreRead(void){ //reads HSTable and displays it
	ST7735_DrawBitmap(34, 20, HighScores, 60, 20);
	ST7735_SetTextColor(ST7735_WHITE);
	int i = 0;
	ST7735_SetCursor(1, 3);
	ST7735_OutString("1.");
	ST7735_SetCursor(1, 4);
	ST7735_OutString("2.");
	ST7735_SetCursor(1, 5);
	ST7735_OutString("3.");
	ST7735_SetCursor(1, 6);
	ST7735_OutString("4.");
	ST7735_SetCursor(1, 7);
	ST7735_OutString("5.");
	while(i<5){
		ST7735_SetTextColor(ST7735_WHITE);
		ST7735_SetCursor(4, i+3);
		ST7735_OutString(HSTable[i].name);
		ST7735_SetTextColor(ST7735_YELLOW);
		ST7735_SetCursor(16, i+3);
		ST7735_OutUDec(HSTable[i].highscore);
		i++;}
	ST7735_DrawBitmap(31, 155, MainMenu, 66, 21);
	while((GPIO_PORTE_DATA_R & 0x01) == 0){}
	Sound_ButtonClick();
	while(GPIO_PORTE_DATA_R & 0x01){}
	ST7735_FillScreen(0);
}
