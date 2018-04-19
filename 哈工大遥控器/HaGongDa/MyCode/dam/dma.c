#include "dma.h"
#define ADC1_DR_Address    ((uint32_t)0x4001244C)

u8  Uart1_Rx[UART_RX_LEN];
u8  Uart2_Rx[UART_RX_LEN];
u8	Uart1_Send[UART_RX_LEN];
u8	Uart2_Send[UART_RX_LEN];
u16 AD_Value[30][3];
void DMA_USART1_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;
    DMA_DeInit(DMA1_Channel5); 
 
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR); 
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Uart1_Rx; 
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; 
    DMA_InitStructure.DMA_BufferSize = UART_RX_LEN; 
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; 
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; 
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; 
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; 	
    DMA_Init(DMA1_Channel5,&DMA_InitStructure); 
    DMA_Cmd(DMA1_Channel5,ENABLE);
	
	//DMA1通道4配置  
	DMA_DeInit(DMA1_Channel4);  
	//外设地址  
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);  
	//内存地址  
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Uart1_Send;  
	//dma传输方向单向  
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  
	//设置DMA在传输时缓冲区的长度  
	DMA_InitStructure.DMA_BufferSize = UART_RX_LEN;  
	//设置DMA的外设递增模式，一个外设  
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
	//设置DMA的内存递增模式  
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
	//外设数据字长  
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
	//内存数据字长  
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;  
	//设置DMA的传输模式  
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  
	//设置DMA的优先级别  
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;  
	//设置DMA的2个memory中的变量互相访问  
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  
	DMA_Init(DMA1_Channel4,&DMA_InitStructure);  
	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);
	DMA_Cmd(DMA1_Channel4, DISABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	NVIC_Init(&NVIC_InitStructure);
	
}
void Uart1_Start_DMA_Tx(u16 size)
{
    DMA_SetCurrDataCounter(DMA1_Channel4,size);
    DMA_Cmd(DMA1_Channel4, ENABLE);
}
void  DMA1_Channel4_IRQHandler(void)//串口1发送DMA中断
{
    if(DMA_GetITStatus(DMA1_IT_TC4))
    {
		DMA_ClearITPendingBit(DMA1_IT_TC4);
		DMA_Cmd(DMA1_Channel4, DISABLE);
    }
}
void DMA_USART2_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;
    DMA_DeInit(DMA1_Channel6); 
 
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART2->DR); 
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Uart2_Rx; 
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; 
    DMA_InitStructure.DMA_BufferSize = UART_RX_LEN; 
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; 
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; 
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; 
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; 	
    DMA_Init(DMA1_Channel6,&DMA_InitStructure); 
    DMA_Cmd(DMA1_Channel6,ENABLE);
	
	//DMA1通道7配置  
	DMA_DeInit(DMA1_Channel7);  
	//外设地址  
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART2->DR);  
	//内存地址  
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Uart2_Send;  
	//dma传输方向单向  
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  
	//设置DMA在传输时缓冲区的长度  
	DMA_InitStructure.DMA_BufferSize = UART_RX_LEN;  
	//设置DMA的外设递增模式，一个外设  
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
	//设置DMA的内存递增模式  
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
	//外设数据字长  
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
	//内存数据字长  
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;  
	//设置DMA的传输模式  
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  
	//设置DMA的优先级别  
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;  
	//设置DMA的2个memory中的变量互相访问  
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  
	DMA_Init(DMA1_Channel7,&DMA_InitStructure);  
	DMA_ITConfig(DMA1_Channel7,DMA_IT_TC,ENABLE);
	DMA_Cmd(DMA1_Channel7, DISABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel7_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	NVIC_Init(&NVIC_InitStructure);
	
}
void Uart2_Start_DMA_Tx(u16 size)
{
    DMA_SetCurrDataCounter(DMA1_Channel7,size);
    DMA_Cmd(DMA1_Channel7, ENABLE);
}
void  DMA1_Channel7_IRQHandler(void)//串口2发送DMA中断
{
    if(DMA_GetITStatus(DMA1_IT_TC7))
    {
		DMA_ClearITPendingBit(DMA1_IT_TC7);
		DMA_Cmd(DMA1_Channel7, DISABLE);
    }
}
void DMA_ADC_Configuration(void)   
{ 
	DMA_InitTypeDef DMA_InitStructure; 
    DMA_DeInit(DMA1_Channel1);   
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;   
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_Value;   
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;   
 
    DMA_InitStructure.DMA_BufferSize = 90;   
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;   
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;   
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;   
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;   
  
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;   
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;   
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;   
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);   
 
    DMA_Cmd(DMA1_Channel1, ENABLE);
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);   
} 
