//DS18B20温度读取
//#include <REGX52.H>
//#include "LCD1602.h"
//#include "DS18B20.h"
//#include "Delay.h"

//float T;

//void main()
//{
//	LCD_Init();
//	LCD_ShowString(1,1,"Temperature:");
//	
//	DS18B20_ConverT();
//	Delayxms(1000);
//	
//	while(1)
//	{
//		//若立刻读取温度，可能温度还没转化完导致读取到默认值，在程序开始时先转化一次然后延时1s即可
//		DS18B20_ConverT();	
//		T = DS18B20_ReadT();
//		if(T < 0)
//		{
//			LCD_ShowChar(2,1,'-');
//			T = -T;
//		}
//		else
//		{
//			LCD_ShowChar(2,1,'+');
//		}
//		LCD_ShowNum(2,2,T,3);	//精度丢失，显示整数位
//		LCD_ShowChar(2,5,'.');
//		LCD_ShowNum(2,6,(unsigned long)(T*10000)%10000,4);	//显示小数位
//	}
//}

//DS18B20温度报警器
#include <REGX52.H>
#include "LCD1602.h"
#include "DS18B20.h"
#include "Delay.h"
#include "AT24C02.h"
#include "IndependentKey.h"
#include "Timer0.h"

float T,TShow;
char TLow,THigh;
unsigned char KeyNum;

void main()
{
	THigh = AT24C02_ReadByte(0);
	TLow = AT24C02_ReadByte(1);
	if(THigh>125 || TLow<-55 || THigh<=TLow)	//不知道上一次存储的值是否符合温度上下限，所以判断一下设置默认值
	{
		THigh = 20;
		TLow = 15;
	}
	LCD_Init();
	Timer0_Init();
	LCD_ShowString(1,1,"T:");
	LCD_ShowString(2,1,"TH:");
	LCD_ShowString(2,9,"TL:");
	LCD_ShowSignedNum(2,4,THigh,3);
	LCD_ShowSignedNum(2,12,TLow,3);	
	
	DS18B20_ConverT();
	Delayxms(500);
	
	while(1)
	{
		KeyNum = Key();
		
		DS18B20_ConverT();
		T = DS18B20_ReadT();
		if(T < 0)
		{
			LCD_ShowChar(1,3,'-');
			TShow = -T;
		}
		else
		{
			LCD_ShowChar(1,3,'+');
			TShow = T;
		}
		LCD_ShowNum(1,4,TShow,3);	//精度丢失，显示整数位
		LCD_ShowChar(1,7,'.');
		LCD_ShowNum(1,8,(unsigned long)(TShow*100)%100,2);	//显示小数位
		
		if(KeyNum)	//按键按下时才刷新，节省资源
		{
			if(KeyNum == 1 && THigh <= 125)
			{
				THigh++;
			}
			if(KeyNum == 2)
			{
				THigh--;
				if(THigh <= TLow){THigh++;}
			}
			if(KeyNum == 3)
			{
				TLow++;
				if(TLow >= THigh){TLow--;}
			}
			if(KeyNum == 4 && TLow >= -55)
			{
				TLow--;
			}
			LCD_ShowSignedNum(2,4,THigh,3);
			LCD_ShowSignedNum(2,12,TLow,3);	
			AT24C02_WriteByte(0,THigh);
			Delayxms(5);
			AT24C02_WriteByte(1,TLow);
			Delayxms(5);
		}
		if(T > THigh)
		{
			LCD_ShowString(1,13,"OV:H");
		}
		else if(T < TLow)
		{
			LCD_ShowString(1,13,"OV:L");
		}
		else
		{
			LCD_ShowString(1,13,"    ");
		}
	}
}
//调用时会打断主函数，若主函数正在延时，会导致闪烁，但是关闭打开中断又会影响依靠中断的计时，根据实际情况选择
void Timer0_Routine() interrupt 1	//注意不能嵌套耗时的函数
{
	static unsigned int T0Count1;
	TL0 = 0x18;//设置定时初值
	TH0 = 0xFC;//设置定时初值
	T0Count1++;
	if(T0Count1 >= 20)	//每过20ms，过滤掉按键电平抖动
	{
		T0Count1=0;
		Key_Loop();
	}
}