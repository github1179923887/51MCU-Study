//直流电机调速
#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"
#include "NixieTube.h"
#include "IndependentKey.h"

sbit Motor = P1^0;

unsigned char Counter,Compare;
unsigned char KeyNum,Speed;

void main()
{
	Timer0_Init();
	Compare = 5;
	while(1)
	{
		KeyNum = Key();
		if(KeyNum == 1)
		{
			Speed++;
			Speed%=4;
			if(Speed == 0){Compare = 0;}
			if(Speed == 1){Compare = 50;}
			if(Speed == 2){Compare = 75;}
			if(Speed == 3){Compare = 100;}
		}
		NixieTube_SetBuf(1,Speed);
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count1,T0Count2;
	TL0 = 0xA4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	Counter++;
	Counter%=100;
	if(Counter < Compare)
	{
		Motor = 1;
	}
	else
	{
		Motor = 0;
	}
	T0Count1++;
	if(T0Count1 >= 20)
	{
		T0Count1=0;
		NixieTube_Loop();
	}
	T0Count2++;
	if(T0Count2 >= 200)
	{
		T0Count2=0;
		Key_Loop();
	}
}