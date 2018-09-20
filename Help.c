//Help.c
//subroutine called by the main menu, as well as one for each help page

#include "Sound.h"
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Random.h"
#include "TExaS.h"
#include "ADC.h"

extern int CurrentSelection;
extern const unsigned short *cannonpt;
extern const unsigned short *colorpt;
extern const unsigned short MainMenu[];
extern const unsigned short Help[];

void Page1(void){
	ST7735_SetCursor(7, 1);
	ST7735_OutString("  1/11 >");
	ST7735_SetCursor(4, 3);
	ST7735_OutString("Aim the cannon");
	ST7735_SetCursor(4, 4);
	ST7735_OutString("with the slide");
	ST7735_SetCursor(5, 5);
	ST7735_OutString("and fire by");
	ST7735_SetCursor(5, 6);
	ST7735_OutString("pressing the");
	ST7735_SetCursor(8, 7);
	ST7735_OutString("button.");
	ST7735_DrawBitmap(40, 130, (cannonpt+1152*15), 48, 24);
}

void Page2(void){
	ST7735_SetCursor(7, 1);
	ST7735_OutString("< 2/11 >");
	ST7735_SetCursor(3, 3);
	ST7735_OutString("Clear each level");
	ST7735_SetCursor(5, 4);
	ST7735_OutString("by matching");
	ST7735_SetCursor(4, 5);
	ST7735_OutString("three or more");
	ST7735_SetCursor(3, 6);
	ST7735_OutString("adjacent baubles");
	ST7735_SetCursor(3, 7);
	ST7735_OutString("of the same type.");
	ST7735_DrawBitmap(56, 130, (colorpt+256*11), 16, 16);
	ST7735_DrawBitmap(40, 130, (colorpt+256*11), 16, 16);
	ST7735_DrawBitmap(72, 130, (colorpt+256*11), 16, 16);
}

void Page3(void){
	ST7735_SetCursor(7, 1);
	ST7735_OutString("< 3/11 >");
	ST7735_SetCursor(3, 3);
	ST7735_OutString("Upcoming baubles");
	ST7735_SetCursor(5, 4);
	ST7735_OutString("are shown in");
	ST7735_SetCursor(3, 5);
	ST7735_OutString("the bottom left.");
	ST7735_SetCursor(3, 7);
	ST7735_OutString("Clear the screen");
	ST7735_SetCursor(2, 8);
	ST7735_OutString("with as few shots");
	ST7735_SetCursor(3, 9);
	ST7735_OutString("as possible, as");
	ST7735_SetCursor(2, 10);
	ST7735_OutString("the ceiling drops");
	ST7735_SetCursor(3, 11);
	ST7735_OutString("every few shots!");
}


void Page4(void){
	ST7735_SetCursor(7, 1);
	ST7735_OutString("< 4/11 >");
	ST7735_SetCursor(4, 3);
	ST7735_OutString("Matching four");
	ST7735_SetCursor(3, 4);
	ST7735_OutString("or more baubles");
	ST7735_SetCursor(2, 5);
	ST7735_OutString("triggers a special");
	ST7735_SetCursor(5, 6);
	ST7735_OutString("effect based");
	ST7735_SetCursor(4, 7);
	ST7735_OutString("on the type of");
	ST7735_SetCursor(4, 8);
	ST7735_OutString("bauble matched.");
	ST7735_DrawBitmap(64, 130, (colorpt+256*11), 16, 16);
	ST7735_DrawBitmap(48, 130, (colorpt+256*11), 16, 16);
	ST7735_DrawBitmap(32, 130, (colorpt+256*11), 16, 16);
	ST7735_DrawBitmap(80, 130, (colorpt+256*11), 16, 16);
}

void Page5(void){
	ST7735_SetCursor(7, 1);
	ST7735_OutString("< 5/11 >");
	ST7735_SetCursor(5, 2);
	ST7735_OutString("Combo Types");
	ST7735_SetCursor(1, 4);
	ST7735_OutString("Fire: Removes");
	ST7735_SetCursor(1, 5);
	ST7735_OutString("all baubles");
	ST7735_SetCursor(1, 6);
	ST7735_OutString("adjacent to");
	ST7735_SetCursor(1, 7);
	ST7735_OutString("the combo.");
	ST7735_SetCursor(1, 9);
	ST7735_OutString("Light: Turns");
	ST7735_SetCursor(1, 10);
	ST7735_OutString("all adjacent");
	ST7735_SetCursor(1, 11);
	ST7735_OutString("baubles into");
	ST7735_SetCursor(1, 12);
	ST7735_OutString("a random type.");
	ST7735_DrawBitmap(104, 66, (colorpt+256*11), 16, 16);
	ST7735_DrawBitmap(104, 116, (colorpt+256*12), 16, 16);
}

void Page6(void){
	ST7735_SetCursor(7, 1);
	ST7735_OutString("< 6/11 >");
	ST7735_SetCursor(5, 2);
	ST7735_OutString("Combo Types");
	ST7735_SetCursor(1, 4);
	ST7735_OutString("Earth: Causes");
	ST7735_SetCursor(1, 5);
	ST7735_OutString("the ceiling");
	ST7735_SetCursor(1, 6);
	ST7735_OutString("to fall an");
	ST7735_SetCursor(1, 7);
	ST7735_OutString("extra level.");
	ST7735_SetCursor(1, 9);
	ST7735_OutString("Water: Removes");
	ST7735_SetCursor(1, 10);
	ST7735_OutString("ALL water type");
	ST7735_SetCursor(1, 11);
	ST7735_OutString("baubles on the");
	ST7735_SetCursor(1, 12);
	ST7735_OutString("screen.");
	ST7735_DrawBitmap(104, 66, (colorpt+256*13), 16, 16);
	ST7735_DrawBitmap(104, 116, (colorpt+256*14), 16, 16);
}

