//AT24C02数据存储及读取
#include <REGX52.H>
#include "LCD1602.h"
#include "IndependentKey.h"
#include "Delay.h"
#include "AT24C02.h"

unsigned char Data,KeyNum;
unsigned int Num;

void main()
{
	LCD_Init();
//	LCD_ShowString(1,1,"Hello");
	
//	AT24C02_WriteByte(1,147);
//	Delayxms(5);	//写周期需要5ms

//	Data = AT24C02_ReadByte(1);
//	LCD_ShowNum(2,1,Data,3);
	
	LCD_ShowNum(1,1,Num,5);
	
	while(1)
	{
		KeyNum = IndependentKey();
		if(KeyNum == 1)
		{
			Num++;
			LCD_ShowNum(1,1,Num,5);
		}
		if(KeyNum == 2)
		{
			Num--;
			LCD_ShowNum(1,1,Num,5);
		}
		if(KeyNum == 3)
		{
			//因为Num是十六位int，需要区分高低八位
			AT24C02_WriteByte(0,Num%256);
			Delayxms(5);
			AT24C02_WriteByte(1,Num/256);
			Delayxms(5);
			LCD_ShowString(2,1,"Write Finish");
			Delayxms(2000);
			LCD_ShowString(2,1,"            ");
		}
		if(KeyNum == 4)
		{
			//还原Num的十六位
			Num = AT24C02_ReadByte(0);
			Num |= AT24C02_ReadByte(1)<<8;
			
			LCD_ShowString(1,1,"Last Num:");
			LCD_ShowNum(1,10,Num,5);
			LCD_ShowString(2,1,"Read Finish");
			Delayxms(2000);
			LCD_ShowNum(1,1,Num,5);
			LCD_ShowString(1,6,"               ");
			LCD_ShowString(2,1,"           ");
		}
	}
}