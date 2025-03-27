//��̬��ʾ,������ֻ����ͬ
//#include <REGX52.H>
//unsigned char NixieTubeNumber[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x00};
//void NixieTube(unsigned char Location,Number)
//{
//	switch(Location)
//	{
//		case 1:	//����һ��LEDΪLED8
//			P2_4 = 1;P2_3 = 1;P2_2 = 1;break;
//		case 2:	
//			P2_4 = 1;P2_3 = 1;P2_2 = 0;break;
//		case 3:	
//			P2_4 = 1;P2_3 = 0;P2_2 = 1;break;
//		case 4:	
//			P2_4 = 1;P2_3 = 0;P2_2 = 0;break;
//		case 5:	
//			P2_4 = 0;P2_3 = 1;P2_2 = 1;break;
//		case 6:	
//			P2_4 = 0;P2_3 = 1;P2_2 = 0;break;
//		case 7:	
//			P2_4 = 0;P2_3 = 0;P2_2 = 1;break;
//		case 8:	
//			P2_4 = 0;P2_3 = 0;P2_2 = 0;break;
//	}
//	P0=NixieTubeNumber[Number];
//}

//void main()
//{
////	//128����������Ӧ8�����LED
////	P2_4 = 1;
////	P2_3 = 0;
////	P2_2 = 1;
////	//��Ӧѡ�е����LED�еĵ���LED
////	P0 = 0x7D;	//P0_0����P0_7�����Ҳ�LED���ų�ͻ
//	NixieTube(8,9);
//	while(1)
//	{
//		
//	}
//}

//��̬��ʾ��ͨ�����ʱ��
#include <REGX52.H>
#include <INTRINS.H>	//_nop_()
unsigned char NixieTubeNumber[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x00};

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

void NixieTube(unsigned char Location,Number)
{
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
	Delayxms(1);	//Ҳ����ֱ�Ӽ���ʱ
	P0 = 0x00;	//Ŀ�ģ���ʱ���㡪��λѡ  ��ѡ���м�ᴮλ��λѡ  ��ѡ
}

void main()
{
	while(1)
	{
		NixieTube(1,1);
		NixieTube(2,2);
		NixieTube(3,3);
		NixieTube(4,4);
	}
}






