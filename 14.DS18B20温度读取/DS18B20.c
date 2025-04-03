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

float DS18B20_ReadT()	//51单片机处理浮点数较慢，注意考量
{
	unsigned char TLSB,TMSB;
	int Temp;
	float T;
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_READ_SCRATCHPAD);
	
	TLSB = OneWire_ReceiveByte();	//寄存器的第零个字节
	TMSB = OneWire_ReceiveByte();	//寄存器的第一个字节
	//LCD_ShowBinNum(1,1,TMSB,8);
	//LCD_ShowBinNum(1,9,TLSB,8);
	
	//合并字节并强制转化为int，虽然二者无符号，但实际操作中都是以补码形式计算，因此转化后仍然保留了符号信息
	Temp = (TMSB<<8)|TLSB;
	//因为温度存储的数据类型后四位是小数，所以转化为int后就往左移了四位，因此需要右移四位即/16.0，.0负责转化为float保持精度
	T = Temp/16.0;
	return T;
}