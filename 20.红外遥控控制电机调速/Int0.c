#include <REGX52.H>

void Int0_Init()
{
	IT0 = 1;	//下降沿触发，0为低电平即触发
	IE0 = 0;	//中断标志位清零
	EX0 = 1;	//打开指定中断（前）
	EA  = 1;	//打开所有中断（后）
	PX0 = 1;	//给高优先级
}

/*
//模板，外部中断0
void Int0_Routine() interrupt 0
{
	
}
*/