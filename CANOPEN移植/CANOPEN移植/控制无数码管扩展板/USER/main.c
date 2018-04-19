#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "dma.h"
#include "adc.h"
#include "mycan.h"
#include "can.h"
#include "stm32f1_canfestival.h"
#include "gk.h"
#include "pdo.h"
#include "nmtMaster.h"
#include "ds401.h"
int main(void)
{		
	delay_init();	
	NVIC_Configuration();
	uart_init(9600);
	DMA_USART1_Configuration();
	
	Init_LEDpin();
//	CanopenInit();
 
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,0);	
	initTimer();
	setNodeId (&gk_Data, CAN1_NODE_ID);	
	setState(&gk_Data,Initialisation);
	
	while(1)
	{	
		DS401.digital_output_handler(&gk_Data, digital_output, sizeof(digital_output));
		JDQ0 = digital_output[0]&0x01;		
		JDQ1 = (digital_output[0]>>1)&0x01;
		JDQ2 = (digital_output[0]>>2)&0x01;
		JDQ3 = (digital_output[0]>>3)&0x01;
		JDQ4 = (digital_output[0]>>4)&0x01;
		JDQ5 = (digital_output[0]>>5)&0x01;
		JDQ6 = (digital_output[0]>>6)&0x01;
		JDQ7 = (digital_output[0]>>7)&0x01;
		JDQ8 = (digital_output[0]>>8)&0x01;
		JDQ9 = (digital_output[0]>>9)&0x01;
		JDQ10 = (digital_output[0]>>10)&0x01;
		JDQ11 = (digital_output[0]>>11)&0x01;
		digital_input[0] = IN0|(IN1<<1)|(IN2<<2)|(IN3<<3)|(IN4<<4)|(IN5<<5)|(IN6<<6)|(IN7<<7)|(IN8<<8)|(IN9<<9)|(IN10<<10);
		DS401.digital_input_handler(&gk_Data, digital_input, sizeof(digital_input));		
	}
}


