//���PWMԭ�����LED������
#include <REGX52.H>

sbit LED = P2^0;

void Delay(unsigned int t)
{
	while(t--);
}

void main()
{
	unsigned char Time,i;
	while(1)
	{
		//�ɰ�����
		for(Time=0;Time<100;Time++)
		{
			for(i=0;i<20;i++)	//�ӻ��仯�ٶ�
			{
				LED = 0;
				Delay(Time);
				LED = 1;
				Delay(100-Time);
			}
		}
		//�����䰵
		for(Time=100;Time>0;Time--)
		{
			for(i=0;i<20;i++)
			{
				LED = 0;
				Delay(Time);
				LED = 1;
				Delay(100-Time);
			}
		}
	}
}
