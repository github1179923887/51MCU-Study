#include <REGX52.H>
#include "Timer0.h"
#include "Int0.h"

unsigned int IR_Time;
unsigned char IR_State;		//0:����״̬��1:Ѱ��start֡��repeat֡��2:����32λ����

//Ϊʲô����long��32λ������Ϊ��������ֻ����16λ
unsigned char IR_Data[4];
unsigned char IR_pData;		//ָ��32���ݵ�λ�ã��ж��Ƿ������

unsigned char IR_DataFlag;	//����1��ʾ�õ�������
unsigned char IR_RepeatFlag;
//����IR_Data�ֽ��������
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
		//P2 = 0;	//����
		Timer0_SetCounter(0);	//��ʱ����
		Timer0_Run(1);
		IR_State = 1;
	}
	else if(IR_State == 1)
	{
		//P2 = 0;	//����
		IR_Time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		if(IR_Time > (int)((float)(13000)/1.085) && IR_Time < (int)((float)(14000)/1.085))	//������500�ķ�Χ,13500���ҵ����࣬�ҵ�start֡��״̬ת��Ϊ��������
		{
			//P2 = 0;	//����
			IR_State = 2;
		}
		else if(IR_Time > (int)((float)(10750)/1.085) && IR_Time < (int)((float)(11750)/1.085))	//11250���ҵ�repeat֡˵�����ݽ�������
		{
			IR_RepeatFlag = 1;
			Timer0_Run(0);		//ֹͣ��ʱ
			IR_State = 0;
		}
		else	//������
		{
			IR_State = 1;
		}
	}
	else if(IR_State == 2)
	{
		IR_Time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		//�ж�������0����1
		if(IR_Time > (int)((float)(560+560-500)/1.085) && IR_Time < (int)((float)(560+560+500)/1.085))
		{
			IR_Data[IR_pData/8] &= ~(0x01<<(IR_pData%8));		//&=~->��Ӧλȡ��
			IR_pData++;
		}
		else if(IR_Time > (int)((float)(560+1690-500)/1.085) && IR_Time < (int)((float)(560+1690+500)/1.085))
		{
			IR_Data[IR_pData/8] |= 0x01<<(IR_pData%8);		//|=->��Ӧλȡһ
			IR_pData++;
		}
		else	//�������
		{
			IR_pData = 0;
			IR_State = 1;
		}
		if(IR_pData >= 32)	//�ж������Ƿ������
		{
			IR_pData = 0;
			if((IR_Data[0] == ~IR_Data[1]) && (IR_Data[2] == ~IR_Data[3]))	//������֤��������ʽ��Address��~Address��Command��~Command
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