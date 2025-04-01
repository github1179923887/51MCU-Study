#include <REGX52.H>

#define DS1302_SECOND 0x80
#define DS1302_MINUTE 0x82
#define DS1302_HOUR	  0x84
#define DS1302_DATE   0x86
#define DS1302_MONTH  0x88
#define DS1302_DAY    0x8A	//星期
#define DS1302_YEAR   0x8C
#define DS1302_WP     0x8E

sbit DS1302_SCLK = P3^6;	//时钟通过上下沿控制读取或写入
sbit DS1302_IO = P3^4;		//输入输出控制
sbit DS1302_CE = P3^5;		//芯片使能，置1打通

//年月日时分秒星期
char DS1302_Time[] = {25,4,1,16,32,0,2};

void DS1302_Init()
{
	DS1302_CE = 0;
	DS1302_SCLK = 0;
}

//写入命令字和数据，命令字告诉时钟：在哪 写入还是读取
//写入有16个脉冲
void DS1302_WriteByte(unsigned char Command,Data)
{
	unsigned char i = 0;
	DS1302_CE = 1;
	for(i = 0;i < 8;i++)
	{
		DS1302_IO = (Command>>i)&0x01;	//提取Command第i位，或者Command&(0x01<<i)
		DS1302_SCLK = 1;
		//Delayxms;		单片机性能不够，所以不快，否则要加延时
		DS1302_SCLK = 0;
	}
	//此处到时序中间
	for(i = 0;i < 8;i++)
	{
		DS1302_IO = (Data>>i)&0x01;
		DS1302_SCLK = 1;	//指给上升沿，写
		DS1302_SCLK = 0;	//指给下降沿，读
	}
	DS1302_CE = 0;
}

//读取命令字，只有15个脉冲
unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i = 0,Data = 0x00;
	DS1302_CE = 1;
	Command |= 0x01;	//因为读取最低位需要设置为一，这样操作后可以直接输入写地址转化为读地址
	for(i = 0;i < 8;i++)
	{
		DS1302_IO = (Command>>i)&0x01;
		//先给1后给0，时序以上升沿左侧结束，先0后一，时序以下降沿左侧结束，上下沿形如：几的左右两边
		DS1302_SCLK = 0;
		DS1302_SCLK = 1;
	}
	//此处到时序中间
	for(i = 0;i < 8;i++)
	{
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
		if(DS1302_IO){Data |= (0x01<<i);}	//如果值非0（其实就是1，因为只有0，1两种值），Data第 i 位 置1
	}
	DS1302_CE = 0;
	DS1302_IO = 0;
	return Data;
}

void DS1302_SetTime()
{
	DS1302_WriteByte(DS1302_WP,0x00);	//解除写入保护
	DS1302_WriteByte(DS1302_YEAR,DS1302_Time[0]/10*16 + DS1302_Time[0]%10);	//十进制转化为BCD码
	DS1302_WriteByte(DS1302_MONTH,DS1302_Time[1]/10*16 + DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE,DS1302_Time[2]/10*16 + DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,DS1302_Time[3]/10*16 + DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,DS1302_Time[4]/10*16 + DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,DS1302_Time[5]/10*16 + DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,DS1302_Time[6]/10*16 + DS1302_Time[6]%10);
	DS1302_WriteByte(DS1302_WP,0x80);	//打开写入保护
}

void DS1302_ReadTime()
{
	unsigned char Temp;
	Temp = DS1302_ReadByte(DS1302_YEAR) ;
	DS1302_Time[0] = Temp/16*10+Temp%16;
	Temp = DS1302_ReadByte(DS1302_MONTH);
	DS1302_Time[1] = Temp/16*10+Temp%16;
	Temp = DS1302_ReadByte(DS1302_DATE);
	DS1302_Time[2] = Temp/16*10+Temp%16;
	Temp = DS1302_ReadByte(DS1302_HOUR);
	DS1302_Time[3] = Temp/16*10+Temp%16;
	Temp = DS1302_ReadByte(DS1302_MINUTE);
	DS1302_Time[4] = Temp/16*10+Temp%16;
	Temp = DS1302_ReadByte(DS1302_SECOND);
	DS1302_Time[5] = Temp/16*10+Temp%16;
	Temp = DS1302_ReadByte(DS1302_DAY);
	DS1302_Time[6] = Temp/16*10+Temp%16;
}

//DS1302时钟以BCD码形式表示和存储时间
//BCD码转十进制：DEC=BCD/16*10+BCD%16;(2位BCD)
//十进制转BCD码：BCD=DEC/10*16+DEC%10;(2位BCD)

