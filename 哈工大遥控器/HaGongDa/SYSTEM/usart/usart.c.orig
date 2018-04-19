#include "usart.h"	
#include "dma.h"
#include "led.h"
#include "adc.h"
#include "can.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos 使用	  
#endif 
 
//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
    USART2->DR = (u8) ch;      
	return ch;
}
#endif 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	  
  
void uart1_init(u32 bound)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
	//USART1_TX   PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

	//USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART1, &USART_InitStructure); //初始化串口
	
	USART_ITConfig(USART1,USART_IT_TC,DISABLE); 
    USART_ITConfig(USART1,USART_IT_RXNE,DISABLE); 
    USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);//开启串口空闲中断
	
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);//采用DMA方式接收
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);//采用DMA方式接收
	USART_Cmd(USART1, ENABLE); 
}
void uart2_init(u32 bound)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART2
	//USART1_TX   PA.2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//USART1_RX	  PA.3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

	//USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART2, &USART_InitStructure); //初始化串口
	
	USART_ITConfig(USART2,USART_IT_TC,DISABLE); 
    USART_ITConfig(USART2,USART_IT_RXNE,DISABLE); 
    USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);//开启串口空闲中断
	
	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);//采用DMA方式接收
//	USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);//采用DMA方式接收
	USART_Cmd(USART2, ENABLE); 
}
//Uart1_Send[0]	方向
//Uart1_Send[1]	速度
//Uart1_Send[2]	行走/升降
//Uart1_Send[3]	直行/斜行
//Uart1_Send[4]	下降
//Uart1_Send[5]	急停
//Uart1_Send[6]	快速/慢速
//Uart1_Send[7]	起升
float adc_x,adc_y,adc_z;
float flagX,flagY,flagZ;
u16 anjian_temp;
void yaokong_fenxi()
{
	char x[100],y[100],z[100];
	float max=145.0,min=105.0;
	adc_z = After_filter[0]*3.3/4096*100;//Z	
	adc_y = After_filter[1]*3.3/4096*100;//Y
	adc_x = After_filter[2]*3.3/4096*100;//X
	Uart1_Send[2] = XingZou_OR_ShengJiang|(ZhiXing_OR_XieXing<<1)|(XiaJiang<<2)|(JiTing<<3)
					|(KuaiSu_OR_ManSu<<4)|(QiSheng<<5)|(YaoGan_Key<<6);
	sprintf(x,"x:%3.f",adc_x);
	sprintf(y,"y:%3.f",adc_y);
	sprintf(z,"z:%3.f",adc_z);
	if(KuaiSu_OR_ManSu == 1)
	{
		KuaiSuDeng = 0;
		ManSuDeng = 1;
	}
	else
	{
		KuaiSuDeng = 1;
		ManSuDeng = 0;		
	}
	if(XingZou_OR_ShengJiang == 1)//选择行走时
	{
		ShengJiangDeng = 1;
		XingZouDeng = 0;
		
		if(adc_x!=flagX||adc_y!=flagY||adc_z!=flagZ||Uart1_Send[2]!=anjian_temp)
		{
			flagX = adc_x;
			flagY = adc_y;
			flagZ = adc_z;
			anjian_temp = Uart1_Send[2];
			flag.change_flag = 1;
			if(ZhiXing_OR_XieXing == 0)//选择斜行
			{
				ZhiXingDeng = 1;
				XieXingDeng = 0;
				//左上
				if(flagX <min && flagY > max)
				{
					 Uart1_Send[0] = 5;
					 Uart1_Send[1] = (flagY-max)/(197.0-max)*100;
					 Uart1_Send[1] = (Uart1_Send[1]<=100) ? Uart1_Send[1]:100;
				}//右上
				else if(flagX >130 && flagY > max)
				{
					 Uart1_Send[0] = 6;
					 Uart1_Send[1] = (flagY-max)/(188.0-max)*100;
					 Uart1_Send[1] = (Uart1_Send[1]<=100) ? Uart1_Send[1]:100;
				}//左下
				else if(flagX <min && flagY < min)
				{
					 Uart1_Send[0] = 7;
					 Uart1_Send[1] = (min-flagY)/(min-55.0)*100;
					 Uart1_Send[1] = (Uart1_Send[1]<=100) ? Uart1_Send[1]:100;
				}//右下
				else if(flagX >max && flagY < min)
				{
					 Uart1_Send[0] = 8;
					 Uart1_Send[1] = (min-flagY)/(min-55.0)*100;
					 Uart1_Send[1] = (Uart1_Send[1]<=100) ? Uart1_Send[1]:100;
				}//左移
				else if(flagX < min )
				{
					 Uart1_Send[0] = 3;
					 Uart1_Send[1] = (min-flagX)/(min-27.0)*100;
					 Uart1_Send[1] = (Uart1_Send[1]<=100) ? Uart1_Send[1]:100;
				 }//右移
				else if(flagX > max )
				{
					 Uart1_Send[0] = 4;
					 Uart1_Send[1] = (flagX-max)/(223-max)*100;
					 Uart1_Send[1] = (Uart1_Send[1]<=100) ? Uart1_Send[1]:100;

				}//左旋
				else if(flagZ < min)
				{
					 Uart1_Send[0] = 9;
					 Uart1_Send[1] = (min-flagZ)/(min-25)*100;
					 Uart1_Send[1] = (Uart1_Send[1]<=100) ? Uart1_Send[1]:100;
				}//右旋
				else if(flagZ > max)
				{
					 Uart1_Send[0] = 10;
					 Uart1_Send[1] = (flagZ-max)/(225-max)*100;
					 Uart1_Send[1] = (Uart1_Send[1]<=100) ? Uart1_Send[1]:100;
				}//停止
				else if((flagX >min && flagX < max)||(flagY >min && flagY < max)||(flagZ >min && flagZ < max))
				{
					 Uart1_Send[0] = 0;
					 Uart1_Send[1]  = 0;
				}			
			}
			else//选择直行
			{
				ZhiXingDeng = 0;
				XieXingDeng = 1;
				//前进
				if(flagY > max)
				{
					 Uart1_Send[0] = 1;
					 Uart1_Send[1] = (flagY-max)/(197-max)*100;
					 Uart1_Send[1] = (Uart1_Send[1]<=100) ? Uart1_Send[1]:100;
				}//后退
				else if(flagY < min)
				{
					 Uart1_Send[0] = 2;
					 Uart1_Send[1] = (min-flagY)/(min-25)*100;
					 Uart1_Send[1] = (Uart1_Send[1]<=100) ? Uart1_Send[1]:100;
				}//停止
				else if((flagX >min && flagX < max)||(flagY >min && flagY < max)||(flagZ >min && flagZ < max))
				{
					 Uart1_Send[0] = 0;
					 Uart1_Send[1]  = 0;
				}				
			}		
		}
		else
		{
			flag.change_flag = 0;
		}		
	}	
	else//选择升降时停止全向车
	{
		ShengJiangDeng = 0;
		XingZouDeng = 1;
		
		Uart1_Send[0] = 0;
		Uart1_Send[1]  = 0;
	}
}
void usart_send(void)
{
	if(flag.change_flag ==1)
	Uart1_Start_DMA_Tx(3);
}
u16 USART1_Length = 0,USART2_Length = 0; 
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
	OSIntEnter();    
