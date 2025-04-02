#include <REGX52.H>
#include <INTRINS.H>	//_nop_()
#include "Delay.h"
//蜂鸣器端口
sbit Buzzer = P2^5;

//500us延时函数
void Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}

/**
  *	@brief	蜂鸣器提示音
  * @param	ms	发声时长
  *	@retval	无
  */
void Buzzer_Time(unsigned int ms)
{
	unsigned int i = 0;
	for(i = 0;i < ms*2;i++)
	{
		Buzzer = !Buzzer;
		//Delayxms(1);	//1ms翻转一次，则周期为2ms，对应频率为1/0.002s = 500 HZ
		Delay500us();	//1000HZ
	}
}