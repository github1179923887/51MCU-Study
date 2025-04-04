#include <REGX52.H>

void Timer1_Init(void)		//100΢��@11.0592MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x10;		//���ö�ʱ��ģʽ
	TL1 = 0xA4;		//���ö�ʱ��ֵ
	TH1 = 0xFF;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
	ET1 = 1;
	EA = 1;
	PT1 = 0;
}

/*��ʱ���жϺ���ģ��
void Timer1_Routine() interrupt 3
{
	static unsigned int T1Count;
	TL1 = 0xA4;		//���ö�ʱ��ֵ
	TH1 = 0xFF;		//���ö�ʱ��ֵ
	T1Count++;
	if(T1Count>=1000)
	{
		T1Count=0;
	}
}
*/