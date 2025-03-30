//��������LED��ˮ�ƣ�ʹ�ö�ʱ����ֹռ��cpu��
//#include <REGX52.H>
//#include <INTRINS.H>
//#include "Timer0.h"
//#include "IndependentKey.h"

//unsigned char KeyNum,LEDMode;

//void main()
//{
//	P2 = 0xFE;
//	Timer0Init();
//	while(1)
//	{
//		KeyNum = IndependentKey();
//		if(KeyNum)
//		{
//			if(KeyNum == 1)
//			{
//				LEDMode++;
//				if(LEDMode >= 2)LEDMode = 0;
//			}
//		}
//	}
//}

////�ڴ˴�ִ������Ϊ��ʼ���󾭹�1ms��TF0=1�������ж�������ִ��
//void Timer0_Routine() interrupt 1	//��ʱ��0���жϺţ��ú����������Ҳ���ܵ���
//{
//	static unsigned int T0Count;
//	TL0 = 0x66;
//	TH0 = 0xFC;
//	T0Count++;
//	if(T0Count>=1000)	//����1000�Σ���1s
//	{
//		T0Count = 0;
//		if(LEDMode == 0)
//		{
//			P2 = _crol_(P2,1);	//���ƺ���
//		}
//		else if(LEDMode == 1)
//		{
//			P2 = _cror_(P2,1);	//���ƺ���
//		}
//	}
//	
//}

//��ʱ��ʱ��
#include <REGX52.H>
#include <INTRINS.H>
#include "Timer0.h"
#include "Delay.h"
#include "LCD1602.h"

unsigned char Hour,Min,Sec;

void main()
{
	LCD_Init();
	Timer0Init();
	
	LCD_ShowString(1,1,"Clock:");
	LCD_ShowString(2,1,"  :  :");
	
	while(1)
	{
		LCD_ShowNum(2,1,Hour,2);
		LCD_ShowNum(2,4,Min,2);
		LCD_ShowNum(2,7,Sec,2);
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x66;
	TH0 = 0xFC;
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count = 0;
		Sec++;
		if(Sec >= 60)
		{
			Sec = 0;
			Min++;
			if(Min >= 60)
			{
				Min = 0;
				Hour++;
				if(Hour >= 24)
				{
					Hour = 0;
				}
			}
		}
	}
	
}



