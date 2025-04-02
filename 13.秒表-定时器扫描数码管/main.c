//���ö�ʱ�������ʱ���������CPUռ��
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

void Timer0_Routine() interrupt 1	//ע�ⲻ��Ƕ�׺�ʱ�ĺ���
{
	static unsigned int T0Count1,T0Count2,T0Count3;
	TL0 = 0x18;//���ö�ʱ��ֵ
	TH0 = 0xFC;//���ö�ʱ��ֵ
	T0Count1++;
	if(T0Count1 >= 20)	//ÿ��20ms�����˵�������ƽ����
	{
		T0Count1=0;
		Key_Loop();
	}
	T0Count2++;
	if(T0Count2 >= 2)	//ÿ��2ms����������ܻ���˸
	{
		T0Count2=0;
		NixieTube_Loop();
	}
	T0Count3++;
	if(T0Count3 >= 10)	//ÿ��10ms��MiniSec+1
	{
		T0Count3=0;
		Sec_Loop();
	}
}