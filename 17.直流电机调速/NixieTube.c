#include <REGX52.H>
#include "Delay.h"
unsigned char NixieTubeNumber[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00,0x40};	//1~0,�ٶ�һ����"-"

unsigned char NixieTube_Buffer[9] = {0,10,10,10,10,10,10,10,10};

void NixieTube_SetBuf(unsigned char Location,Number)
{
	NixieTube_Buffer[Location] = Number;
}

void NixieTube_Scan(unsigned char Location,Number)
{
	//Delayxms(1);	//Ҳ����ֻ����ʱ
	//P0 = 0x00;	//Ŀ�ģ���ʱ���㡪��λѡ  ��ѡ���м�ᴮλ��λѡ  ��ѡ
	P0 = 0x00;
	switch(Location)
	{
		case 1:	//����һ��LEDΪLED8
			P2_4 = 1;P2_3 = 1;P2_2 = 1;break;
		case 2:	
			P2_4 = 1;P2_3 = 1;P2_2 = 0;break;
		case 3:	
			P2_4 = 1;P2_3 = 0;P2_2 = 1;break;
		case 4:	
			P2_4 = 1;P2_3 = 0;P2_2 = 0;break;
		case 5:	
			P2_4 = 0;P2_3 = 1;P2_2 = 1;break;
		case 6:	
			P2_4 = 0;P2_3 = 1;P2_2 = 0;break;
		case 7:	
			P2_4 = 0;P2_3 = 0;P2_2 = 1;break;
		case 8:	
			P2_4 = 0;P2_3 = 0;P2_2 = 0;break;
	}
	P0 = NixieTubeNumber[Number];
}

void NixieTube_Loop()
{
	static unsigned char i = 1;
	NixieTube_Scan(i,NixieTube_Buffer[i]);
	i++;
	if(i>8){i = 1;}
}