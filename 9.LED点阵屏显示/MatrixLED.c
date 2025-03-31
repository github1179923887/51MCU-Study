#include <REGX52.H>
#include "Delay.h"

//�����ȡP3�ĵ�n+1λ��ַ(0,1,2,3,4,5,6,7)
sbit RCK = P3^5;	//���ڽ�����ͬʱ�������ݻ�����(ȡ)��RCLK��������ˣ�����û��
sbit SCK = P3^6;	//���ڽ���������λ�Ĵ�������(ȡ�ߵ�ƽʱ��λ)��SRCLK
sbit SER = P3^4;	//���ڽ����ݴ�����λ�Ĵ�����ڣ�SER

#define MATRIX_LED_PORT P0

/**
	*  @breif	��������ʼ��
	*  @param	��
	*  @retval	��
	*/
void MatrixLED_Init()
{
	SCK = 0;
	RCK = 0;
}

/**
	*  @breif	74HC595д��һ���ֽ�
	*  @param	Byte������0x80
	*  @retval	��
	*/
void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i;
//	SER = Byte&0x80;	//��ȡByte�����λ����Ϊ��Ҫ���������λȻ��������λ���Ҳ�Ϊ8λֵ�����Ϊ1λֵ����ʱ�й��򡰷�0��1��ʹλ����
//	SCK = 1;	//��λ
//	SCK = 0;	//����	
	for(i = 0;i < 8;i++)
	{
		SER = Byte&(0x80>>i);
		SCK = 1;	//��λ
		SCK = 0;	//����
	}
	RCK = 1;	//�������ݻ���
	RCK = 0;	//����
}

/**
	*  @breif	����ĳ��LED������
	*  @param	Column ѡ���У���Χ��0~7������
	*  @param	Row	   ѡ��Ҫ�������У���λ���ϣ�1��0��
	*  @retval	��
	*/
void MatrixLED_ShowColumn(unsigned char Column,Row)	//��ȡ�ߵ�ƽ����ȡ�͵�ƽ->����
{
//	�÷���һ�ν���һ�����˷���
//	unsigned char Data = 0x00;
//	for(Row = 1;Row < 9;Row++)
//	{
//		Data = 0x01<<(Row - 1);
//	}
	_74HC595_WriteByte(Row);
	MATRIX_LED_PORT = ~0x80>>(Column-1);	//�͵�ƽ��������ȡ��
	//��Ӱ
	Delayxms(1);	//��ʱ
	MATRIX_LED_PORT = 0xFF;	//λ����
}