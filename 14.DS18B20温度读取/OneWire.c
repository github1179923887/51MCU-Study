#include <REGX52.H>
#include <INTRINS.H>	//_nop_()

sbit OneWire_DQ = P3^7;

unsigned char OneWire_Init()
{
	unsigned char i,AckBit;
	
	EA = 0;	//进入延时时关闭中断
	
	OneWire_DQ = 1;
	OneWire_DQ = 0;
	//延时500us，至少480us
	_nop_();
	i = 227;
	while (--i);
	//释放总线
	OneWire_DQ = 1;
	//延时70us，15~60us后从机会拉低总线（存在的话）
	_nop_();
	i = 29;
	while (--i);
	//监测从机是(0)否(1)应答
	AckBit = OneWire_DQ;
	//延时500us，至少480us
	_nop_();
	i = 227;
	while (--i);
	
	EA = 1;	//退出延时时打开中断
	
	return AckBit;
}

void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
		
	EA = 0;	//进入延时时关闭中断
	
	OneWire_DQ = 1;		//可不给
	OneWire_DQ = 0;
	//延时10us，一个_nop_()1us，一个函数调用4us
	_nop_();
	i = 3;
	while (--i);
	//发送Bit
	OneWire_DQ = Bit;
	//延时50us
	i = 22;
	while (--i);
	//释放总线
	OneWire_DQ = 1;
		
	EA = 1;	//退出延时时打开中断
	
}

unsigned char OneWire_ReceiveBit()
{
	unsigned char i,Bit;
		
	EA = 0;	//进入延时时关闭中断
	
	OneWire_DQ = 1;		//可不给
	OneWire_DQ = 0;
	//延时10us
	_nop_();
	i = 3;
	while (--i);
	//释放总线
	OneWire_DQ = 1;
	//延时5us
	_nop_();
	i = 1;
	while (--i);
	//接收Bit
	Bit = OneWire_DQ;
	//延时50us
	i = 22;
	while (--i);
		
	EA = 1;	//退出延时时打开中断
	
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






