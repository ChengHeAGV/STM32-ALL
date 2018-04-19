#ifndef __DMA_H
#define __DMA_H

#include "sys.h"


extern void DMA_USART1_Configuration(void);
extern void DMA_USART2_Configuration(void);
extern void Uart1_Start_DMA_Tx(u16 size);
extern void Uart2_Start_DMA_Tx(u16 size);
extern void DMA_ADC_Configuration(void);
extern u8 Uart1_Rx[UART_RX_LEN],Uart2_Rx[UART_RX_LEN],Uart1_Send[UART_RX_LEN],Uart2_Send[UART_RX_LEN];
extern u16 AD_Value[30][3];
#endif


