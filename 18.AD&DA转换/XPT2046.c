#include <REGX52.H>
#include "Delay.h"

sbit XPT2046_CS = P3^5;		//控制进入
sbit XPT2046_DCLK = P3^6;	//上升沿发出命令让DIN接收，下降沿接收DOUT数据
sbit XPT2046_DIN = P3^4;
sbit XPT2046_DOUT = P3^7;

unsigned int XPT2046_ReadAD(unsigned char Command)
{
	unsigned char i = 0;
	unsigned int ADValue = 0;
	XPT2046_DCLK = 0;
	XPT2046_CS = 0;
	for(i=0;i<8;i++)
	{
		XPT2046_DIN = Command&(0x80>>i);
		XPT2046_DCLK = 1;
		XPT2046_DCLK = 0;
	}
	for(i=0;i<16;i++)
	{
		XPT2046_DCLK = 1;
		XPT2046_DCLK = 0;
		Delayxms(1);	//不加延时电阻不会变
		if(XPT2046_DOUT){ADValue|=(0x8000>>i);}
	}
	XPT2046_CS = 1;
	if(Command&0x08){return ADValue>>8;}
	else{return ADValue>>4;}
	
}