#include <REGX52.H>

void Int0_Init()
{
	IT0 = 1;	//�½��ش�����0Ϊ�͵�ƽ������
	IE0 = 0;	//�жϱ�־λ����
	EX0 = 1;	//��ָ���жϣ�ǰ��
	EA  = 1;	//�������жϣ���
	PX0 = 1;	//�������ȼ�
}

/*
//ģ�壬�ⲿ�ж�0
void Int0_Routine() interrupt 0
{
	
}
*/