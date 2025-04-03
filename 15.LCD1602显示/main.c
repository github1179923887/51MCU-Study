#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"

void main()
{
	LCD_Init();
	LCD_ShowChar(1,1,'A');
	LCD_ShowString(1,3,"Hello!");
	LCD_ShowNum(1,10,66,2);
	LCD_ShowSignedNum(1,13,-88,2);
	LCD_ShowHexNum(2,1,0xA5,2);
	LCD_ShowBinNum(2,4,0xA5,8);
	LCD_ShowChar(2,13,0xDF);
	LCD_ShowChar(2,14,'C');
	LCD_ShowString(1,17,"Welcome to China");
	while(1)
	{
		Delayxms(500);
		LCD_WriteCommand(0x18);
	}
}
