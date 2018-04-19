#include "can.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "dma.h"
//CAN³õÊ¼»¯
//tsjw:ÖØĞÂÍ¬²½ÌøÔ¾Ê±¼äµ¥Ôª.·¶Î§:CAN_SJW_1tq~ CAN_SJW_4tq
//tbs2:Ê±¼ä¶Î2µÄÊ±¼äµ¥Ôª.   ·¶Î§:CAN_BS2_1tq~CAN_BS2_8tq;
//tbs1:Ê±¼ä¶Î1µÄÊ±¼äµ¥Ôª.   ·¶Î§:CAN_BS1_1tq ~CAN_BS1_16tq
//brp :²¨ÌØÂÊ·ÖÆµÆ÷.·¶Î§:1~1024;  tq=(brp)*tpclk1
//²¨ÌØÂÊ=Fpclk1/((tbs1+1+tbs2+1+1)*brp);
//mode:CAN_Mode_Normal,ÆÕÍ¨Ä£Ê½;CAN_Mode_LoopBack,»Ø»·Ä£Ê½;
//Fpclk1µÄÊ±ÖÓÔÚ³õÊ¼»¯µÄÊ±ºòÉèÖÃÎª36M,Èç¹ûÉèÖÃCAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_LoopBack);
//Ôò²¨ÌØÂÊÎª:36M/((8+9+1)*4)=500Kbps
//·µ»ØÖµ:0,³õÊ¼»¯OK;
//ÆäËû,³õÊ¼»¯Ê§°Ü; 
u8 CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode)
{ 
	GPIO_InitTypeDef 		GPIO_InitStructure; 
	CAN_InitTypeDef        	CAN_InitStructure;
	CAN_FilterInitTypeDef  	CAN_FilterInitStructure;
#if CAN_RX0_INT_ENABLE 
	NVIC_InitTypeDef  		NVIC_InitStructure;
#endif
                											 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//Ê¹ÄÜCAN1Ê±ÖÓ
	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//¸´ÓÃÍÆÍì
	GPIO_Init(GPIOB, &GPIO_InitStructure);			//³õÊ¼»¯IO

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//ÉÏÀ­ÊäÈ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);			//³õÊ¼»¯IO
	
	GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);//¶Ë¿ÚÖØÓ³Éä
	/* CAN register init */  
	CAN_DeInit(CAN1);
	CAN_StructInit(&CAN_InitStructure);
	//CANµ¥ÔªÉèÖÃ
	CAN_InitStructure.CAN_TTCM=DISABLE;			//·ÇÊ±¼ä´¥·¢Í¨ĞÅÄ£Ê½  
	CAN_InitStructure.CAN_ABOM=DISABLE;			//Èí¼ş×Ô¶¯ÀëÏß¹ÜÀí	 
	CAN_InitStructure.CAN_AWUM=DISABLE;			//Ë¯ÃßÄ£Ê½Í¨¹ıÈí¼ş»½ĞÑ(Çå³ıCAN->MCRµÄSLEEPÎ»)
	CAN_InitStructure.CAN_NART=ENABLE;			//½ûÖ¹±¨ÎÄ×Ô¶¯´«ËÍ 
	CAN_InitStructure.CAN_RFLM=DISABLE;		 	//±¨ÎÄ²»Ëø¶¨,ĞÂµÄ¸²¸Ç¾ÉµÄ  
	CAN_InitStructure.CAN_TXFP=DISABLE;			//ÓÅÏÈ¼¶ÓÉ±¨ÎÄ±êÊ¶·û¾ö¶¨ 
	CAN_InitStructure.CAN_Mode= mode;	        //Ä£Ê½ÉèÖÃ£º mode:0,ÆÕÍ¨Ä£Ê½;1,»Ø»·Ä£Ê½; 
	//ÉèÖÃ²¨ÌØÂÊ
	CAN_InitStructure.CAN_SJW=tsjw;				//ÖØĞÂÍ¬²½ÌøÔ¾¿í¶È(Tsjw)Îªtsjw+1¸öÊ±¼äµ¥Î»  CAN_SJW_1tq	 CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
	CAN_InitStructure.CAN_BS1=tbs1; 			//Tbs1=tbs1+1¸öÊ±¼äµ¥Î»CAN_BS1_1tq ~CAN_BS1_16tq
	CAN_InitStructure.CAN_BS2=tbs2;				//Tbs2=tbs2+1¸öÊ±¼äµ¥Î»CAN_BS2_1tq ~	CAN_BS2_8tq
	CAN_InitStructure.CAN_Prescaler=brp;        //·ÖÆµÏµÊı(Fdiv)Îªbrp+1	
	CAN_Init(CAN1, &CAN_InitStructure);        	//³õÊ¼»¯CAN1 

	CAN_FilterInitStructure.CAN_FilterNumber=0;	//¹ıÂËÆ÷0
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 	//ÆÁ±ÎÎ»Ä£Ê½
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; 	//32Î»¿í 
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;	//32Î»ID
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32Î»MASK
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//¹ıÂËÆ÷0¹ØÁªµ½FIFO0
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;//¼¤»î¹ıÂËÆ÷0

	CAN_FilterInit(&CAN_FilterInitStructure);			//ÂË²¨Æ÷³õÊ¼»¯
	
