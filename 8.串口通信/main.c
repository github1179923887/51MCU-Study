//����Է������ݣ�ע�Ⲩ���ʶ���
//#include <REGX52.H>
//#include "Delay.h"
//#include "UART.h"

//unsigned char Sec;

//void main()
//{
//	UART_Init();
//	while(1)
//	{
//		UART_SendByte(Sec);	//���������ڽ��յ�������16������ʾ
//		Sec++;
//		Delayxms(1000);	//������һ�˽��յ������ݲ��ԣ���ʱ1ms����
//	}
//}

//����ͨ�����ڿ���LED
#include <REGX52.H>
#include "Delay.h"
#include "UART.h"

unsigned char Sec;

void main()
{
	UART_Init();
	while(1)
	{
		//���µȼۣ�ʵ�ʴ洢��ֵ��һ����
		//UART_SendByte('B');
		//UART_SendByte(0x42);
		
		//���ж����öϿ�����ES=0��EA=0�������·���Ҳ��ʵ�֣����������ж�ϵͳ
//		while(RI == 0);
//		P2 = ~SBUF;	//��ȡ��һ�˷��͵����ݿ���LED
//		UART_SendByte(SBUF);	//�����յ������ݷ��ͻ�ȥ
//		RI = 0;
	}
}

void UART_Routine() interrupt 4	//�����жϺ�
{
	if(RI == 1)	//���ݽ�����ɣ����жϵ�ԭ���Ƿ��ͺͽ��չ���һ���жϿڣ���Ҫ����
	{
		P2 = ~SBUF;	//��ȡ��һ�˷��͵����ݿ���LED
		UART_SendByte(SBUF);	//�����յ������ݷ��ͻ�ȥ
		RI = 0;
	}
}

//���������ڵ��ı�ģʽ��HEX(�����ơ��˽��ơ�ʮ������)ģʽ֮���ת����ͨ��ASCLL��һһ��Ӧ�������ĸʱ��Ҫ�õ���֪ʶ��
