#include <REGX52.H>
#include "I2C.h"

#define AT24C02_ADDRESS 0xA0	//ͨ�� |0x01 �����һλ��1�ͱ�Ϊд��ַ
/**
  *	@brief	AT24C02д��һ���ֽ�
  * @param	WordAddress Ҫ�������ַд���ֽ�
  * @param	Data Ҫд�������
  *	@retval	��
  */
void AT24C02_WriteByte(unsigned char WordAddress,Data)	//�ֵ�ַȡ0~255
{
	//unsigned char Ack = 0;
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	//Ack = I2C_ReceiveAck();
	//if(Ack==0)P2=0x00;	//����
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();
}
/**
  *	@brief	AT24C02��ȡһ���ֽ�
  * @param	WordAddress Ҫ�������ַ�����ֽ�
  *	@retval	����������
  */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS|0x01);
	I2C_ReceiveAck();
	Data = I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();
	return Data;
}