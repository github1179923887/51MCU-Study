//显示按钮对应的键值
//#include <REGX52.H>
//#include "LCD1602.h"
//#include "Delay.h"
//#include "MatrixKey.h"

//unsigned char KeyNum;

//void main()
//{
////	LCD_Init();
////	LCD_ShowChar(1,1,'A');
////	LCD_ShowString(1,3,"Hello");
////	LCD_ShowNum(1,9,123,3);
////	LCD_ShowSignedNum(1,13,-66,2);
////	LCD_ShowHexNum(2,1,0xA8,2);	//十六进制
////	LCD_ShowBinNum(2,4,0xAA,8);	//二进制
//	LCD_Init();
//	LCD_ShowString(1,1,"InputValue:");
//	while(1)
//	{
//		KeyNum=MatrixKey();
//		if(KeyNum)	//KeyNum为0指无按钮按下
//		{
//			LCD_ShowNum(2,1,KeyNum,2);
//		}
//	}
//}

//密码锁
#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
#include "MatrixKey.h"

unsigned char KeyNum;
unsigned int Password;
unsigned int n;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Password:");
	LCD_ShowNum(2,1,0,4);
	while(1)
	{
		KeyNum=MatrixKey();
		if(KeyNum)	//KeyNum为0指无按钮按下
		{
			if(KeyNum<=10)	//S1——S10按下
			{
				if(n<4)
				{
					Password=Password*10+KeyNum%10;	//让第十个按键输出0值
					n++;
				}
				else
				{
					LCD_ShowString(1,12,"Extra");
				}
				LCD_ShowNum(2,1,Password,4);
			}
			if(KeyNum==11)
			{
				if(Password==0)
				{
					LCD_ShowString(1,1,"Please Input   ");
				}
				else if(Password==5876)
				{
					LCD_ShowString(1,12,"Right");
				}
				else
				{
					LCD_ShowString(1,12,"Wrong");
				}
			}
			if(KeyNum==12)
			{
				n=Password=0;
				LCD_ShowString(1,12,"Reset");
				LCD_ShowNum(2,1,Password,4);
				Delayxms(2000);
				LCD_ShowString(1,12,"     ");
			}
		}
	}
}