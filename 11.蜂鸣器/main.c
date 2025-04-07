//����������
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

//��������������
//ͨ������Ƶ�����鸳���жϺ����������ɣ��ص��������Ķ�Ӧ
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

void Timer0_Routine() interrupt 1	//ͨ������TL0��TH0������Ϊ1msִ��һ��
{
	TL0 = 0x18;//���ö�ʱ��ֵ
	TH0 = 0xFC;//���ö�ʱ��ֵ
	Buzzer = !Buzzer;
}

