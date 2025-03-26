//静态显示,单个或只能相同
#include <REGX52.H>

unsigned char NixieTubeNumber[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x00};
void NixieTube(unsigned char Location,Number)
{
	switch(Location)
	{
		case 1:	//左侧第一组LED为LED8
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
//	//128编码器，对应8个组合LED
//	P2_4 = 1;
//	P2_3 = 0;
//	P2_2 = 1;
//	//对应选中的组合LED中的单个LED
//	P0 = 0x7D;	//P0_0——P0_7，与右侧LED引脚冲突
	NixieTube(8,9);
	while(1)
	{
		
	}
}