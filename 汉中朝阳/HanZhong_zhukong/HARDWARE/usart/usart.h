#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

void USART1_Configuration(u32 bound);
void USART4_Configuration(u32 bound);
void USART6_Configuration(u32 bound);
void USART2_Configuration(u32 bound);
void USART3_Configuration(u32 bound);
int fputc(int ch, FILE *f);
#endif


