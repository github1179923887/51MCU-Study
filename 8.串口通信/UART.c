#include <REGX52.H>

/**
	*  @breif	4800bps@11.0592MHz串口初始化
	*  @param	无
	*  @retval	无
	*/
void UART_Init()	//4800bps@11.0592MHz
{
	//配置串口相关寄存器
	SCON = 0x50;	//0100 0000 分别指SM0,SM1,SM2,REN,TB8,RB8,TI,RI，
					//具体功能见手册P235，1：0x40未打开接收，2：0x50打开接收（即REN置1）
	PCON |= 0x80;
	
	//配置定时器1
	TMOD &= 0x0F;		//设置定时器模式，模式2：八位自动重装模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xF4;		//设定定时初值
	TH1 = 0xF4;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	
	//配置中断，需要接收时，优先级取默认
	ES = 1;
	EA = 1;
}
/**
	*  @breif	串口发送一个字节数据
	*  @param	Byte 要发送的数据
	*  @retval	无
	*/
void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte;	//串口数据缓存寄存器
	while(TI == 0);	//检测到TI==1(即数据发送完成)时跳出循环，将TI置0
	TI = 0;
}
/**
	*  @breif	串口中断函数模板
	*  @param	无
	*  @retval	无
	*/
/*
void UART_Routine() interrupt 4	//串口中断号
{
	if(RI == 1)	//数据接收完成，作判断的原因是发送和接收公用一个中断口，需要区分
	{
		
		RI = 0;
	}
}
*/



