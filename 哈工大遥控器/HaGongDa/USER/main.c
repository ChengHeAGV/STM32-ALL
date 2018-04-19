#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "dma.h"
#include "adc.h"
#include "math.h"
#include "string.h"
#include "can.h"
#include "wdg.h"
u8 xintiao_buf[4] = {0xff, 0xff, 0xff, 0xff};
int main(void)
{
    u16 i = 0;
    delay_init();
    NVIC_Configuration();
    uart1_init(9600);
    uart2_init(115200);
    DMA_USART1_Configuration();
    DMA_USART2_Configuration();
    DMA_ADC_Configuration();
    ADC1_Configuration();
    Init_LEDpin();
	BEEP = 1;
	delay_ms(500);
	BEEP = 0;	
    IWDG_Init(4, 625);   //与分频数为64,重载值为625,溢出时间为1s
    CAN_Mode_Init(CAN_SJW_1tq, CAN_BS2_8tq, CAN_BS1_9tq, 4, 0);
    Can_Send_Msg(cansend, 4);
    cansend[3] = 0;//清除复位标志

    while(1)
    {			
		yaokong_fenxi();
        i++;
        if(i == 50)
        {
            IWDG_Feed();
            LED_CPU = ~LED_CPU;
            i = 0;
        }	
        delay_ms(10);
    }
}

