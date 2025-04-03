#include <REGX52.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;
/**
  *	@brief	I2C��ʼ
  * @param	��
  *	@retval	��
  */
void I2C_Start()
{
	//ȷ������֡����Ҫ�õ���ʼ����ʱ����ʼ������������ʼ����ǰ�ĳ�ʼ״̬
	I2C_SDA = 1;
	I2C_SCL = 1;
	//��ʼ����
	I2C_SDA = 0;
	I2C_SCL = 0;
}
/**
  *	@brief	I2C����
  * @param	��
  *	@retval	��
  */
void I2C_Stop()
{
	//��������
	I2C_SDA = 0;
	I2C_SCL = 1;
	I2C_SDA = 1;
}
/**
  *	@brief	I2C����һ���ֽ�
  * @param	Byte Ҫ���͵��ֽ�
  *	@retval	��
  */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i = 0;
	for(i=0;i<8;i++)
	{
		I2C_SDA = Byte&(0x80>>i);
		I2C_SCL = 1;
		//Delayxms();	��ǰ��Ƭ��IO��ת��������Ҫ
		I2C_SCL = 0;
	}
}
/**
  *	@brief	I2C����һ���ֽ�
  * @param	��
  *	@retval	Byte ���յ����ֽ�
  */
unsigned char I2C_ReceiveByte()
{
	unsigned char i = 0,Byte = 0x00;
	I2C_SDA = 1;
	for(i=0;i<8;i++)
	{
		I2C_SCL = 1;
		//I2C_SDA�ں�����Ϊʲô��䣿���ͣ���������Ϊ�ӻ���������ʱ�Զ���������������
		if(I2C_SDA){Byte |= (0x80>>i);}
		I2C_SCL = 0;
	}
	return Byte;
}
/**
  *	@brief	I2C����Ӧ��
  * @param	AckBit Ӧ��λ��0��1����
  *	@retval	��
  */
void I2C_SendAck(unsigned char AckBit)	//���շ���������ֵ
{
	I2C_SDA = AckBit;
	I2C_SCL = 1;
	I2C_SCL = 0;
}
/**
  *	@brief	I2C����Ӧ��
  * @param	��
  *	@retval	AckBit ���յ���Ӧ��λ��0��1����
  */
unsigned char I2C_ReceiveAck()	//���ͷ����������
{
	unsigned char AckBit = 0;
	I2C_SDA = 1;
	I2C_SCL = 1;
	AckBit = I2C_SDA;
	I2C_SCL = 0;
	return AckBit;
}