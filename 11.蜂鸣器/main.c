//蜂鸣器发声
#include <REGX52.H>
#include "Delay.h"
#include "NixieTube.h"
#include "IndependentKey.h"
#include "Buzzer.h"

unsigned char KeyNum;

void main()
{
	NixieTube(1,0);
	while(1)
	{
		KeyNum = IndependentKey();
		if(KeyNum)
		{
			Buzzer_Time(100);
			NixieTube(1,KeyNum);
		}
	}
}

//蜂鸣器播放音乐
//通过音乐频率数组赋予中断函数产生旋律，重点在索引的对应
#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"

sbit Buzzer = P2^5;

void main()
{
	Timer0Init();
	while(1)
	{
		
	}
}

void Timer0_Routine() interrupt 1	//通过设置TL0和TH0，设置为1ms执行一次
{
	TL0 = 0x18;//设置定时初值
	TH0 = 0xFC;//设置定时初值
	Buzzer = !Buzzer;
}

