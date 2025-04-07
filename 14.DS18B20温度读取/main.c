//DS18B20�¶ȶ�ȡ
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
//		//�����̶�ȡ�¶ȣ������¶Ȼ�ûת���굼�¶�ȡ��Ĭ��ֵ���ڳ���ʼʱ��ת��һ��Ȼ����ʱ1s����
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
//		LCD_ShowNum(2,2,T,3);	//���ȶ�ʧ����ʾ����λ
//		LCD_ShowChar(2,5,'.');
//		LCD_ShowNum(2,6,(unsigned long)(T*10000)%10000,4);	//��ʾС��λ
//	}
//}

//DS18B20�¶ȱ�����
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
	if(THigh>125 || TLow<-55 || THigh<=TLow)	//��֪����һ�δ洢��ֵ�Ƿ�����¶������ޣ������ж�һ������Ĭ��ֵ
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
		LCD_ShowNum(1,4,TShow,3);	//���ȶ�ʧ����ʾ����λ
		LCD_ShowChar(1,7,'.');
		LCD_ShowNum(1,8,(unsigned long)(TShow*100)%100,2);	//��ʾС��λ
		
		if(KeyNum)	//��������ʱ��ˢ�£���ʡ��Դ
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
//����ʱ��������������������������ʱ���ᵼ����˸�����ǹرմ��ж��ֻ�Ӱ�������жϵļ�ʱ������ʵ�����ѡ��
void Timer0_Routine() interrupt 1	//ע�ⲻ��Ƕ�׺�ʱ�ĺ���
{
	static unsigned int T0Count1;
	TL0 = 0x18;//���ö�ʱ��ֵ
	TH0 = 0xFC;//���ö�ʱ��ֵ
	T0Count1++;
	if(T0Count1 >= 20)	//ÿ��20ms�����˵�������ƽ����
	{
		T0Count1=0;
		Key_Loop();
	}
}