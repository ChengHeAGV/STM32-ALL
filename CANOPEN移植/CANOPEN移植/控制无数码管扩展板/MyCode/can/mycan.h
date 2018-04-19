#ifndef __CAN_H
#define __CAN_H	 
#include "sys.h"	    
 
//CAN接收RX0中断使能
#define CAN_RX0_INT_ENABLE	1		//0,不使能;1,使能.	
#define  CAN1_NODE_ID   0x01       //CAN 节点ID		

typedef struct {
  u16 cob_id;	/**< message's ID */
  u8 rtr;		/**< remote transmission request. (0 if not rtr message, 1 if rtr message) */
  u8 len;		/**< message's length (0 to 8) */
  u8 data[8];   /**< message's datas */
} can_message_t;   //CAN消息基本结构  

u8 CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN初始化
 
u8 Can_Send_Msg(can_message_t *msg);						//发送数据

void Can_Receive_Msg(can_message_t *msg);							//接收数据

void send(void);

extern u8 cansend[1];

#endif
