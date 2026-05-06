#include "ekranas.h"
#include "ssd1306.h"
#include "fonts.h"
#include <stdio.h>

extern I2C_HandleTypeDef hi2c1;  
extern volatile float RMS, a;                    
extern int dispflag, clipping, gainflag, stop, i;

static char string_display[30];

void izanga(){
	ssd1306_SetCursor(0,0);
	ssd1306_WriteString("ITERPTINIU",Font_11x18, White);
	
	ssd1306_SetCursor(0,18);
	ssd1306_WriteString("PROJEKTAS",Font_11x18, White);
	
	ssd1306_SetCursor(10,50);
	ssd1306_WriteString("zmogus",Font_7x10, White);
	

	ssd1306_UpdateScreen(&hi2c1);

}

void TRMS(){	
	
	if(dispflag == 0){
	ssd1306_Fill(Black);
	dispflag = 2;
	}
	
	ssd1306_SetCursor(0, 18);
	sprintf(string_display, "Vrms= %.2fV", RMS);
  ssd1306_WriteString(string_display,Font_11x18, White);

  ssd1306_UpdateScreen(&hi2c1);
	
}

void Vout(){
	
	ssd1306_SetCursor(0, 0);
	sprintf(string_display, "Vout= %.2fV", a);
  ssd1306_WriteString(string_display,Font_11x18, White);
		
	if(gainflag == 1 && stop == 0){
		ssd1306_SetCursor(0, 50);
		sprintf(string_display, "15x");
		ssd1306_WriteString(string_display,Font_7x10, White);
		stop = 1;

	}
	if(gainflag == 0 && stop == 0){
		ssd1306_FillRect(0, 50, 21, 10, Black);
		stop = 1;
	}
	ssd1306_UpdateScreen(&hi2c1);
}

void CLIP(){
	if(dispflag ==2){
	if(clipping == 0){
	ssd1306_SetCursor(20,45);
	ssd1306_WriteString("CLIPPING",Font_11x18, White);
	
	ssd1306_SetCursor(0, 0);
	sprintf(string_display, "Vout= %.2fV", a);
  ssd1306_WriteString(string_display,Font_11x18, White);

	}
	
	if(clipping == 1){
		
	ssd1306_FillRect(20, 45, 90, 15, Black);

	}
	
	ssd1306_UpdateScreen(&hi2c1);
	}
}