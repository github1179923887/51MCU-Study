//��ť״̬����LED����
//#include <REGX52.H>
//void main()
//{
//	while(1)
//	{
//		if(P3_1==0)	//0�ǰ���״̬��1	���ɿ�״̬
//		//���¶�������K1��P3_0��K2��P3_2��K3��P3_3��K4
//		{
//			P2_0 = 0;
//		}
//		else
//		{
//			P2_0 = 1;
//		}
//	}
//}

//��ť���¸ı�LED����
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
//			while(P3_1==0);	//��������ʶ�𵽰�ť�ɿ���Ž�����һ��
//			Delayxms(20);
//			P2_0 = ~P2_0;
//		}
//	}
//}

//��ť��һ�¼�1��8��LED��ʾ��������
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
//	//8λ�����ƣ�һ���ô˱�ʾ�Ĵ���
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
//			//P2--;	//�ڶ��ַ���
//			//(~P2)++;	//�����ַ���
//		}
//	}
//}

//������ť����LED�ƶ���������
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

