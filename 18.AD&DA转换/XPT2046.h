#ifndef __XPT2046_H__
#define __XPT2046_H__

//宏定义控制字，设置原理见手册数字接口部分
//8位
#define XPT2046_XP_8		0x9C	//滑动变阻器
#define XPT2046_YP_8		0xDC	//热敏电阻
#define XPT2046_VBAT_8		0xAC	//光敏电阻
#define XPT2046_AUX_8		0xEC
//12位
#define XPT2046_XP_12		0x94
#define XPT2046_YP_12		0xD4
#define XPT2046_VBAT_12		0xA4
#define XPT2046_AUX_12		0xE4

unsigned int XPT2046_ReadAD(unsigned char Command);

#endif