#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "dma.h"
#include "adc.h"
#include "math.h"
#include "string.h"
float adc_x,adc_y,adc_z;
int i=0;
void LCD_disp(u8 dir,u16 x,u16 y);
void yaogan_fenxi(void);
u8 buf_clear[6]={0xAA,0x52,0xCC,0x33,0xC3,0x3C};
float flagX,flagY,flagZ;
void send(u8* buf,u16 len)
{
	for(i=0;i<len;i++)	
	{
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC)!=1);	
		USART_SendData(USART2, buf[i]);		
	}
}

void send_str(char*str,u16 x,u16 y)
{
	u8 buf1[6]={0XAA,0X55,0X00,0X00,0X00,0X00};//头，坐标
	u8 buf3[4]={0XCC,0X33,0XC3,0X3C};//尾

	//1，更新坐标
	buf1[2]=x>>8;
	buf1[3]=x&0xff;
	buf1[4]=y>>8;
	buf1[5]=y&0xff;

	send(buf1,6);
	send(str,strlen(str));
	send(buf3,4);
}
int main(void)
{		
	u16 i;
	u8*dis;
	delay_init();	
	NVIC_Configuration();
	uart1_init(115200);
	uart2_init(115200);
	DMA_USART1_Configuration();
	DMA_USART2_Configuration();
	DMA_ADC_Configuration();
	ADC1_Configuration();
	Init_LEDpin();
	LED1 = 0;LED2 = 0;LED3 = 0;LED4 = 0;LED5 = 0;
	LED_CPU = 1;
	delay_ms(5500);
	send(buf_clear,sizeof(buf_clear));
	while(1)
	{
		yaogan_fenxi();
		delay_ms(20);
	}
}
//Uart1_Send[0]	方向
//Uart1_Send[1]	速度
//Uart1_Send[2]	手自动
//Uart1_Send[3]	故障复位
//Uart1_Send[4]	起升
//Uart1_Send[5]	下降
//Uart1_Send[6]	操作使能
//Uart1_Send[7]	急停

