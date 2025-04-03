#include <REGX52.H>
#include <INTRINS.H>	//_nop_()
#include "OneWire.h"
#include "LCD1602.h"

#define DS18B20_SKIP_ROM		0xCC
#define DS18B20_CONVERT_T		0x44
#define DS18B20_READ_SCRATCHPAD	0xBE

void DS18B20_ConverT()
{
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_CONVERT_T);
}

float DS18B20_ReadT()	//51��Ƭ����������������ע�⿼��
{
	unsigned char TLSB,TMSB;
	int Temp;
	float T;
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_READ_SCRATCHPAD);
	
	TLSB = OneWire_ReceiveByte();	//�Ĵ����ĵ�����ֽ�
	TMSB = OneWire_ReceiveByte();	//�Ĵ����ĵ�һ���ֽ�
	//LCD_ShowBinNum(1,1,TMSB,8);
	//LCD_ShowBinNum(1,9,TLSB,8);
	
	//�ϲ��ֽڲ�ǿ��ת��Ϊint����Ȼ�����޷��ţ���ʵ�ʲ����ж����Բ�����ʽ���㣬���ת������Ȼ�����˷�����Ϣ
	Temp = (TMSB<<8)|TLSB;
	//��Ϊ�¶ȴ洢���������ͺ���λ��С��������ת��Ϊint�������������λ�������Ҫ������λ��/16.0��.0����ת��Ϊfloat���־���
	T = Temp/16.0;
	return T;
}