#include <REGX52.H>
#include <INTRINS.H>	//_nop_()
#include "Delay.h"
//�������˿�
sbit Buzzer = P2^5;

//500us��ʱ����
void Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}

/**
  *	@brief	��������ʾ��
  * @param	ms	����ʱ��
  *	@retval	��
  */
void Buzzer_Time(unsigned int ms)
{
	unsigned int i = 0;
	for(i = 0;i < ms*2;i++)
	{
		Buzzer = !Buzzer;
		//Delayxms(1);	//1ms��תһ�Σ�������Ϊ2ms����ӦƵ��Ϊ1/0.002s = 500 HZ
		Delay500us();	//1000HZ
	}
}