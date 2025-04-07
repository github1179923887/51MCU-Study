//��дDS1302��ʵ�ֿɵ�ʱ��
#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "IndependentKey.h"
#include "Timer0.h"

unsigned char KeyNum,MODE,TimeSetSelect,TimeSetFlag;

void TimeShow()
{
	DS1302_ReadTime();
	LCD_ShowNum(1,1,DS1302_Time[0],2);
	LCD_ShowNum(1,4,DS1302_Time[1],2);
	LCD_ShowNum(1,7,DS1302_Time[2],2);
	LCD_ShowNum(2,1,DS1302_Time[3],2);
	LCD_ShowNum(2,4,DS1302_Time[4],2);
	LCD_ShowNum(2,7,DS1302_Time[5],2);
}

void TimeSet()
{
	unsigned char i = 0;
	if(KeyNum == 2)
	{
		TimeSetSelect++;
		TimeSetSelect %= 6;
	}
	
	if(KeyNum == 3)
	{
		DS1302_Time[TimeSetSelect]++;
		//��
		if(DS1302_Time[0] > 99){DS1302_Time[0] = 0;}
		//��
		if(DS1302_Time[1] > 12){DS1302_Time[1] = 1;}
		//��
		if(DS1302_Time[1] == 1 || DS1302_Time[1] == 3 || DS1302_Time[1] == 5 || DS1302_Time[1] == 7
		|| DS1302_Time[1] == 8 || DS1302_Time[1] == 10|| DS1302_Time[1] == 12)
		{
			if(DS1302_Time[2] > 31){DS1302_Time[2] = 1;}
		}
		else if(DS1302_Time[1] == 4 || DS1302_Time[1] == 6 || DS1302_Time[1] == 9 || DS1302_Time[1] == 11)
		{
			if(DS1302_Time[2] > 30){DS1302_Time[2] = 1;}
		}
		else if(DS1302_Time[1] == 2)
		{
			if(DS1302_Time[0] % 4 ==0)
			{
				if(DS1302_Time[2] > 29){DS1302_Time[2] = 1;}
			}
			else
			{
				if(DS1302_Time[2] > 28){DS1302_Time[2] = 1;}
			}
		}
		//ʱ����
		if(DS1302_Time[3] > 23){DS1302_Time[3] = 0;}
		if(DS1302_Time[4] > 59){DS1302_Time[4] = 0;}
		if(DS1302_Time[5] > 59){DS1302_Time[5] = 0;}
	}
	if(KeyNum == 4)
	{
		DS1302_Time[TimeSetSelect]--;
		//��
		if(DS1302_Time[0] < 0){DS1302_Time[0] = 99;}
		//��
		if(DS1302_Time[1] < 1){DS1302_Time[1] = 12;}
		//��
		if(DS1302_Time[1] == 1 || DS1302_Time[1] == 3 || DS1302_Time[1] == 5 || DS1302_Time[1] == 7
		|| DS1302_Time[1] == 8 || DS1302_Time[1] == 10|| DS1302_Time[1] == 12)
		{
			if(DS1302_Time[2] < 1){DS1302_Time[2] = 31;}
			if(DS1302_Time[2] > 31){DS1302_Time[2] = 1;}
		}
		else if(DS1302_Time[1] == 4 || DS1302_Time[1] == 6 || DS1302_Time[1] == 9 || DS1302_Time[1] == 11)
		{
			if(DS1302_Time[2] < 1){DS1302_Time[2] = 30;}
			if(DS1302_Time[2] > 30){DS1302_Time[2] = 1;}
		}
		else if(DS1302_Time[1] == 2)
		{
			if(DS1302_Time[0] % 4 ==0)
			{
				if(DS1302_Time[2] < 1){DS1302_Time[2] = 29;}
				if(DS1302_Time[2] > 29){DS1302_Time[2] = 1;}
			}
			else
			{
				if(DS1302_Time[2] < 1){DS1302_Time[2] = 28;}
				if(DS1302_Time[2] > 28){DS1302_Time[2] = 1;}
			}
		}
		//ʱ����
		if(DS1302_Time[3] < 0){DS1302_Time[3] = 23;}
		if(DS1302_Time[4] < 0){DS1302_Time[4] = 59;}
		if(DS1302_Time[5] < 0){DS1302_Time[5] = 59;}
	}
	//��˸����
	for(i = 0;i < 6;i++)
	{
		if(i <=2 )
		{
			if(TimeSetSelect == i && TimeSetFlag == 1)
			{
				LCD_ShowString(1,1 + 3*i,"  ");
			}
			else
			{
				LCD_ShowNum(1,1 + 3*i,DS1302_Time[i],2);
			}
		}
		else
		{
			if(TimeSetSelect == i && TimeSetFlag == 1)
			{
				LCD_ShowString(2,1 + 3*(i-3),"  ");
			}
			else
			{
				LCD_ShowNum(2,1 + 3*(i-3),DS1302_Time[i],2);
			}
		}	
	}
}

void main()
{
	LCD_Init();
	DS1302_Init();
	Timer0Init();
	//DS1302_WriteByte(0x80,0x55);	//0x81��д�������洢��ַ
	
	DS1302_SetTime();
	LCD_ShowString(1,1,"  -  -  ");
	LCD_ShowString(2,1,"  :  :  ");
	
	while(1)
	{
		//Sec = DS1302_ReadByte(0x81);	//0x81����ȡ�����洢��ַ
		//Min = DS1302_ReadByte(0x83);	//0x83����ȡ���Ӵ洢��ַ
		KeyNum = IndependentKey();
		if(KeyNum == 1)
		{
			if(MODE == 0){MODE = 1;TimeSetSelect = 0;}
			else if(MODE == 1){MODE = 0;DS1302_SetTime();}
		}
		//ģʽ����
		switch (MODE)
		{
			case 0:TimeShow();break;
			case 1:TimeSet();break;
		}
	}
}

void Timer0Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0=0x18;//���ö�ʱ��ֵ
	TH0 =0xFC;//���ö�ʱ��ֵ
	T0Count++;
	if(T0Count >= 500)	//ÿ��500ms
	{
		T0Count=0;
		TimeSetFlag =!TimeSetFlag;	//����ȡ0,1
	}
}