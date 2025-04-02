//利用定时器完成延时的秒表，避免CPU占用
#include <REGX52.H>
#include "Delay.h"
#include "IndependentKey.h"
#include "Timer0.h"
#include "NixieTube.h"

unsigned char KeyNum,Min,Sec,MiniSec,RunFlag;

void main()
{
	Timer0_Init();
	while(1)
	{
		KeyNum = Key();
		if(KeyNum == 1)
		{
			RunFlag = !RunFlag;
		}
		if(KeyNum == 2)
		{
			RunFlag = 0;
			Min = Sec = MiniSec = 0;
		}
		NixieTube_SetBuf(1,Min/10);
		NixieTube_SetBuf(2,Min%10);
		NixieTube_SetBuf(3,11);
		NixieTube_SetBuf(4,Sec/10);
		NixieTube_SetBuf(5,Sec%10);
		NixieTube_SetBuf(6,11);
		NixieTube_SetBuf(7,MiniSec/10);
		NixieTube_SetBuf(8,MiniSec%10);
	}
}

void Sec_Loop()
{
	if(RunFlag)
	{
		MiniSec++;
		if(MiniSec >= 100)
		{
			MiniSec = 0;
			Sec++;
			if(Sec >= 60)
			{
				Sec = 0;
				Min++;
				if(Min >= 60)
				{
					Min = 0;
				}
			}
		}
	}
	
}

void Timer0_Routine() interrupt 1	//注意不能嵌套耗时的函数
{
	static unsigned int T0Count1,T0Count2,T0Count3;
	TL0 = 0x18;//设置定时初值
	TH0 = 0xFC;//设置定时初值
	T0Count1++;
	if(T0Count1 >= 20)	//每过20ms，过滤掉按键电平抖动
	{
		T0Count1=0;
		Key_Loop();
	}
	T0Count2++;
	if(T0Count2 >= 2)	//每过2ms，大了数码管会闪烁
	{
		T0Count2=0;
		NixieTube_Loop();
	}
	T0Count3++;
	if(T0Count3 >= 10)	//每过10ms，MiniSec+1
	{
		T0Count3=0;
		Sec_Loop();
	}
}