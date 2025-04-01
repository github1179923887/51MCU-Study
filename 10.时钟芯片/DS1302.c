#include <REGX52.H>

#define DS1302_SECOND 0x80
#define DS1302_MINUTE 0x82
#define DS1302_HOUR	  0x84
#define DS1302_DATE   0x86
#define DS1302_MONTH  0x88
#define DS1302_DAY    0x8A	//����
#define DS1302_YEAR   0x8C
#define DS1302_WP     0x8E

sbit DS1302_SCLK = P3^6;	//ʱ��ͨ�������ؿ��ƶ�ȡ��д��
sbit DS1302_IO = P3^4;		//�����������
sbit DS1302_CE = P3^5;		//оƬʹ�ܣ���1��ͨ

//������ʱ��������
char DS1302_Time[] = {25,4,1,16,32,0,2};

void DS1302_Init()
{
	DS1302_CE = 0;
	DS1302_SCLK = 0;
}

//д�������ֺ����ݣ������ָ���ʱ�ӣ����� д�뻹�Ƕ�ȡ
//д����16������
void DS1302_WriteByte(unsigned char Command,Data)
{
	unsigned char i = 0;
	DS1302_CE = 1;
	for(i = 0;i < 8;i++)
	{
		DS1302_IO = (Command>>i)&0x01;	//��ȡCommand��iλ������Command&(0x01<<i)
		DS1302_SCLK = 1;
		//Delayxms;		��Ƭ�����ܲ��������Բ��죬����Ҫ����ʱ
		DS1302_SCLK = 0;
	}
	//�˴���ʱ���м�
	for(i = 0;i < 8;i++)
	{
		DS1302_IO = (Data>>i)&0x01;
		DS1302_SCLK = 1;	//ָ�������أ�д
		DS1302_SCLK = 0;	//ָ���½��أ���
	}
	DS1302_CE = 0;
}

//��ȡ�����֣�ֻ��15������
unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i = 0,Data = 0x00;
	DS1302_CE = 1;
	Command |= 0x01;	//��Ϊ��ȡ���λ��Ҫ����Ϊһ���������������ֱ������д��ַת��Ϊ����ַ
	for(i = 0;i < 8;i++)
	{
		DS1302_IO = (Command>>i)&0x01;
		//�ȸ�1���0��ʱ��������������������0��һ��ʱ�����½��������������������磺������������
		DS1302_SCLK = 0;
		DS1302_SCLK = 1;
	}
	//�˴���ʱ���м�
	for(i = 0;i < 8;i++)
	{
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
		if(DS1302_IO){Data |= (0x01<<i);}	//���ֵ��0����ʵ����1����Ϊֻ��0��1����ֵ����Data�� i λ ��1
	}
	DS1302_CE = 0;
	DS1302_IO = 0;
	return Data;
}

void DS1302_SetTime()
{
	DS1302_WriteByte(DS1302_WP,0x00);	//���д�뱣��
	DS1302_WriteByte(DS1302_YEAR,DS1302_Time[0]/10*16 + DS1302_Time[0]%10);	//ʮ����ת��ΪBCD��
	DS1302_WriteByte(DS1302_MONTH,DS1302_Time[1]/10*16 + DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE,DS1302_Time[2]/10*16 + DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,DS1302_Time[3]/10*16 + DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,DS1302_Time[4]/10*16 + DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,DS1302_Time[5]/10*16 + DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,DS1302_Time[6]/10*16 + DS1302_Time[6]%10);
	DS1302_WriteByte(DS1302_WP,0x80);	//��д�뱣��
}

void DS1302_ReadTime()
{
	unsigned char Temp;
	Temp = DS1302_ReadByte(DS1302_YEAR) ;
	DS1302_Time[0] = Temp/16*10+Temp%16;
	Temp = DS1302_ReadByte(DS1302_MONTH);
	DS1302_Time[1] = Temp/16*10+Temp%16;
	Temp = DS1302_ReadByte(DS1302_DATE);
	DS1302_Time[2] = Temp/16*10+Temp%16;
	Temp = DS1302_ReadByte(DS1302_HOUR);
	DS1302_Time[3] = Temp/16*10+Temp%16;
	Temp = DS1302_ReadByte(DS1302_MINUTE);
	DS1302_Time[4] = Temp/16*10+Temp%16;
	Temp = DS1302_ReadByte(DS1302_SECOND);
	DS1302_Time[5] = Temp/16*10+Temp%16;
	Temp = DS1302_ReadByte(DS1302_DAY);
	DS1302_Time[6] = Temp/16*10+Temp%16;
}

//DS1302ʱ����BCD����ʽ��ʾ�ʹ洢ʱ��
//BCD��תʮ���ƣ�DEC=BCD/16*10+BCD%16;(2λBCD)
//ʮ����תBCD�룺BCD=DEC/10*16+DEC%10;(2λBCD)

