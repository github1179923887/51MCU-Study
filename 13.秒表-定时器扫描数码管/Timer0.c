#include <REGX52.H>

//12MHZ一次1us，11.0598MHZ一次1.085us
//void Timer0_Init()
//{
//	//TMOD = 0x01;	//模式寄存器，不可位寻址（必须整体赋值）
//	TMOD &= 0xF0;	//高四位不变，低四位清零
//	TMOD |= 0x01;	//高四位不变，低四位赋0001
//	//0000 0001，分别指定时器1：Gate C/T M1 M0 定时器0：Gate C/T M1 M0	T上有一横
//	//指选用模式一，设置原理见定时器电路图
//	
//	//TCON	//控制寄存器，可位寻址（可以单独赋值）
//	TF0 = 0;
//	TR0 = 1;	//允许T1开始计数，0不允许
//	
//	//两个八位"计数器"组成十六位，0~65535，TH0高位，TL0低位
//	TH0 = 64613/256;
//	TL0 = 64613%256;
//	
//	//打通中断系统T0，包括ET0、EA，  PT0（优先级，0低1高）
//	ET0 = 1;
//	EA = 1;
//	PT0 = 0;
//}
void Timer0_Init(void)		//1毫秒@11.0592MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;
	EA = 1;
	PT0 = 0;	//默认为0，可以不赋值
}

/*定时器中断函数模板
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;//设置定时初值
	TH0 =0xFC;//设置定时初值
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;
	}
}
*/