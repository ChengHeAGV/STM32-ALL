#include "adc.h"
#include "dma.h"
#define N 30
float  After_filter[3];
void ADC1_Configuration(void)   
{   
    ADC_InitTypeDef ADC_InitStructure;  
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1,ENABLE); 

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	
	
	ADC_DeInit(ADC1);	
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;   
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; //连续转换开启
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;   
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;   
    ADC_InitStructure.ADC_NbrOfChannel = 3;  //设置转换序列长度
    ADC_Init(ADC1, &ADC_InitStructure);   

    ADC_TempSensorVrefintCmd(ENABLE);//ADC内置温度传感器失使能   
        
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_239Cycles5);   
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_239Cycles5); 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 3, ADC_SampleTime_239Cycles5); 	
 
    ADC_Cmd(ADC1, ENABLE);   
 
    ADC_DMACmd(ADC1, ENABLE);//开启DAM   
    //ADC自校准 
    ADC_ResetCalibration(ADC1);   
 
    while(ADC_GetResetCalibrationStatus(ADC1));   
   
    ADC_StartCalibration(ADC1);   
  
    while(ADC_GetCalibrationStatus(ADC1));   

    ADC_SoftwareStartConvCmd(ADC1, ENABLE); //启动ADC 
}  
void filter(void)
{
   int  sum = 0;
   u8 count,i;
   for(i=0;i<3;i++)
   {
		for (count=0;count<N;count++)
		{
		   sum += AD_Value[count][i];
		}
		After_filter[i]=sum/N;
		sum=0;
   }  
}
void DMA1_Channel1_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC1) != RESET)
	{
	  filter();
	  DMA_ClearITPendingBit(DMA1_IT_TC1);
	}
}









