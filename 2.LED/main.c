//����һ��LED��P2�ǹ���8��LED�ļĴ���
//#include <REGX52.H>
//void main()
//{
//	//P2 = 0xFE; //1111 1110
//	P2 = 0x55;	//0101 0101
//	while(1)
//	{
//		
//	}
//}

//LDE��˸��delay
//#include <REGX52.H>
//#include <INTRINS.H>	//_nop_()
//void Delay500ms()		//@11.0592MHz
//{
//	unsigned char i, j, k;

//	_nop_();
//	i = 4;
//	j = 129;
//	k = 119;
//	do
//	{
//		do
//		{
//			while (--k);
//		} while (--j);
//	} while (--i);
//}
//void main()
//{
//	while(1)
//	{
//		P2 = 0xFE;
//		Delay500ms();
//		P2 = 0xFF;
//		Delay500ms();
//	}
//}

//LED��ˮ�ƣ��ɱ�Delay
#include <REGX52.H>
#include <INTRINS.H>	//_nop_()
void Delayxms(unsigned int x)		//@11.0592MHz
{
	unsigned char i, j;
	while(x)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		x--;
	} 
}
void main()
{
	while(1)
	{
		P2 = 0xFE;
		Delayxms(500);
		P2 = 0xFD;
		Delayxms(1000);
		P2 = 0xFB;
		Delayxms(100);
		P2 = 0xF7;
		Delayxms(200);
		P2 = 0xEF;
		Delayxms(300);
		P2 = 0xDF;
		Delayxms(700);
		P2 = 0xBF;
		Delayxms(800);
		P2 = 0x7F;
		Delayxms(400);
	}
}