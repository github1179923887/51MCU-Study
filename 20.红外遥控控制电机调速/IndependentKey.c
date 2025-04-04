#include <REGX52.H>
#include "Delay.h"

unsigned char Key_KeyNumber;

unsigned char Key()
{
	unsigned char Temp = 0;
	Temp = Key_KeyNumber;
	Key_KeyNumber = 0;
	return Temp;
}

/**
	* @breif	��ȡ����������ֵ
	* @param	��
	* @retval	���°����ļ�ֵ����Χ��0~4���ް�������ʱ����0
	*/
unsigned char Key_GetState()
{
	unsigned char KeyNumber = 0;
	if(P3_1 == 0){KeyNumber = 1;}
	if(P3_0 == 0){KeyNumber = 2;}
	if(P3_2 == 0){KeyNumber = 3;}
	if(P3_3 == 0){KeyNumber = 4;}
	return KeyNumber;
}

void Key_Loop()
{
	static unsigned char NowState = 0,LastState = 0;
	unsigned char i = 0;
	LastState = NowState;
	NowState = Key_GetState();

	if((LastState && NowState == 0) && LastState != 0)
	{
		Key_KeyNumber = LastState;
	}
	
}