#include <REGX52.H>
#include "Delay.h"

/**
	* @breif	获取独立按键键值
	* @param	无
	* @retval	按下按键的键值，范围：0~4，无按键按键时返回0
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