void yaogan_fenxi()
{
	char x[100],y[100],z[100],now[100];
	float max=145.0,min=105.0;
	adc_z = After_filter[0]*3.3/4096*100;//Z	
	adc_y = After_filter[1]*3.3/4096*100;//Y
	adc_x = After_filter[2]*3.3/4096*100;//X
	sprintf(x,"x:%3.f",adc_x);
	sprintf(y,"y:%3.f",adc_y);
	sprintf(z,"z:%3.f",adc_z);
	send_str(x,100,20);
	send_str(y,100,60);
	send_str(z,100,100);
	if(adc_x!=flagX||adc_y!=flagY||adc_z!=flagZ)
	{
		flagX = adc_x;
		flagY = adc_y;
		flagZ = adc_z;
		//左上
		if(flagX <min && flagY > max)
		{
			 Uart1_Send[0] = 5;
			 Uart1_Send[1] = (flagY-max)/(197.0-max)*100;
			 Uart1_Send[1] = (Uart1_Send[1]<=100) ? Uart1_Send[1]:100;
			 sprintf(now,"左上:%3d",Uart1_Send[1]);
			 send_str(now,100,140);
		}//右上
		else if(flagX >130 && flagY > max)
		{
			 Uart1_Send[0] = 6;
			 Uart1_Send[1] = (flagY-max)/(188.0-max)*100;
			 Uart1_Send[1] = (Uart1_Send[1]<=100) ? Uart1_Send[1]:100;
			 sprintf(now,"右上:%3d",Uart1_Send[1]);
			 send_str(now,100,140);
		}//左下
		else if(flagX <min && flagY < min)
		{
			 Uart1_Send[0] = 7;
			 Uart1_Send[1] = (min-flagY)/(min-55.0)*100;
			 Uart1_Send[1] = (Uart1_Send[1]<=100) ? Uart1_Send[1]:100;
			 sprintf(now,"左下:%3d",Uart1_Send[1]);
			 send_str(now,100,140);
		}//右下
		else if(flagX >max && flagY < min)
		{
			 Uart1_Send[0] = 8;
			 Uart1_Send[1] = (min-flagY)/(min-55.0)*100;
			 Uart1_Send[1] = (Uart1_Send[1]<=100) ? Uart1_Send[1]:100;
			 sprintf(now,"右下:%3d",Uart1_Send[1]);
			 send_str(now,100,140);
		}//左移
		else if(flagX < min )
		{
			 Uart1_Send[0] = 3;
			 Uart1_Send[1] = (min-flagX)/(min-27.0)*100;
			 Uart1_Send[1] = (Uart1_Send[1]<=100) ? Uart1_Send[1]:100;
			 sprintf(now,"左移:%3d",Uart1_Send[1]);
			 send_str(now,100,140);
		 }//右移
		else if(flagX > max )
		{
			 Uart1_Send[0] = 4;
			 Uart1_Send[1] = (flagX-max)/(223-max)*100;
			 Uart1_Send[1] = (Uart1_Send[1]<=100) ? Uart1_Send[1]:100;
			 sprintf(now,"右移:%3d",Uart1_Send[1]);
			 send_str(now,100,140);

		}//前进
		else if(flagY > max)
		{
			 Uart1_Send[0] = 1;
			 Uart1_Send[1] = (flagY-max)/(197-max)*100;
			 Uart1_Send[1] = (Uart1_Send[1]<=100) ? Uart1_Send[1]:100;
			 sprintf(now,"前进:%3d",Uart1_Send[1]);
			 send_str(now,100,140);
		}//后退
		else if(flagY < min)
		{
			 Uart1_Send[0] = 2;
			 Uart1_Send[1] = (min-flagY)/(min-25)*100;
			 Uart1_Send[1] = (Uart1_Send[1]<=100) ? Uart1_Send[1]:100;
			 sprintf(now,"后退:%3d",Uart1_Send[1]);
			 send_str(now,100,140);
		}//左旋
		else if(flagZ < min)
		{
			 Uart1_Send[0] = 9;
			 Uart1_Send[1] = (min-flagZ)/(min-25)*100;
			 Uart1_Send[1] = (Uart1_Send[1]<=100) ? Uart1_Send[1]:100;
			 sprintf(now,"左旋:%3d",Uart1_Send[1]);
			 send_str(now,100,140);
		}//右旋
		else if(flagZ > max)
		{
			 Uart1_Send[0] = 10;
			 Uart1_Send[1] = (flagZ-max)/(225-max)*100;
			 Uart1_Send[1] = (Uart1_Send[1]<=100) ? Uart1_Send[1]:100;
			 sprintf(now,"右旋:%3d",Uart1_Send[1]);
			 send_str(now,100,140);
		}//停止
		else if((flagX >min && flagX < max)||(flagY >min && flagY < max)||(flagZ >min && flagZ < max))
		{
			 Uart1_Send[0] = 0;
			 Uart1_Send[1]  = 0;
			 sprintf(now,"停止:%3d",Uart1_Send[1]);
			 send_str(now,100,140);
		}
  }
	Uart1_Send[2] = SouZiDong;
	Uart1_Send[3] = FuWei;
	Uart1_Send[4] = QiSheng;
	Uart1_Send[5] = XiaJiang;
	Uart1_Send[6] = ShiNeng;
	Uart1_Send[7] = JiTing;
	Uart1_Send[8] = YaoGan_Key;
	Uart1_Start_DMA_Tx(9);	
}
void LCD_disp(u8 dir,u16 x,u16 y)
{
	switch (dir)
	{
		case 1://前进
				send_str("前进",x,y);
				break;
		case 2://后退
				send_str("后退",x,y);				
				break;
		case 3://左移
				send_str("左移",x,y);				
				break;
		case 4://右移
				send_str("右移",x,y);				
				break;
		case 5://左上
				send_str("左上",x,y);				
				break;
		case 6://左下
				send_str("左下",x,y);			
				break;
		case 7://右上
				send_str("右上",x,y);			
				break;
		case 8://右下
				send_str("右下",x,y);				
				break;
		case 9://左旋
				send_str("左旋",x,y);				
				break;
		case 10://右旋
				send_str("右旋",x,y);			
				break;
		case 0://停止
				send_str("停止",x,y);				
				break;
		default:
			break;
	}
}


