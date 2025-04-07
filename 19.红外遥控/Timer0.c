#include <REGX52.H>

void Timer0_Init(void)		//@11.0592MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0;		//���ö�ʱ��ֵ
	TH0 = 0;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 0;		//��ʱ��0����ʱ
}
//���ó�ֵ
void Timer0_SetCounter(unsigned int Value)
{
	TH0 = Value/256;
	TL0 = Value%256;
}

unsigned int Timer0_GetCounter()
{
	return (TH0<<8)|TL0;
}
//������Ҫ������رռ�ʱ
void Timer0_Run(unsigned char Flag)
{
	TR0 = Flag;		
}