#if CAN_RX0_INT_ENABLE 
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);				//FIFO0ÏûÏ¢¹ÒºÅÖĞ¶ÏÔÊĞí.		    

	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     // Ö÷ÓÅÏÈ¼¶Îª1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // ´ÎÓÅÏÈ¼¶Îª0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
	return 0;
}   
deflag flag={0,0,0,0};
#if CAN_RX0_INT_ENABLE	//Ê¹ÄÜRX0ÖĞ¶Ï
//ÖĞ¶Ï·şÎñº¯Êı	
CanRxMsg RxMessage;
void USB_LP_CAN1_RX0_IRQHandler(void)
{
    CAN_Receive(CAN1, 0, &RxMessage);
	if(RxMessage.StdId == 0x10)
	{
		if(RxMessage.Data[3] == 0x55)//Ö÷¿Ø°å¸´Î»´¦Àí
		{
			Can_Send_Msg(cansend,3);
		}
	}
}
#endif
//JDQ0¶ÔÓ¦µç»ú1·½Ïò	JDQ1¶ÔÓ¦µç»ú2·½Ïò	JDQ2¶ÔÓ¦µç»ú3·½Ïò	JDQ3¶ÔÓ¦µç»ú4·½Ïò
//can·¢ËÍÒ»×éÊı¾İ(¹Ì¶¨¸ñÊ½:IDÎª0X12,±ê×¼Ö¡,Êı¾İÖ¡)	
//len:Êı¾İ³¤¶È(×î´óÎª8)				     
//msg:Êı¾İÖ¸Õë,×î´óÎª8¸ö×Ö½Ú.
//·µ»ØÖµ:0,³É¹¦;
//ÆäËû,Ê§°Ü;
u8 Can_Send_Msg(int* msg,u8 len)
{	
	u8 mbox;
	u16 i=0;
	CanTxMsg TxMessage;
	TxMessage.StdId=22;	// ±ê×¼±êÊ¶·û 
	TxMessage.ExtId=0;			// ÉèÖÃÀ©Õ¹±êÊ¾·û 
	TxMessage.IDE=CAN_Id_Standard; 	// ±ê×¼Ö¡
	TxMessage.RTR=CAN_RTR_Data;		// Êı¾İÖ¡
	TxMessage.DLC=len;				// Òª·¢ËÍµÄÊı¾İ³¤¶È
	for(i=0;i<len;i++)
	TxMessage.Data[i]=msg[i];			          
	mbox= CAN_Transmit(CAN1, &TxMessage);   
	i=0; 
	while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//µÈ´ı·¢ËÍ½áÊø
	if(i>=0XFFF)return 1;
	return 0;	 
}
//can¿Ú½ÓÊÕÊı¾İ²éÑ¯
//buf:Êı¾İ»º´æÇø;	 
//·µ»ØÖµ:0,ÎŞÊı¾İ±»ÊÕµ½;
//ÆäËû,½ÓÊÕµÄÊı¾İ³¤¶È;
u8 Can_Receive_Msg(u8 *buf)
{		   		   
 	u32 i;
	CanRxMsg RxMessage;
    if( CAN_MessagePending(CAN1,CAN_FIFO0)==0)return 0;		//Ã»ÓĞ½ÓÊÕµ½Êı¾İ,Ö±½ÓÍË³ö 
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);//¶ÁÈ¡Êı¾İ	
    for(i=0;i<8;i++)
    buf[i]=RxMessage.Data[i];  
	return RxMessage.DLC;	
}
int cansend[4]={0,0,0,1};
void can_send(void)
{
	Can_Send_Msg(cansend,4);
}
