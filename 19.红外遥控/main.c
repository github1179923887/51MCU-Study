//利用外部中断实现红外遥控
#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "IR.h"

unsigned char Num;
unsigned char Address;
unsigned char Command;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"ADDR  CMD  NUM");
	
	/*
	Timer0_Init();
	Timer0_SetCounter(0);
	Timer0_Run(1);				//开始计时
	Delayxms(1);
	Time = Timer0_GetCounter();	//获取计时
	LCD_ShowNum(2,1,Time,5);
	*/
	
	IR_Init();
	
	while(1)
	{
		if(IR_GetDataFlag() || IR_GetRepeatFlag())	//接收到数据信号或信号正在重复
		{
			Address = IR_GetAddress();
			Command = IR_GetCommand();
			if(Command == IR_VOLMINUS)
			{
				Num--;
			}
			if(Command == IR_VOLADD)
			{
				Num++;
			}
		}
		LCD_ShowHexNum(2,2,Address,2);
		LCD_ShowHexNum(2,7,Command,2);
		LCD_ShowNum(2,12,Num,3);
	}
}
