//AD模数转换
//DA跟PWM原理一致，只是更换了引脚接口且电路内部添加了低通滤波，实际实现代码没有区别。且DA用得少，PWM用得多
#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "XPT2046.h"

unsigned int ADValue;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"ADJ NTC RG");
	while(1)
	{
		ADValue = XPT2046_ReadAD(XPT2046_XP_8);
		LCD_ShowNum(2,1,ADValue*5/256,3);
		ADValue = XPT2046_ReadAD(XPT2046_YP_8);
		LCD_ShowNum(2,5,ADValue*5/256,3);
		ADValue = XPT2046_ReadAD(XPT2046_VBAT_8);
		LCD_ShowNum(2,9,ADValue*5/256,3);
		Delayxms(10);
	}
}
