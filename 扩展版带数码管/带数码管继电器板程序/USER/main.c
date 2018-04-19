#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "dma.h"
#include "adc.h"
#include "can.h"
#include "flash.h"
#include "Modbus_slave_170M.h"
#include "stm32f10x_flash.h"
#include "TM1650.h"
#include "74HC595.h"
#include "wdg.h"
void key_can(void);
	
//**********8级亮度调节***********************************
u8 liangdu[]={0x19,0x29,0x39,0x49,0x59,0x69,0x79,0x09};//1-8级亮度调节
//*******************************************************
u8 shuma[]={0x00,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};//共阳管0-f
//************共阴数码管显示0-F************************
u8 display[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};//共阴极
//************ START信号*******************************
int ReadNum=0;
u8 key=0,j=0,k=0,key_last=0;
uint16_t Temp_Data[20] = {0};
int main(void) 
{	
	u8 i=0;
	delay_init();	
	NVIC_Configuration();
	uart_init(9600);
	DMA_USART1_Configuration();	
	Init_LEDpin();
	IWDG_Init(4,625);    //与分频数为64,重载值为625,溢出时间为1s	 
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,0);		
	send();	
	cansend[2] = 0;
	HC595SendData(0X0fff);
	delay_ms(100);	
	TM1650_Set(0x48,0x01);//初始化为8级灰度，开显示

	ReadNum = ReadFlashNBtye(0, Temp_Data,1);
	TM1650_Set(0x68,display[Temp_Data[0]/10]);
	k = Temp_Data[0]/10;
	TM1650_Set(0x6A,display[Temp_Data[0]%10]);
	j = Temp_Data[0]%10;
	shumaguan_num = k*10+j;	
	LED0 = 1;
	while(1)
	{
		key_can();		
		send();
		i++;
		if(i==50)
		{
			IWDG_Feed();
			LED0 = ~LED0;
			i=0;
		}
		delay_ms(10);
	}
}

void key_can()
{

	key = Scan_Key();		
	if((key == 0x47)&&(key_last != 0x47))	//key1按键按下
	{
		k++;
		if(k==10)
		{				
			k=0;			
		}		
		shumaguan_num = k*10+j;
		TM1650_Set(0x68,display[k]);		
		WriteFlashOneWord(0,shumaguan_num);					
	}		
	else if((key == 0x4F)&&(key_last != 0x4F)) //key2按键按下
	{
		j++;
		if(j==10)
		{				
			j=0;			
		}					
		shumaguan_num = k*10+j;
		TM1650_Set(0x6A,display[j]);		
		WriteFlashOneWord(0,shumaguan_num);			
	}
	key_last = key;
}

