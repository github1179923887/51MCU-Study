//向电脑发送数据，注意波特率对齐
//#include <REGX52.H>
//#include "Delay.h"
//#include "UART.h"

//unsigned char Sec;

//void main()
//{
//	UART_Init();
//	while(1)
//	{
//		UART_SendByte(Sec);	//串口助手内接收的数据以16进制显示
//		Sec++;
//		Delayxms(1000);	//否则另一端接收到的数据不对，延时1ms即可
//	}
//}

//电脑通过串口控制LED
#include <REGX52.H>
#include "Delay.h"
#include "UART.h"

unsigned char Sec;

void main()
{
	UART_Init();
	while(1)
	{
		//以下等价，实际存储的值是一样的
		//UART_SendByte('B');
		//UART_SendByte(0x42);
		
		//将中断配置断开即（ES=0或EA=0），以下方法也可实现，即不利用中断系统
//		while(RI == 0);
//		P2 = ~SBUF;	//读取另一端发送的数据控制LED
//		UART_SendByte(SBUF);	//将接收到的数据发送回去
//		RI = 0;
	}
}

void UART_Routine() interrupt 4	//串口中断号
{
	if(RI == 1)	//数据接收完成，作判断的原因是发送和接收公用一个中断口，需要区分
	{
		P2 = ~SBUF;	//读取另一端发送的数据控制LED
		UART_SendByte(SBUF);	//将接收到的数据发送回去
		RI = 0;
	}
}

//串口助手内的文本模式与HEX(二进制、八进制、十六进制)模式之间的转换是通过ASCLL码一一对应，输出字母时需要用到该知识点
