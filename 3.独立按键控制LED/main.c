//按钮状态控制LED亮灭
//#include <REGX52.H>
//void main()
//{
//	while(1)
//	{
//		if(P3_1==0)	//0是按下状态，1	是松开状态
//		//按下独立按键K1，P3_0是K2，P3_2是K3，P3_3是K4
//		{
//			P2_0 = 0;
//		}
//		else
//		{
//			P2_0 = 1;
//		}
//	}
//}

//按钮按下改变LED亮灭
//#include <REGX52.H>
//void Delayxms(unsigned int x)		//@11.0592MHz
//{
//	unsigned char i, j;

//	while(x)
//	{
//		i = 2;
//		j = 199;
//		do
//		{
//			while (--j);
//		} while (--i);
//		x--;
//	}
//	
//}

//void main()
//{
//	while(1)
//	{
//		if(P3_1==0)
//		{
//			Delayxms(20);
//			while(P3_1==0);	//缓冲区，识别到按钮松开后才进行下一步
//			Delayxms(20);
//			P2_0 = ~P2_0;
//		}
//	}
//}

//按钮按一下加1，8个LED表示出二进制
//#include <REGX52.H>
//void Delayxms(unsigned int x)		//@11.0592MHz
//{
//	unsigned char i, j;

//	while(x)
//	{
//		i = 2;
//		j = 199;
//		do
//		{
//			while (--j);
//		} while (--i);
//		x--;
//	}
//	
//}

//void main()
//{
//	//8位二进制，一般用此表示寄存器
//	unsigned char LEDNum = 0;	//0000 0000
//	while(1)
//	{
//		if(P3_1==0)
//		{
//			Delayxms(20);
//			while(P3_1==0);
//			Delayxms(20);
//			LEDNum++;
//			P2 = ~LEDNum;
//			//P2--;	//第二种方法
//			//(~P2)++;	//第三种方法
//		}
//	}
//}

//两个按钮控制LED移动（点亮）
#include <REGX52.H>
void Delayxms(unsigned int x)		//@11.0592MHz
{
	unsigned char i, j;

	while(x)
	{
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
	unsigned char LEDNum = 0;	//0000 0000
	P2=~0x01;
	while(1)
	{
		if(P3_0==0)
		{
			Delayxms(20);
			while(P3_0==0);
			Delayxms(20);
			LEDNum++;
			P2 = ~(0x01<<(LEDNum%8));
			
		}
		if(P3_1==0)
		{
			Delayxms(20);
			while(P3_1==0);
			Delayxms(20);
			LEDNum--;
			P2 = ~(0x01<<(LEDNum%8));
			
		}
	}
}

