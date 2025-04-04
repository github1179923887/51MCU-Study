#include <REGX52.H>
#include "Timer0.h"
#include "Int0.h"

unsigned int IR_Time;
unsigned char IR_State;		//0:空闲状态；1:寻找start帧或repeat帧；2:解码32位数据

//为什么不用long（32位），因为左移右移只能移16位
unsigned char IR_Data[4];
unsigned char IR_pData;		//指向32数据的位置，判断是否接收完

unsigned char IR_DataFlag;	//等于1表示得到数据了
unsigned char IR_RepeatFlag;
//避免IR_Data又接收又输出
unsigned char IR_Address;
unsigned char IR_Command;

void IR_Init()
{
	Timer0_Init();
	Int0_Init();
}

unsigned char IR_GetDataFlag()
{
	if(IR_DataFlag == 1)
	{
		IR_DataFlag = 0;
		return 1;
	}
	return 0;
}

unsigned char IR_GetRepeatFlag()
{
	if(IR_RepeatFlag == 1)
	{
		IR_RepeatFlag = 0;
		return 1;
	}
	return 0;
}

unsigned char IR_GetAddress()
{
	return IR_Address;
}

unsigned char IR_GetCommand()
{
	return IR_Command;
}

void Int0_Routine() interrupt 0
{
	if(IR_State == 0)
	{
		//P2 = 0;	//测试
		Timer0_SetCounter(0);	//计时清零
		Timer0_Run(1);
		IR_State = 1;
	}
	else if(IR_State == 1)
	{
		//P2 = 0;	//测试
		IR_Time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		if(IR_Time > (int)((float)(13000)/1.085) && IR_Time < (int)((float)(14000)/1.085))	//给上下500的范围,13500左右的冗余，找到start帧，状态转化为接收数据
		{
			//P2 = 0;	//测试
			IR_State = 2;
		}
		else if(IR_Time > (int)((float)(10750)/1.085) && IR_Time < (int)((float)(11750)/1.085))	//11250，找到repeat帧说明数据接收完了
		{
			IR_RepeatFlag = 1;
			Timer0_Run(0);		//停止计时
			IR_State = 0;
		}
		else	//错误处理
		{
			IR_State = 1;
		}
	}
	else if(IR_State == 2)
	{
		IR_Time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		//判断数据是0还是1
		if(IR_Time > (int)((float)(560+560-500)/1.085) && IR_Time < (int)((float)(560+560+500)/1.085))
		{
			IR_Data[IR_pData/8] &= ~(0x01<<(IR_pData%8));		//&=~->对应位取零
			IR_pData++;
		}
		else if(IR_Time > (int)((float)(560+1690-500)/1.085) && IR_Time < (int)((float)(560+1690+500)/1.085))
		{
			IR_Data[IR_pData/8] |= 0x01<<(IR_pData%8);		//|=->对应位取一
			IR_pData++;
		}
		else	//处理错误
		{
			IR_pData = 0;
			IR_State = 1;
		}
		if(IR_pData >= 32)	//判断数据是否接收完
		{
			IR_pData = 0;
			if((IR_Data[0] == ~IR_Data[1]) && (IR_Data[2] == ~IR_Data[3]))	//数据验证，数据形式：Address，~Address，Command，~Command
			{
				IR_Address = IR_Data[0];
				IR_Command = IR_Data[2];
				IR_DataFlag = 1;
			}
			Timer0_Run(0);
			IR_State = 0;
		}
	}
}