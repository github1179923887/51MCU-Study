#include <REGX52.H>
#include "Delay.h"

/**
	* @breif	��ȡ����������ֵ
	* @param	��
	* @retval	���°����ļ�ֵ����Χ��0~4���ް�������ʱ����0
	*/

unsigned char IndependentKey()
{
	unsigned char KeyNumber = 0;
	if(P3_1 == 0){Delayxms(20);while(P3_1 == 0);Delayxms(20);KeyNumber = 1;}
	if(P3_0 == 0){Delayxms(20);while(P3_0 == 0);Delayxms(20);KeyNumber = 2;}
	if(P3_2 == 0){Delayxms(20);while(P3_2 == 0);Delayxms(20);KeyNumber = 3;}
	if(P3_3 == 0){Delayxms(20);while(P3_3 == 0);Delayxms(20);KeyNumber = 4;}
	return KeyNumber;
}