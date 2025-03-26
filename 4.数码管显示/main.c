//��̬��ʾ,������ֻ����ͬ
#include <REGX52.H>

unsigned char NixieTubeNumber[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x00};
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
	P0=NixieTubeNumber[Number];
}

void main()
{
//	//128����������Ӧ8�����LED
//	P2_4 = 1;
//	P2_3 = 0;
//	P2_2 = 1;
//	//��Ӧѡ�е����LED�еĵ���LED
//	P0 = 0x7D;	//P0_0����P0_7�����Ҳ�LED���ų�ͻ
	NixieTube(8,9);
	while(1)
	{
		
	}
}