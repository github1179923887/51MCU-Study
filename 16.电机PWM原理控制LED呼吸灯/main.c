//电机PWM原理控制LED呼吸灯
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
		//由暗变亮
		for(Time=0;Time<100;Time++)
		{
			for(i=0;i<20;i++)	//延缓变化速度
			{
				LED = 0;
				Delay(Time);
				LED = 1;
				Delay(100-Time);
			}
		}
		//由亮变暗
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
