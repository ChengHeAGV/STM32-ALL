#ifndef __TLC5620_H
#define __TLC5620_H

#include "sys.h"

#define TLC5620RNG 1//电压的倍数

#define DADATA PGout(0)	//TLC5620 DA转换器的DATA位
#define DACLK  PGout(1)	//TLC5620 DA转换器的CLK位
#define DALOAD PEout(7)	//TLC5620 DA转换器的LOAD位
#define DALDAC PEout(8)	//TLC5620 DA转换器的LDAC位

void TLC5620_Init(void);//初始化		 	
void TLC5620_OUT(u8 CHn,double date);//
void TLC5620_OUTnum(u8 CHn,u8 date);
#endif
