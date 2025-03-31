#include <REGX52.H>
#include "Delay.h"

//用异或取P3的第n+1位地址(0,1,2,3,4,5,6,7)
sbit RCK = P3^5;	//用于将数据同时传入数据缓存区(取)，RCLK被定义过了，其他没有
sbit SCK = P3^6;	//用于将数据在移位寄存器下移(取高电平时移位)，SRCLK
sbit SER = P3^4;	//用于将数据传入移位寄存器入口，SER

#define MATRIX_LED_PORT P0

/**
	*  @breif	点阵屏初始化
	*  @param	无
	*  @retval	无
	*/
void MatrixLED_Init()
{
	SCK = 0;
	RCK = 0;
}

/**
	*  @breif	74HC595写入一个字节
	*  @param	Byte，例：0x80
	*  @retval	无
	*/
void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i;
//	SER = Byte&0x80;	//提取Byte的最高位，因为需要先输入最高位然后依次移位，右侧为8位值，左侧为1位值，此时有规则“非0即1”使位对齐
//	SCK = 1;	//移位
//	SCK = 0;	//清零	
	for(i = 0;i < 8;i++)
	{
		SER = Byte&(0x80>>i);
		SCK = 1;	//移位
		SCK = 0;	//清零
	}
	RCK = 1;	//传入数据缓存
	RCK = 0;	//清零
}

/**
	*  @breif	点亮某列LED点阵屏
	*  @param	Column 选择列，范围：0~7，从左
	*  @param	Row	   选择要点亮的行，高位在上，1亮0灭
	*  @retval	无
	*/
void MatrixLED_ShowColumn(unsigned char Column,Row)	//行取高电平，列取低电平->点亮
{
//	该方法一次仅亮一个，浪费了
//	unsigned char Data = 0x00;
//	for(Row = 1;Row < 9;Row++)
//	{
//		Data = 0x01<<(Row - 1);
//	}
	_74HC595_WriteByte(Row);
	MATRIX_LED_PORT = ~0x80>>(Column-1);	//低电平点亮，故取反
	//消影
	Delayxms(1);	//延时
	MATRIX_LED_PORT = 0xFF;	//位清零
}