void Page7(void){
	ST7735_SetCursor(7, 1);
	ST7735_OutString("< 7/11 >");
	ST7735_SetCursor(5, 2);
	ST7735_OutString("Combo Types");
	ST7735_SetCursor(1, 4);
	ST7735_OutString("Wind: Fills");
	ST7735_SetCursor(1, 5);
	ST7735_OutString("the combo's");
	ST7735_SetCursor(1, 6);
	ST7735_OutString("rows with");
	ST7735_SetCursor(1, 7);
	ST7735_OutString("bubbles.");
	ST7735_SetCursor(1, 9);
	ST7735_OutString("Dark: Combo");
	ST7735_SetCursor(1, 10);
	ST7735_OutString("turns into");
	ST7735_SetCursor(1, 11);
	ST7735_OutString("baubles of");
	ST7735_SetCursor(1, 12);
	ST7735_OutString("random types.");
	ST7735_DrawBitmap(104, 66, (colorpt+256*15), 16, 16);
	ST7735_DrawBitmap(104, 116, (colorpt+256*16), 16, 16);
}

void Page8(void){
	ST7735_SetCursor(7, 1);
	ST7735_OutString("< 8/11 >");
	ST7735_SetCursor(6, 3);
	ST7735_OutString("There are");
	ST7735_SetCursor(5, 4);
	ST7735_OutString("also special");
	ST7735_SetCursor(5, 5);
	ST7735_OutString("baubles that");
	ST7735_SetCursor(4, 6);
	ST7735_OutString("have their own");
	ST7735_SetCursor(4, 7);
	ST7735_OutString("unique effects.");
}

void Page9(void){//bomb/antibomb
	ST7735_SetCursor(7, 1);
	ST7735_OutString("< 9/11 >");
	ST7735_SetCursor(3, 2);
	ST7735_OutString("Special Baubles");
	ST7735_SetCursor(1, 4);
	ST7735_OutString("Bomb: Destroys");
	ST7735_SetCursor(1, 5);
	ST7735_OutString("nearby baubles.");
	ST7735_SetCursor(1, 9);
	ST7735_OutString("Antibomb: Adds");
	ST7735_SetCursor(1, 10);
	ST7735_OutString("random baubles");
	ST7735_SetCursor(1, 11);
	ST7735_OutString("nearby.");
	ST7735_DrawBitmap(104, 66, (colorpt+256*17), 16, 16);
	ST7735_DrawBitmap(104, 116, (colorpt+256*20), 16, 16);
}

void Page10(void){//wild/randomizer
	ST7735_SetCursor(6, 1);
	ST7735_OutString("< 10/11 >");
	ST7735_SetCursor(3, 2);
	ST7735_OutString("Special Baubles");
	ST7735_SetCursor(1, 4);
	ST7735_OutString("Wild: Turns");
	ST7735_SetCursor(1, 5);
	ST7735_OutString("into the");
	ST7735_SetCursor(1, 6);
	ST7735_OutString("bauble type");
	ST7735_SetCursor(1, 7);
	ST7735_OutString("that it hits.");
	ST7735_SetCursor(1, 9);
	ST7735_OutString("Randomizer:");
	ST7735_SetCursor(1, 10);
	ST7735_OutString("Turns nearby");
	ST7735_SetCursor(1, 11);
	ST7735_OutString("baubles into");
	ST7735_SetCursor(1, 12);
	ST7735_OutString("random types.");
	ST7735_DrawBitmap(104, 66, (colorpt+256*18), 16, 16);
	ST7735_DrawBitmap(104, 116, (colorpt+256*19), 16, 16);
}

void Page11(void){//yerrabubble
	ST7735_SetCursor(6, 1);
	ST7735_OutString("< 11/11");
	ST7735_SetCursor(3, 2);
	ST7735_OutString("Special Baubles");
	ST7735_SetCursor(9, 7);
	ST7735_OutString("???");
	ST7735_DrawBitmap(55, 96, (colorpt+256*21), 16, 16);
}

void HelpScreens(void){
	int HelpSelect = 1;
	CurrentSelection = -1;
	ST7735_DrawBitmap(34, 20, Help, 60, 20);
	ST7735_SetCursor(7, 5);
	ST7735_OutString("Move the");
	ST7735_SetCursor(4, 6);
	ST7735_OutString("slide all the");
	ST7735_SetCursor(7, 7);
	ST7735_OutString("way left.");
	while(HelpSelect){HelpSelect = ADC_In()/300;}
	while((GPIO_PORTE_DATA_R & 0x01) == 0){
		HelpSelect = ADC_In()/405;
		if(HelpSelect != CurrentSelection){
			Sound_ScrollClick();
			ST7735_FillScreen(0);
			ST7735_DrawBitmap(31, 155, MainMenu, 66, 21);
			CurrentSelection = HelpSelect;
			if(HelpSelect == 0){Page1();}
			if(HelpSelect == 1){Page2();}
			if(HelpSelect == 2){Page3();}
			if(HelpSelect == 3){Page4();}
			if(HelpSelect == 4){Page5();}
			if(HelpSelect == 5){Page6();}
			if(HelpSelect == 6){Page7();}
			if(HelpSelect == 7){Page8();}
			if(HelpSelect == 8){Page9();}
			if(HelpSelect == 9){Page10();}
			if(HelpSelect == 10){Page11();}
		}
	}
	Sound_ButtonClick();
	while(GPIO_PORTE_DATA_R & 0x01){}
	ST7735_FillScreen(0);
}