#endif 
    if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET) 
    { 
        DMA_Cmd(DMA1_Channel5,DISABLE);
        USART1_Length = USART1->SR; 
        USART1_Length = USART1->DR; 
        USART1_Length = UART_RX_LEN - DMA_GetCurrDataCounter(DMA1_Channel5); 
        DMA1_Channel5->CNDTR = UART_RX_LEN;
		
		flag.usart_flag = 1;		
		if((Uart1_Rx[0]==1)&&(Uart1_Rx[1]==1)&&(Uart1_Rx[2]==2))
		{
			flag.ShiNeng_flag = 0;
			YaoKongJinZhiDeng = 1;//遥控器有效
		}
		else if((Uart1_Rx[0]==1)&&(Uart1_Rx[1]==2)&&(Uart1_Rx[2]==3))
		{
			flag.ShiNeng_flag = 1;
			YaoKongJinZhiDeng = 0;//遥控器无效
		}
		else if((Uart1_Rx[0]==1)&&(Uart1_Rx[1]==0)&&(Uart1_Rx[2]==1))//主控板复位
		{
			Uart1_Start_DMA_Tx(3);
		}

        DMA_Cmd(DMA1_Channel5, ENABLE);
    }  
#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
	OSIntExit();  											 
#endif
} 
void USART2_IRQHandler(void)                	//串口2中断服务程序
{
#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
	OSIntEnter();    
#endif 
    if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET) 
    { 
        DMA_Cmd(DMA1_Channel6,DISABLE);
        USART2_Length = USART2->SR; 
        USART2_Length = USART2->DR; 
        USART2_Length = UART_RX_LEN - DMA_GetCurrDataCounter(DMA1_Channel6); 
        DMA1_Channel6->CNDTR = UART_RX_LEN;
		
        DMA_Cmd(DMA1_Channel6, ENABLE);
    }  
#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
	OSIntExit();  											 
#endif
} 
#endif	

