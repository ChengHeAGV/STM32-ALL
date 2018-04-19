#include "TM1650.h" 
#include "delay.h"

#define SCL  PBout(6)
#define DIO  PBout(7)

#define CLK_H  PBout(6) = 1
#define CLK_L  PBout(6) = 0

#define DIO_H  PBout(7) = 1
#define DIO_L  PBout(7) = 0

#define DIO_in  PBin(7)

void I2CStart(void)	//开始信号
{
	CLK_H;
	DIO_H;
	delay_us(5);
	DIO_L;
}

void I2Cask(void) //ACK信号
{
	u8 timeout = 1;
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;// 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 	//输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB
	CLK_H;
	delay_us(5);
	CLK_L;
	while((DIO_in)&&(timeout<=100))
	{
	  timeout++;	
	}
	delay_us(5);
	CLK_L;
}

void I2CStop(void) //停止信号
{
	CLK_H;
	DIO_L;
	delay_us(5);
	DIO_H;
}

void I2CWrByte(u8 oneByte) //写一个字节高位在前，低位在后
{
	GPIO_InitTypeDef GPIO_InitStructure;
	u8 i;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;// 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB	
	CLK_L;
	delay_us(1);
	for(i=0;i<8;i++)
	{	
		if(oneByte&0x80)
		{
			DIO = 1;
		}
		else
		{
			DIO = 0;
		}		
		oneByte = oneByte<<1;
		CLK_L;
		delay_us(5);
		CLK_H;
		delay_us(5);
		CLK_L;
	}
	delay_us(5);
}

u8 Scan_Key(void)	  // 按键扫描
{
	GPIO_InitTypeDef GPIO_InitStructure;
	u8 i;
	u8 rekey;
	I2CStart();
	I2CWrByte(0x49);//读按键命令
	I2Cask();
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;// 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 	//输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB
	for(i=0;i<8;i++)
	{
	   CLK_H;
	   rekey = rekey<<1;
	   if(DIO_in)
	   {
			rekey++;
	   } 
	   delay_us(5);
	   CLK_L;		
	}
	I2Cask();
	I2CStop();

	return(rekey);
}

void TM1650_Set(u8 add,u8 dat) //数码管显示
{
	//写显存必须从高地址开始写
	I2CStart();
	I2CWrByte(add); //第一个显存地址
	I2Cask();
	I2CWrByte(dat);
	I2Cask();
	I2CStop();
}

