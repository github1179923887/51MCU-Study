#include <REGX52.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;
/**
  *	@brief	I2C开始
  * @param	无
  *	@retval	无
  */
void I2C_Start()
{
	//确保数据帧中需要用到起始条件时二者始终满足设置起始条件前的初始状态
	I2C_SDA = 1;
	I2C_SCL = 1;
	//起始条件
	I2C_SDA = 0;
	I2C_SCL = 0;
}
/**
  *	@brief	I2C结束
  * @param	无
  *	@retval	无
  */
void I2C_Stop()
{
	//结束条件
	I2C_SDA = 0;
	I2C_SCL = 1;
	I2C_SDA = 1;
}
/**
  *	@brief	I2C发送一个字节
  * @param	Byte 要发送的字节
  *	@retval	无
  */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i = 0;
	for(i=0;i<8;i++)
	{
		I2C_SDA = Byte&(0x80>>i);
		I2C_SCL = 1;
		//Delayxms();	当前单片机IO翻转慢，不需要
		I2C_SCL = 0;
	}
}
/**
  *	@brief	I2C接收一个字节
  * @param	无
  *	@retval	Byte 接收到的字节
  */
unsigned char I2C_ReceiveByte()
{
	unsigned char i = 0,Byte = 0x00;
	I2C_SDA = 1;
	for(i=0;i<8;i++)
	{
		I2C_SCL = 1;
		//I2C_SDA在函数内为什么会变？解释：可能是因为从机满足条件时自动向主机发送数据
		if(I2C_SDA){Byte |= (0x80>>i);}
		I2C_SCL = 0;
	}
	return Byte;
}
/**
  *	@brief	I2C发送应答
  * @param	AckBit 应答位（0答，1不答）
  *	@retval	无
  */
void I2C_SendAck(unsigned char AckBit)	//接收方操作，赋值
{
	I2C_SDA = AckBit;
	I2C_SCL = 1;
	I2C_SCL = 0;
}
/**
  *	@brief	I2C接收应答
  * @param	无
  *	@retval	AckBit 接收到的应答位（0答，1不答）
  */
unsigned char I2C_ReceiveAck()	//发送方操作，监测
{
	unsigned char AckBit = 0;
	I2C_SDA = 1;
	I2C_SCL = 1;
	AckBit = I2C_SDA;
	I2C_SCL = 0;
	return AckBit;
}