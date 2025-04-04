#include <REGX52.H>
#include <INTRINS.H>	//_nop_()

sbit LCD_RS = P2^6;
sbit LCD_RW = P2^5;
sbit LCD_E = P2^7;
#define LCD_DataPort P0

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_DataPort = Command;
	LCD_E = 1;
	Delay1ms();		//执行指令需要时间
	LCD_E = 0;
	Delay1ms();
}

void LCD_WriteData(unsigned char Data)
{
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_DataPort = Data;
	LCD_E = 1;
	Delay1ms();		//执行指令需要时间
	LCD_E = 0;
	Delay1ms();
}

void LCD_Init()
{
	//设置模式
	LCD_WriteCommand(0x38);	//八位数据接口，两行显示，5*7点阵
	LCD_WriteCommand(0x0C);	//显示开，光标关，闪烁关
	LCD_WriteCommand(0x06);	//数据读写操作后，光标自动加一，画面不变
	LCD_WriteCommand(0x01);	//清屏
}

void LCD_LC2Location(unsigned char Line,unsigned char Column)
{
	//行列到地址的转换
	if(Line == 1)
	{
		LCD_WriteCommand(0x80|(Column-1));
	}
	else
	{
		LCD_WriteCommand(0x80|(Column-1)+0x40);
	}
}

void LCD_ShowChar(unsigned char Line,unsigned char Column,unsigned char Char)
{
	LCD_LC2Location(Line,Column);
	LCD_WriteData(Char);
}

void LCD_ShowString(unsigned char Line,unsigned char Column,unsigned char String[])
{
	unsigned char i = 0;
	LCD_LC2Location(Line,Column);
	for(i = 0;String[i] != '\0';i++)
	{
		LCD_WriteData(String[i]);
	}
}

int LCD_Pow(int X,int Y)
{
	unsigned char i = 0;
	int Result = 1;
	for(i = 0;i < Y;i++)
	{
		Result *= X;
	}
	return Result;
}

void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i = 0;
	LCD_LC2Location(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number/LCD_Pow(10,i-1)%10 + '0');
	}
}

void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length)
{
	unsigned char i = 0;
	unsigned int Number1 = 0;
	LCD_LC2Location(Line,Column);
	if(Number>=0)
	{
		LCD_WriteData('+');
		Number1 = Number;
	}
	else
	{
		LCD_WriteData('-');
		Number1 = -Number;
	}
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number1/LCD_Pow(10,i-1)%10 + '0');
	}
}

void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i = 0;
	unsigned char SingleNumber = 0;
	LCD_LC2Location(Line,Column);
	for(i=Length;i>0;i--)
	{
		SingleNumber = Number/LCD_Pow(16,i-1)%16;
		if(SingleNumber<10)
		{
			LCD_WriteData(SingleNumber + '0');
		}
		else
		{
			LCD_WriteData(SingleNumber-10 + 'A');
		}
	}
}

void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i = 0;
	LCD_LC2Location(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number/LCD_Pow(2,i-1)%2 + '0');
	}
}








