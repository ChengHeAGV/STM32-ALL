#ifndef __DMA_H
#define	__DMA_H	   
#include "stm32f4xx.h"
#define UART_RX_LEN     250
#define UART_TX_LEN     250
#define UART6_RX_LEN    250
#define UART3_RX_LEN    130
#define RX_LEN 			20
#define TX_LEN          20
#define ADC1_DR_Addr   ((uint32_t)0x4001204C)
extern u16 AD_Value[30][3];
extern u8 rece_index,sendBuf[UART_RX_LEN],receBuf[UART_RX_LEN],*ps,*pr;
extern char rece2_buf[UART_RX_LEN],send2_buf[UART_RX_LEN],rece6_buf[UART6_RX_LEN],rece3_buf[UART3_RX_LEN],send3_buf[UART3_RX_LEN],send6_buf[UART6_RX_LEN];
extern u8 rece2_index,rece6_index,rece3_index,SPI_RX_BUFFER[RX_LEN],SPI_TX_BUFFER[TX_LEN];
extern double After_filter[3];
void DMA_adc1_Init(void);
void DMA_Uart4_Init(void);
void DMA_Uart2_Init(void);
void DMA_Uart6_Init(void);
void DMA_Uart3_Init(void);
void Uart4_Start_DMA_Tx(u16 size);
void Uart6_Start_DMA_Tx(u16 size);
void Uart3_Start_DMA_Tx(u16 size);
void DMA_SPI2_Init(void);
#endif






























