#ifndef __DMA_H
#define __DMA_H

#include "sys.h"


void DMA_USART1_Configuration(void);
void DMA_ADC_Configuration(void);
void Uart1_Start_DMA_Tx(u16 size);
extern u8 rece3_buf[UART_RX_LEN],send3_buf[UART_RX_LEN],rece3_index;
extern u16 AD_Value[30][4];
#endif


