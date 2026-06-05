#include <lpc21xx.h>
#include "delay.h"
#include "LCD.h"
#include "KPM.h"
#include "Score.h"

int main()
{
	init_LCD();      // Initialize LCD display

	init_KPM();      // Initialize keypad module
	
	init_Match();    // Initialize match variables and settings

	IPL_intro_UI();  // Display IPL welcome screen
	
	cmd_LCD(0x01);   // Clear LCD
	
	TOSS();          // Perform toss and select batting team
	
	while(1)
	{
		Score();          // Update and display match score

		change_bowler();  // Change bowler when over is completed

		Winner();         // Check for match winner

		if(win) break;    // Exit when match is finished
	}
}
