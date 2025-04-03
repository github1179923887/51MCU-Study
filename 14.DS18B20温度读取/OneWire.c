#include <REGX52.H>
#include <INTRINS.H>	//_nop_()

sbit OneWire_DQ = P3^7;

unsigned char OneWire_Init()
{
	unsigned char i,AckBit;
	
	EA = 0;	//������ʱʱ�ر��ж�
	
	OneWire_DQ = 1;
	OneWire_DQ = 0;
	//��ʱ500us������480us
	_nop_();
	i = 227;
	while (--i);
	//�ͷ�����
	OneWire_DQ = 1;
	//��ʱ70us��15~60us��ӻ����������ߣ����ڵĻ���
	_nop_();
	i = 29;
	while (--i);
	//���ӻ���(0)��(1)Ӧ��
	AckBit = OneWire_DQ;
	//��ʱ500us������480us
	_nop_();
	i = 227;
	while (--i);
	
	EA = 1;	//�˳���ʱʱ���ж�
	
	return AckBit;
}

void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
		
	EA = 0;	//������ʱʱ�ر��ж�
	
	OneWire_DQ = 1;		//�ɲ���
	OneWire_DQ = 0;
	//��ʱ10us��һ��_nop_()1us��һ����������4us
	_nop_();
	i = 3;
	while (--i);
	//����Bit
	OneWire_DQ = Bit;
	//��ʱ50us
	i = 22;
	while (--i);
	//�ͷ�����
	OneWire_DQ = 1;
		
	EA = 1;	//�˳���ʱʱ���ж�
	
}

unsigned char OneWire_ReceiveBit()
{
	unsigned char i,Bit;
		
	EA = 0;	//������ʱʱ�ر��ж�
	
	OneWire_DQ = 1;		//�ɲ���
	OneWire_DQ = 0;
	//��ʱ10us
	_nop_();
	i = 3;
	while (--i);
	//�ͷ�����
	OneWire_DQ = 1;
	//��ʱ5us
	_nop_();
	i = 1;
	while (--i);
	//����Bit
	Bit = OneWire_DQ;
	//��ʱ50us
	i = 22;
	while (--i);
		
	EA = 1;	//�˳���ʱʱ���ж�
	
	return Bit;
}

void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i = 0;
	for(i = 0;i < 8;i++)
	{
		OneWire_SendBit(Byte&(0x01<<i));
	}
}

unsigned char OneWire_ReceiveByte()
{
	unsigned char i = 0,Byte = 0x00;
	for(i = 0;i < 8;i++)
	{
		if(OneWire_ReceiveBit()){Byte |= (0x01<<i);}
	}
	return Byte;
}






