#include <REGX52.H>
#include "Timer1.h"
#include "NixieTube.h"
#include "IndependentKey.h"

sbit Motor = P1^0;

unsigned char Counter,Compare;

void Motor_Init()
{
	Timer1_Init();
}

void Motor_SetSpeed(unsigned char Speed)
{
	Compare = Speed;
}

void Timer1_Routine() interrupt 3
{
	static unsigned int T1Count1,T1Count2;
	TL1 = 0xA4;		//设置定时初值
	TH1 = 0xFF;		//设置定时初值
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
	T1Count1++;
	if(T1Count1 >= 20)
	{
		T1Count1=0;
		NixieTube_Loop();
	}
	T1Count2++;
	if(T1Count2 >= 200)
	{
		T1Count2=0;
		Key_Loop();
	}
}