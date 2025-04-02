#include <REGX52.H>
#include "I2C.h"

#define AT24C02_ADDRESS 0xA0	//通过 |0x01 将最后一位置1就变为写地址
/**
  *	@brief	AT24C02写入一个字节
  * @param	WordAddress 要在这个地址写入字节
  * @param	Data 要写入的数据
  *	@retval	无
  */
void AT24C02_WriteByte(unsigned char WordAddress,Data)	//字地址取0~255
{
	//unsigned char Ack = 0;
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	//Ack = I2C_ReceiveAck();
	//if(Ack==0)P2=0x00;	//测试
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();
}
/**
  *	@brief	AT24C02读取一个字节
  * @param	WordAddress 要在这个地址读出字节
  *	@retval	读出的数据
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