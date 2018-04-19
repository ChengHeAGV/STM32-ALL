#include "sys.h"
#include "regex.h"
//将这些优先级分配给了UCOSIII的5个系统内部任务
//优先级0：中断服务服务管理任务 OS_IntQTask()
//优先级1：时钟节拍任务 OS_TickTask()
//优先级2：定时任务 OS_TmrTask()
//优先级OS_CFG_PRIO_MAX-2：统计任务 OS_StatTask()
//优先级OS_CFG_PRIO_MAX-1：空闲任务 OS_IdleTask()
//任务优先级
#define START_TASK_PRIO		3
//任务堆栈大小	
#define START_STK_SIZE 		512
//任务控制块
OS_TCB StartTaskTCB;
//任务堆栈	
CPU_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *p_arg);

//任务优先级
#define Transducer_TASK_PRIO		4
//任务堆栈大小	
#define Transducer_STK_SIZE 		512
//任务控制块
OS_TCB TransducerTaskTCB;
//任务堆栈	
CPU_STK Transducer_TASK_STK[Transducer_STK_SIZE];
void Transducer_task(void *p_arg);


//任务优先级
#define Auto_TASK_PRIO		5
//任务堆栈大小	
#define Auto_STK_SIZE 		512
//任务控制块
OS_TCB AutoTaskTCB;
//任务堆栈	
CPU_STK Auto_TASK_STK[Auto_STK_SIZE];
//任务函数
void Auto_task(void *p_arg);

//任务优先级
#define Manual_TASK_PRIO		6
//任务堆栈大小	
#define Manual_STK_SIZE 		512
//任务控制块
OS_TCB ManualTaskTCB;
//任务堆栈	
CPU_STK Manual_TASK_STK[Manual_STK_SIZE];
//任务函数
void Manual_task(void *p_arg);

//任务优先级
#define FLOAT_TASK_PRIO		7
//任务堆栈大小
#define FLOAT_STK_SIZE		512
//任务控制块
OS_TCB	FloatTaskTCB;
//任务堆栈
CPU_STK	FLOAT_TASK_STK[FLOAT_STK_SIZE];
//任务函数
void float_task(void *p_arg);

//任务优先级
#define DEMO_TASK_PRIO		8
//任务堆栈大小	
#define DEMO_STK_SIZE 		512
//任务控制块
OS_TCB DEMOTaskTCB;
//任务堆栈	
CPU_STK DEMO_TASK_STK[DEMO_STK_SIZE];
//任务函数
void DEMO_task(void *p_arg);

//任务优先级
#define Task5_TASK_PRIO		9
//任务堆栈大小	
#define Task5_STK_SIZE 		512
//任务控制块
OS_TCB Task5_TaskTCB;
//任务堆栈	
CPU_STK Task5_TASK_STK[Task5_STK_SIZE];
//任务函数
void Task5_task(void *p_arg);


//任务优先级
#define Control_TASK_PRIO		10
//任务堆栈大小	
#define Control_STK_SIZE 		512
//任务控制块
OS_TCB ControlTaskTCB;
//任务堆栈	
CPU_STK Control_TASK_STK[Control_STK_SIZE];
//任务函数
void Control_task(void *p_arg);


//任务优先级
#define WIFI_TASK_PRIO		11
//任务堆栈大小	
#define WIFI_STK_SIZE 		512
//任务控制块
OS_TCB WIFITaskTCB;
//任务堆栈	
CPU_STK WIFI_TASK_STK[WIFI_STK_SIZE];
//任务函数
void WIFI_task(void *p_arg);


//任务优先级
#define DEMO1_TASK_PRIO		13
//任务堆栈大小	
#define DEMO1_STK_SIZE 		512
//任务控制块
OS_TCB DEMO1TaskTCB;
//任务堆栈	
CPU_STK DEMO1_TASK_STK[DEMO1_STK_SIZE];
//任务函数
void DEMO1_task(void *p_arg);

//任务优先级
#define DEMO2_TASK_PRIO		12
//任务堆栈大小	
#define DEMO2_STK_SIZE 		512
//任务控制块
OS_TCB DEMO2TaskTCB;
//任务堆栈	
CPU_STK DEMO2_TASK_STK[DEMO2_STK_SIZE];
//任务函数
void DEMO2_task(void *p_arg);


//任务优先级
#define Screen_TASK_PRIO		14
//任务堆栈大小	
#define Screen_STK_SIZE 		512
//任务控制块
OS_TCB ScreenTaskTCB;
//任务堆栈	
CPU_STK Screen_TASK_STK[Screen_STK_SIZE];
//任务函数
void Screen_task(void *p_arg);


//任务优先级
#define PID_TASK_PRIO		15
//任务堆栈大小	
#define PID_STK_SIZE 		512
//任务控制块
OS_TCB PIDTaskTCB;
//任务堆栈	
CPU_STK PID_TASK_STK[PID_STK_SIZE];
//任务函数
void PID_task(void *p_arg);

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	
	delay_init(168);  	//时钟初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组配置
	LED_Init();         //LED初始化
	DMA_adc1_Init();
	DMA_Uart4_Init();
	DMA_Uart2_Init();
	DMA_Uart6_Init();
	DMA_Uart3_Init();
	ADC1_Configuration();
	USART1_Configuration(9600);
	USART4_Configuration(9600);
	USART6_Configuration(115200);
	USART2_Configuration(9600);
	USART3_Configuration(9600);
	TIM4_PWM_Init(1000-1,8-1);	//84M/8=10Mhz?????,????1000,??PWM??? 10M/50000=200hz. //500-10   20hz-1000hz
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);//CAN1初始化普通模式,波特率500Kbps
	CAN2_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);//CAN2初始化普通模式,波特率500Kbps
	PID_Init();
	TIM2_Int_Init(5000-1,840-1);			//Tout=((arr+1)*(psc+1))/Ft us.  50ms	
	TIM3_CH1_Cap_Init1(5000,84-1); 			//以84/84=1Mhz的频率计数 5ms捕获脉冲
 	TIM9_CH1_Cap_Init1(5000,84-1); 			//以84/84=1Mhz的频率计数 5ms捕获脉冲
	IWDG_Init(4,500);
	
	can_Sebuf[2]=0x55;//发送继电器板同步信息
	CanSend();	
	can_Sebuf[2]=0;
	
	MotoStop(5);

	OSInit(&err);		//初始化UCOSIII
	OS_CRITICAL_ENTER();//进入临界区
	//创建开始任务
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//任务控制块
				 (CPU_CHAR	* )"start task", 		//任务名字
                 (OS_TASK_PTR )start_task, 			//任务函数
                 (void		* )0,					//传递给任务函数的参数
                 (OS_PRIO	  )START_TASK_PRIO,     //任务优先级
                 (CPU_STK   * )&START_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//任务堆栈深度限位
                 (CPU_STK_SIZE)START_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,					//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* )&err);				//存放该函数错误时的返回值
	OS_CRITICAL_EXIT();	//退出临界区	 
	OSStart(&err);  //开启UCOSIII
	while(1);
}
//开始任务函数
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//统计任务                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();	
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	 //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	
	OS_CRITICAL_ENTER();	//进入临界区
	//创建Transducer任务
	OSTaskCreate((OS_TCB 	* )&TransducerTaskTCB,		
				 (CPU_CHAR	* )"Transducer task", 		
                 (OS_TASK_PTR )Transducer_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Transducer_TASK_PRIO,     
                 (CPU_STK   * )&Transducer_TASK_STK[0],	
                 (CPU_STK_SIZE)Transducer_STK_SIZE/10,	
                 (CPU_STK_SIZE)Transducer_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);								 
	
	//创建自动任务
	OSTaskCreate((OS_TCB 	* )&AutoTaskTCB,		
				 (CPU_CHAR	* )"Auto task", 		
                 (OS_TASK_PTR )Auto_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Auto_TASK_PRIO,     	
                 (CPU_STK   * )&Auto_TASK_STK[0],	
                 (CPU_STK_SIZE)Auto_STK_SIZE/10,	
                 (CPU_STK_SIZE)Auto_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);				 
				 
	//创建浮点测试任务
	OSTaskCreate((OS_TCB 	* )&FloatTaskTCB,		
				 (CPU_CHAR	* )"float test task", 		
                 (OS_TASK_PTR )float_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )FLOAT_TASK_PRIO,     	
                 (CPU_STK   * )&FLOAT_TASK_STK[0],	
                 (CPU_STK_SIZE)FLOAT_STK_SIZE/10,	
                 (CPU_STK_SIZE)FLOAT_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);	

	//创建触摸屏任务
	OSTaskCreate((OS_TCB 	* )&ScreenTaskTCB,		
				 (CPU_CHAR	* )"Screen task", 		
                 (OS_TASK_PTR )Screen_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Screen_TASK_PRIO,     	
                 (CPU_STK   * )&Screen_TASK_STK[0],	
                 (CPU_STK_SIZE)Screen_STK_SIZE/10,	
                 (CPU_STK_SIZE)Screen_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);	

	//PID
	OSTaskCreate((OS_TCB 	* )&PIDTaskTCB,		
				 (CPU_CHAR	* )"PID task", 		
                 (OS_TASK_PTR )PID_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )PID_TASK_PRIO,     	
                 (CPU_STK   * )&PID_TASK_STK[0],	
                 (CPU_STK_SIZE)PID_STK_SIZE/10,	
                 (CPU_STK_SIZE)PID_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
	//Control
	OSTaskCreate((OS_TCB 	* )&ControlTaskTCB,		
				 (CPU_CHAR	* )"Control task", 		
                 (OS_TASK_PTR )Control_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Control_TASK_PRIO,     	
                 (CPU_STK   * )&Control_TASK_STK[0],	
                 (CPU_STK_SIZE)Control_STK_SIZE/10,	
                 (CPU_STK_SIZE)Control_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
	//DEMO
	OSTaskCreate((OS_TCB 	* )&DEMOTaskTCB,		
				 (CPU_CHAR	* )"DEMO task", 		
                 (OS_TASK_PTR )DEMO_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )DEMO_TASK_PRIO,     	
                 (CPU_STK   * )&DEMO_TASK_STK[0],	
                 (CPU_STK_SIZE)DEMO_STK_SIZE/10,	
                 (CPU_STK_SIZE)DEMO_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);				 
	//DEMO1
	OSTaskCreate((OS_TCB 	* )&DEMO1TaskTCB,		
				 (CPU_CHAR	* )"DEMO1 task", 		
                 (OS_TASK_PTR )DEMO1_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )DEMO1_TASK_PRIO,     	
                 (CPU_STK   * )&DEMO1_TASK_STK[0],	
                 (CPU_STK_SIZE)DEMO1_STK_SIZE/10,	
                 (CPU_STK_SIZE)DEMO1_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);	
	//DEMO2
	OSTaskCreate((OS_TCB 	* )&DEMO2TaskTCB,		
				 (CPU_CHAR	* )"DEMO2 task", 		
                 (OS_TASK_PTR )DEMO2_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )DEMO2_TASK_PRIO,     	
                 (CPU_STK   * )&DEMO2_TASK_STK[0],	
                 (CPU_STK_SIZE)DEMO2_STK_SIZE/10,	
                 (CPU_STK_SIZE)DEMO2_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
				 
	//创建手动任务
	OSTaskCreate((OS_TCB 	* )&ManualTaskTCB,		
				 (CPU_CHAR	* )"Manual task", 		
				 (OS_TASK_PTR )Manual_task, 			
				 (void		* )0,					
				 (OS_PRIO	  )Manual_TASK_PRIO,     	
				 (CPU_STK   * )&Manual_TASK_STK[0],	
				 (CPU_STK_SIZE)Manual_STK_SIZE/10,	
				 (CPU_STK_SIZE)Manual_STK_SIZE,		
				 (OS_MSG_QTY  )0,					
				 (OS_TICK	  )0,					
				 (void   	* )0,				
				 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
				 (OS_ERR 	* )&err);
				 
	OSTaskCreate((OS_TCB 	* )&WIFITaskTCB,		
				 (CPU_CHAR	* )"WIFI task", 		
				 (OS_TASK_PTR )WIFI_task, 			
				 (void		* )0,					
				 (OS_PRIO	  )WIFI_TASK_PRIO,     	
				 (CPU_STK   * )&WIFI_TASK_STK[0],	
				 (CPU_STK_SIZE)WIFI_STK_SIZE/10,	
				 (CPU_STK_SIZE)WIFI_STK_SIZE,		
				 (OS_MSG_QTY  )0,					
				 (OS_TICK	  )0,					
				 (void   	* )0,				
				 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
				 (OS_ERR 	* )&err);	
							 
	OSTaskCreate((OS_TCB 	* )&Task5_TaskTCB,		
				 (CPU_CHAR	* )"Task5 task", 		
				 (OS_TASK_PTR )Task5_task, 			
				 (void		* )0,					
				 (OS_PRIO	  )Task5_TASK_PRIO,     	
				 (CPU_STK   * )&Task5_TASK_STK[0],	
				 (CPU_STK_SIZE)Task5_STK_SIZE/10,	
				 (CPU_STK_SIZE)Task5_STK_SIZE,		
				 (OS_MSG_QTY  )0,					
				 (OS_TICK	  )0,					
				 (void   	* )0,				
				 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
				 (OS_ERR 	* )&err);
				 
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//挂起开始任务			 
	OS_CRITICAL_EXIT();	//进入临界区
}
//手自动切换
void Transducer_task(void *p_arg)
{
	p_arg = p_arg;
	HmiScreenControlMode = 1;
	while(1)
	{	
		if(((SouZiDongQieHuan==0)&&(All_flag.flag_szd == 0))||(PLC_OutPut[18]==1))
		{
			All_flag.stopAsk= 1;
			All_flag.flag_tz = 1;
			All_flag.flag_szd = 1;			
			speek("手动");
			HmiShouZiDongYinCang = 0;			
			HmiScreenControlMode = 1;		
			while(SouZiDongQieHuan==0)
			{
				delay(0,0,0,10);
			}		
		}
		else if(((SouZiDongQieHuan==0)&&(All_flag.flag_szd == 1))||(PLC_OutPut[17]==1))
		{
			All_flag.stopAsk= 1;
			All_flag.flag_szd = 0;			
			speek("自动");
			HmiShouZiDongYinCang = 0;			
			speed.jisu_speed = ZiDongJiSu;	//自动一开始没扫到地标之前给个速度		
			HmiScreenControlMode = 0;		
			while(SouZiDongQieHuan==0)
			{
				delay(0,0,0,10);
			}
		}
		delay(0,0,0,5); //延时5ms
	}
}
//自动按钮相关
void Auto_task(void *p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		if(All_flag.flag_szd == 0)
		{
			if(All_flag.flag_qd==0)//防止多次软起
			{
				if((QD==0)||(HmiQiDong))
				{	
					All_flag.jiting_flag = 0;
					All_flag.flag_tz = 0;
					All_flag.startAsk = 1;	
					speek("启动");
				}
			}	
			
			if(All_flag.flag_qd==1)
			{
				if((TZ==0)||(HmiTinZhi))
				{
					All_flag.flag_tz = 1;
					All_flag.stopAsk=1;	
					speek("停止");					
				}
				if((QfangZ==0)&&(dir==0))
				{
					All_flag.flag_qd = 0;
					All_flag.jiting_flag = 1;
					All_flag.stopAsk=1;
					All_flag.speek1_flag=1;
				}
				if((HfangZ==0)&&(dir==1))
				{
					All_flag.flag_qd = 0;
					All_flag.jiting_flag = 1;
					All_flag.stopAsk=1;
					All_flag.speek3_flag=1;					
				}				
			}			
		}
		delay(0,0,0,5); //延时5ms
	}
}
//手动操作
void Manual_task(void *p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		if(All_flag.flag_szd==1)
		{
			if(All_flag.speek_flag==0)
			{
				if((QianJin==0))//前进
				{
					CanSend_data(1);					
					while(QianJin==0)
					{
						Motor_Zzhuan(1,SouDongSuDu);
						Motor_Zzhuan(2,SouDongSuDu);
						Motor_Zzhuan(3,SouDongSuDu);
						Motor_Zzhuan(4,SouDongSuDu);						
						delay(0,0,0,10);
					}	
					MotoStop(5);
		//			if((ZuoXuan==0))//左旋
		//			{
		//				Motor_Zzhuan(2,SouDongSuDu*1.5);
		//				Motor_Zzhuan(4,SouDongSuDu*1.5);
		//			}
		//			else if((YouXuan==0))//右旋
		//			{
		//				Motor_Zzhuan(1,SouDongSuDu*1.5);
		//				Motor_Zzhuan(3,SouDongSuDu*1.5);
		//			}			
				}
				else if((HouTui==0))//后退
				{
					CanSend_data(2);
					while(HouTui==0)
					{
						Motor_Fzhuan(1,SouDongSuDu);
						Motor_Fzhuan(2,SouDongSuDu);
						Motor_Fzhuan(3,SouDongSuDu);
						Motor_Fzhuan(4,SouDongSuDu);						
						delay(0,0,0,10);
					}
					MotoStop(5);
		//			if((ZuoXuan==0))//左旋
		//			{
		//				Motor_Zzhuan(2,SouDongSuDu*1.5);
		//				Motor_Zzhuan(4,SouDongSuDu*1.5);
		//			}
		//			else if((YouXuan==0))//右旋
		//			{
		//				Motor_Zzhuan(1,SouDongSuDu*1.5);
		//				Motor_Zzhuan(3,SouDongSuDu*1.5);
		//			}
				}
				else if((ZuoYi==0))//左移
				{
					CanSend_data(3);
					while(ZuoYi==0)
					{
						Motor_Fzhuan(1,SouDongSuDu);
						Motor_Zzhuan(2,SouDongSuDu);
						Motor_Zzhuan(3,SouDongSuDu);
						Motor_Fzhuan(4,SouDongSuDu);						
						delay(0,0,0,10);
					}
					MotoStop(5);
				}
				else if((YouYI==0))//右移
				{
					CanSend_data(4);
					while(YouYI==0)
					{
						Motor_Zzhuan(1,SouDongSuDu);
						Motor_Fzhuan(2,SouDongSuDu);
						Motor_Fzhuan(3,SouDongSuDu);
						Motor_Zzhuan(4,SouDongSuDu);						
						delay(0,0,0,10);
					}
					MotoStop(5);
				}
				else if((ZuoShang==0))//左上
				{
					CanSend_data(5);
					while(ZuoShang==0)
					{
						MotoStop(1);			
						Motor_Zzhuan(2,SouDongSuDu);
						Motor_Zzhuan(3,SouDongSuDu);
						MotoStop(4);						
						delay(0,0,0,10);
					}
					MotoStop(5);
				}
				else if((ZuoXia==0))//左下
				{
					CanSend_data(6);
					while(ZuoXia==0)
					{
						Motor_Fzhuan(1,SouDongSuDu);
						MotoStop(2);
						MotoStop(3);
						Motor_Fzhuan(4,SouDongSuDu);						
						delay(0,0,0,10);
					}
					MotoStop(5);			
				}
				else if((YouShang==0))//右上
				{
					CanSend_data(7);
					while(YouShang==0)
					{
						Motor_Zzhuan(1,SouDongSuDu);
						MotoStop(2);
						MotoStop(3);
						Motor_Zzhuan(4,SouDongSuDu);
						delay(0,0,0,10);
					}
					MotoStop(5);			
				}
				else if((YouXia==0))//右下
				{
					CanSend_data(8);
					while(YouXia==0)
					{
						MotoStop(1);
						Motor_Fzhuan(2,SouDongSuDu);
						Motor_Fzhuan(3,SouDongSuDu);
						MotoStop(4);						
						delay(0,0,0,10);
					}
					MotoStop(5);			
				}
				else if((ZuoXuan==0))//左旋
				{
					CanSend_data(9);
					while(ZuoXuan==0)
					{
						Motor_Fzhuan(1,SouDongSuDu);
						Motor_Zzhuan(2,SouDongSuDu);
						Motor_Fzhuan(3,SouDongSuDu);
						Motor_Zzhuan(4,SouDongSuDu);						
						delay(0,0,0,10);
					}	
					MotoStop(5);			
				}
				else if((YouXuan==0))//右旋
				{
					CanSend_data(10);
					while(YouXuan==0)
					{
						Motor_Zzhuan(1,SouDongSuDu);
						Motor_Fzhuan(2,SouDongSuDu);
						Motor_Zzhuan(3,SouDongSuDu);
						Motor_Fzhuan(4,SouDongSuDu);						
						delay(0,0,0,10);
					}
					MotoStop(5);
				}			
			}		
		
		}
		delay(0,0,0,10); //延时10ms	
	}
}
//电机PID调节
u8 cy_time=5;
void PID_task(void *p_arg)
{
	while(1)
	{
		if((All_flag.flag_qd==1)&&(car_statu == 1)&&(All_flag.flag_szd==0))
		{	
			PID_Adjust(speed.jisu_speed,PID.Kp,PID.Ki,PID.Kd);
		}
		delay(0,0,0,cy_time);
	}
}
//蜂鸣器、电池电量告警、与参数下位机通讯
void float_task(void *p_arg)
{
	u8 num=0;
	u16 num_beep=0;
	UserConfigInit();
	p_arg = p_arg;
	All_flag.yuyin_flag=YinLiang;	
	BEEP=1;
	delay(0,0,0,500);
	BEEP=0;
	while(1)
	{
		cy_time = PIDZhouQi;
		PID.Kp = SPID_P/10.0;
		PID.Ki = SPID_I/1000.0;
		PID.Kd = SPID_D/10.0;	
		if(All_flag.beep_flag)
		{
			BEEP=1;
			num_beep++;
			if(num_beep==40)
			{
				num_beep = 0;
				BEEP=0;
				All_flag.beep_flag = 0;				
			}
		}
		if(All_flag.yuyin_flag!=YinLiang)
		{
			yinling(YinLiang);		
		}
		All_flag.yuyin_flag = YinLiang;
		num++;
		if(num==200)
		{
			LED1 = ~LED1;//运行灯
			TongXunDeng=~TongXunDeng;//触摸屏通讯指示灯
			LiDian_send();//获取电池数据
			num=0;
		}
		QianFangZhuang = QfangZ;//前防撞
		HouFangZhuang = HfangZ;//后防撞
		if(QfangZ ==1)	All_flag.speek1_flag=0;
		if(HfangZ ==1)	All_flag.speek3_flag=0;	
		
		if(JieMianHao==5)
		{
			//动态刷新手动自动和时间按钮的显示或隐藏
			//正向、反向、左移正向、左移反向、右移正向、右移反向
			if(PLC_Data[4]==0||PLC_Data[4]==3||PLC_Data[4]==4||PLC_Data[4]==5||PLC_Data[4]==7||PLC_Data[4]==8
				||PLC_Data[4]==10||PLC_Data[4]==11||PLC_Data[4]==12||PLC_Data[4]==13)
			{
				if(PLC_Data[4]==10||PLC_Data[4]==11||PLC_Data[4]==12||PLC_Data[4]==13)
				{
					PLC_OutPut[23]=1;
				}
				else
				{
					PLC_OutPut[23]=0;
				}
				PLC_OutPut[0]=1;//显示手动自动
				if(PLC_Data[5]==0)//自动
					PLC_OutPut[1]=1;//显示停留时间
				else
					PLC_OutPut[1]=0;//隐藏停留时间
			}
			else
			{
				PLC_OutPut[0]=0;//隐藏手动自动
				PLC_OutPut[1]=0;//隐藏停留时间
				PLC_OutPut[23]=0;//隐藏突变次数
			}
		}
		if(receive_ok == 1)
		{
			data_Parameterreceive();
			DMA_Cmd(DMA2_Stream1, ENABLE);
		}		
		if(lidian.MAh<1635)//满容量8179，小于满容量的20%报警
		{
			All_flag.speek2_flag=1;			
		}
		else
		{
			All_flag.speek2_flag=0;
		}
		delay(0,0,0,5); //延时5ms
	}
}
 //触摸屏上路径流程参数设置
void Screen_task(void*p_arg)
{
    OS_ERR err ;
    u16 i=0,j=0 ;   
    //用户参数初始化
    JieMianHao=22 ;
    
    while(1)
    {
        switch(JieMianHao)
        {
            case 0 :
            break ;
			case 2 :
            break ;
            case ZiDongMoShiJieMian :
				while(JieMianHao==ZiDongMoShiJieMian)
				{
					osdelay_ms(10);
				}				
            break ;
            case 4 :
            break ;
			//路径规划界面
            case LuJingGuiHuaJieMian :
            {			
				while(JieMianHao==LuJingGuiHuaJieMian||JieMianHao==QueDingChaRuLuJingJieMian||JieMianHao==QueDingShanChuLuJingJieMian
					||JieMianHao==FuZhiLuJingTanChuJieMian)
				{  
					//复制路径
					while(JieMianHao==FuZhiLuJingTanChuJieMian)//处于复制路径界面
					{
						//被复制路径号为零时置1
						if(HmiRouteCopiedNum==0)
							HmiRouteCopiedNum=1;	
						if(HmiRouteCopiedNum>RouteNum)	
						{
							HmiRouteCopiedNum =1;
						}
						
						//输入的被复制路径号变化时更新
						if(HmiRouteCopiedNumTemp!=HmiRouteCopiedNum)
							HmiRouteCopiedCount = GetRouteStationNum(HmiRouteCopiedNum);

						
						
						//确定复制
						if(HmiRoutemode==1)
						{
							//读取被复制信息到当前
							GetRouteData(HmiRouteCopiedNum);
							
							//保存并更新被复制信息
							SetRouteData(HmiRouteNum);	
							
							UpdataStationToHmi();
							
							//设置当前站点为1
							if(HmiStationNum!=0)
								HmiStationSerialNum = 1;
							
							//退出复制模式
							HmiRoutemode=0;
						}
						osdelay_ms(10);
					}

					//添加站点
					if(HmiRoutemode==2)
					{ 
						//站点数加一
						HmiStationNum ++;
						//站点号等于站点数
						HmiStationSerialNum = HmiStationNum;
						
						//地标号清零
						keynumber = 0;		
						
						ClearStationToHmi();	
						
						while(HmiRoutemode==2)
						{
							//如果读到地标，更新到显示器
							if(keynumber!=0)
							{
								HmiRfidNum = keynumber;//刷新地标号
								keynumber = 0;
							}										
							//确定
							if(HmiRouteEnter==1)
							{
								HmiRouteEnter = 0;
								//更新站点数据到当前数据
								UpdataStationToNow();

								//保存站点信息
								SetStationData(HmiRouteNum,HmiStationSerialNum-1);
								//退出添加模式
								HmiRoutemode = 0;
							}
							else
							//取消
							if(HmiRouteEnter==2)
							{
								HmiRouteEnter = 0;
								//站点数减一
								HmiStationNum--;
								//站点号等于站点数
								HmiStationSerialNum = HmiStationNum;
								//退出添加模式
								HmiRoutemode = 0;
							}
							osdelay_ms(10);
						}
					}
					//插入站点
					if(HmiRoutemode==3)
					{
						//站点数加一
						HmiStationNum ++;
						//站点号为零时加一
						if(HmiStationNum==0)
							HmiStationSerialNum = 1;
						
						//地标号清零
						keynumber = 0;		
						
						ClearStationToHmi();										

						while(HmiRoutemode==3)
						{
							//如果读到地标，更新到显示器
							if(keynumber!=0)
							{
								HmiRfidNum = keynumber;//刷新地标号
								keynumber = 0;
							}												
							
							//确定
							if(HmiRouteEnter==1)
							{
								HmiRouteEnter = 0;
								
								//站点信息向后移动一个位置，并插入当前站点信息
								for(i=HmiStationNum;i>=HmiStationSerialNum;i--)
								{
									for(j=0;j<StaiionInfor;j++)
									{
										NowRouteInfor[i][j] = NowRouteInfor[i-1][j];
									}
								}
								
								//更新站点信息到当前
								UpdataStationToNow();
								
								//保存路径信息
								SetRouteData(HmiRouteNum);

								//退出添加模式
								HmiRoutemode=	0;
							}
							else
							//取消
							if(HmiRouteEnter==2)
							{
								HmiRouteEnter = 0;
								//站点数减一
								HmiStationNum--;
								//站点号为1时置零
								if(HmiStationSerialNum==1)
									HmiStationSerialNum = 0;
								//退出添加模式
								HmiRoutemode=	0;
							}

							osdelay_ms(10);
						}

					}
					//更改站点
					if(HmiRoutemode==4)
					{
						keynumber = 0;
						while(HmiRoutemode==4)
						{
							//如果读到地标，更新到显示器
							if(keynumber!=0)
							{
								HmiRfidNum = keynumber;//刷新地标号
								keynumber = 0;
							}			
							
							//确定
							if(HmiRouteEnter==1)
							{
								HmiRouteEnter = 0;
								//更新站点数据到当前数据
								UpdataStationToNow();
								//保存当前站点数据
								SetRouteData(HmiRouteNum);
								//退出添加模式
								HmiRoutemode = 0;
							}
							else
							//取消
							if(HmiRouteEnter==2)
							{
								HmiRouteEnter = 0;
								//更新到界面
								UpdataStationToHmi();
								//退出添加模式
								HmiRoutemode=	0;
							}
							osdelay_ms(10);
						}
					}
				
					//删除站点
					if(HmiRoutemode==5)
					{
						if(HmiStationNum>0)
						{
							//将后面所数据向前移动一位
							if((HmiStationNum>0)&&((HmiStationNum)!=HmiStationSerialNum))
							{
								//站点信息向前移动一个位置
								for(i=HmiStationSerialNum;i<HmiStationNum;i++)
								{
									for(j=0;j<StaiionInfor;j++)
									{
										NowRouteInfor[i-1][j] = NowRouteInfor[i][j];
									}
								}
							}

							HmiStationNum--;
							if(HmiStationNum==0)
								HmiStationSerialNum = 0;
							else if((HmiStationNum+1 )== HmiStationSerialNum)
								HmiStationSerialNum--;
							//保存路径信息
							SetRouteData(HmiRouteNum);
							
							//更新界面
							UpdataStationToHmi();
						}	
						HmiRoutemode = 0;
					}
					
					//查询站点
					if(HmiRoutemode==0)
					{
						//当路径站点数大于0，并且序号为0时，设置序号为1，并更新显示内容
						if((HmiStationNum>0)&&(HmiStationSerialNum==0))
						{
							HmiStationSerialNum = 1;
							//更新到界面
							UpdataStationToHmi();
						}
						else
						if(HmiStationNum==0)
						{
							HmiStationSerialNum = 0;
						}
						
						//路径号变化时，更新界面
						if(HmiRouteNumFlag != HmiRouteNum)
						{
							HmiRouteNumFlag = HmiRouteNum;
							//获取路径信息
							GetRouteData(HmiRouteNum);
							
							if(HmiStationNum>0)
								HmiStationSerialNum = 1;
							//更新到界面
							UpdataStationToHmi();
							
						}
						
						//上一个
						if(HmiStationLast == 1)
						{
							HmiStationLast = 0;
							if(HmiStationSerialNum>1)
								HmiStationSerialNum--;
							else
								HmiStationSerialNum = HmiStationNum;
						}
						//下一个
						if(HmiStationNext == 2)
						{
							HmiStationNext = 0;
							if(HmiStationSerialNum<HmiStationNum)
									HmiStationSerialNum++;
								else
									if(HmiStationSerialNum!=0)
										HmiStationSerialNum = 1;
						}
						
						if(HmiStationNum==0)		//没有站点
						{
							//清除站点信息
							ClearStationToHmi();
						}
						else
						{
							//更新站点信息
							UpdataStationToHmi();
						}
					}
					osdelay_ms(10);
				}
			}
            break ;
			case 7 :
            case 6 :
			//调试界面设置
			case 8:
				while(JieMianHao==8)
				{		
					 SystemParameter[19] = PIDZhouQi;
					 SystemParameter[20] = SPID_P;
					 SystemParameter[21] = SPID_I ;
					 SystemParameter[22] = SPID_D;
					 SystemParameter[23] = QianHouJuLi;
					 SystemParameter[15] = ZiDongJiSu;
					 delay(0,0,0,10);					
				}			
				//存储所有系统参数
				SetAllParameterToSystem();
			break;
			case 9 :
            //参数设置
            //
            while(JieMianHao==9)
            {				                            
				SystemParameter[9] = PLC_Data[22];//慢速
				SystemParameter[10] = PLC_Data[23];//中速
				SystemParameter[11] = PLC_Data[24];//快速
				SystemParameter[14] = SouDongSuDu;
				SystemParameter[15] = ZiDongJiSu;
				SystemParameter[16] = SouDongBiZhang;
				SystemParameter[17] = YuYinKaiGuan;
				SystemParameter[18] = YinLiang;
				SystemParameter[98] = LiuChengZongShu;
				SystemParameter[99] = LuJingZongShu;
				SystemParameter[25]	= CheHao;	
                delay(0,0,0,10);
            }
            //循环结束，保存参数
			//Your Save Code！
			//存储所有系统参数
			SetAllParameterToSystem();			
            break ;
			//流程设置
			case LiuChengGuiHuaJieMian:
				{
						while(JieMianHao==LiuChengGuiHuaJieMian||JieMianHao==FuZhiLiuChengTanChuJieMian||JieMianHao==QueDingChaRuLiuChengJieMian
							||JieMianHao==QueDingShanChuLiuChengJieMian)
						{ 
							//查看模式
							if(HmiProcessMode==0)
							{
								//当前流程步数大于0，并且界面序号为0时，设置序号为1，并更新显示内容
								if((HmiStepNum>0)&&(HmiProcessSerialNum==0))
								{
									HmiProcessSerialNum = 1;
									GetProcessData();
								}
								else
								if(HmiStepNum==0)
								{
									HmiProcessSerialNum = 0;
									HmiProcessStartNum = 1;
									HmiProcessStopNum = 0;
									HmiProcessAction = 0;
								}
								
								//流程号变化时，更新界面
								if(HmiProcessNumFlag != HmiProcessNum)
								{
									HmiProcessNumFlag = HmiProcessNum;
									GetProcessData();
								}
								
								if(HmiProcessLast==1)//上一个
								{
									HmiProcessLast = 0;
									if(HmiProcessSerialNum>1)
										HmiProcessSerialNum--;
									else
										HmiProcessSerialNum = HmiStepNum;
								}
								else
									if(HmiProcessNext==2)//下一个
									{
										HmiProcessNext = 0;
										if(HmiProcessSerialNum<HmiStepNum)
											HmiProcessSerialNum++;
										else
											if(HmiProcessSerialNum!=0)
												HmiProcessSerialNum = 1;
									}
								if(HmiStepNum==0)
								{
									ClearStepToHmi();
								}
								else
								{
									UpdataProcessToHmi();
								}								
							}									
							//复制流程
							if(JieMianHao==FuZhiLiuChengTanChuJieMian)
							{
								while(JieMianHao==FuZhiLiuChengTanChuJieMian)
								{
									//被复制流程号为零时置1
									if(HmiProcessCopiedNum==0)
										HmiProcessCopiedNum=1;	
									//输入的被复制流程号变化时更新
									if(HmiProcessCopiedNumTemp!=HmiProcessCopiedNum)
										HmiProcessCopiedCount = GetProcessStepNum(HmiProcessCopiedNum);
									if(HmiProcessCopiedNum>ProcessNum)
									{
										HmiProcessCopiedNum = 1;
									}
									//确定复制
									if(HmiProcessMode==1)
									{
										//读取被复制信息到当前
										GetProcessDataFrom(HmiProcessCopiedNum);
										//保存被复制信息
										SetProcessData();	
										
										//设置当前序号为1
										if(HmiStepNum!=0)
											HmiProcessSerialNum = 1;
									
										//退出复制模式
										HmiProcessMode = 0;
									}
									osdelay_ms(10);
								}
							}
							//添加流程
							if(HmiProcessMode==2)
							{
								//流程步数加一
								HmiStepNum++;
								//序号等于流程数
								HmiProcessSerialNum = HmiStepNum;
								
								//起始路径号默认为0则置1
								if(HmiProcessStartNum==0)
									HmiProcessStartNum = 1;
								
								ClearStepToHmi();
								
								while(HmiProcessMode==2)
								{
									switch(HmiProcessAction)
									{
										case 0://单次执行
											break;
										case 1://顺序执行到
											if(HmiProcessStopNum<=HmiProcessStartNum)
											{
												if(HmiProcessStartNum==ProcessNum)
													HmiProcessStopNum=HmiProcessStartNum;
												else
													HmiProcessStopNum=HmiProcessStartNum+1;
											}
											break;
										case 2://倒序执行
											if(HmiProcessStopNum>=HmiProcessStartNum)
											{
												if(HmiProcessStartNum==1)
													HmiProcessStopNum=HmiProcessStartNum;
												else
													HmiProcessStopNum=HmiProcessStartNum-1;
											}
											break;
										case 3://循环执行
											if(HmiProcessStopNum==0)
											{
													HmiProcessStopNum=1;
											}
											break;
										default:break;
									}
									
									//确定
									if(HmiProcessEnter==1)
									{
										HmiProcessEnter = 0;
										//保存并更新数据
										SetProcessData();
										
										//退出添加模式
										HmiProcessMode = 0;
									}
									//取消
									else if(HmiProcessEnter==2) 
									{
										HmiProcessEnter = 0;
										
										//流程步数减一
										HmiStepNum--;
										//序号等于流程数
										HmiProcessSerialNum = HmiStepNum;
										
										//退出添加模式
										HmiProcessMode = 0;
									}
									osdelay_ms(10);
								}
							}
							
							//插入流程
							if(HmiProcessMode==3)
							{
								//流程步数加一
								HmiStepNum++;
								//序号为零时加一
								if(HmiProcessSerialNum==0)
									HmiProcessSerialNum = 1;
								
								//起始路径号默认为0则置1
								if(HmiProcessStartNum==0)
									HmiProcessStartNum = 1;
								
								ClearStepToHmi();
								
								while(HmiProcessMode==3)
								{
									switch(HmiProcessAction)
									{
										case 0://单次执行
											break;
										case 1://顺序执行到
											if(HmiProcessStopNum<=HmiProcessStartNum)
											{
												if(HmiProcessStartNum==ProcessNum)
													HmiProcessStopNum=HmiProcessStartNum;
												else
													HmiProcessStopNum=HmiProcessStartNum+1;
											}
											break;
										case 2://倒序执行
											if(HmiProcessStopNum>=HmiProcessStartNum)
											{
												if(HmiProcessStartNum==1)
													HmiProcessStopNum=HmiProcessStartNum;
												else
													HmiProcessStopNum=HmiProcessStartNum-1;
											}
											break;
										case 3://循环执行
											if(HmiProcessStopNum==0)
											{
													HmiProcessStopNum=1;
											}
											break;
										default:break;
									}
									
									//确定
									if(HmiProcessEnter==1)
									{
										HmiProcessEnter = 0;
										
										//保存并更新数据
										InsertProcessData();
										
										//退出插入模式
										HmiProcessMode = 0;
									}
									//取消
									else if(HmiProcessEnter==2) 
									{
										HmiProcessEnter = 0;
										
										//流程步数减一
										HmiStepNum--;
										//序号为1时减一
										if(HmiProcessSerialNum==1)
											HmiProcessSerialNum = 0;
										
										//退出添加模式
										HmiProcessMode = 0;
									}
									osdelay_ms(10);
								}
							}									
							//更改流程
							if(HmiProcessMode==4)
							{
								while(HmiProcessMode==4)
								{
									switch(HmiProcessAction)
									{
										case 0://单次执行
											break;
										case 1://顺序执行到
											if(HmiProcessStopNum<=HmiProcessStartNum)
											{
												if(HmiProcessStartNum==ProcessNum)
													HmiProcessStopNum=HmiProcessStartNum;
												else
													HmiProcessStopNum=HmiProcessStartNum+1;
											}
											break;
										case 2://倒序执行
											if(HmiProcessStopNum>=HmiProcessStartNum)
											{
												if(HmiProcessStartNum==1)
													HmiProcessStopNum=HmiProcessStartNum;
												else
													HmiProcessStopNum=HmiProcessStartNum-1;
											}
											break;
										case 3://循环执行
											if(HmiProcessStopNum==0)
											{
													HmiProcessStopNum=1;
											}
											break;
										default:break;
									}
									
									//确定
									if(HmiProcessEnter==1)
									{
										HmiProcessEnter = 0;
										//保存并更新数据
										SetProcessData();
										
										//退出更改模式
										HmiProcessMode = 0;
									}
									//取消
									else if(HmiProcessEnter==2) 
									{
										HmiProcessEnter = 0;

										//退出添加模式
										HmiProcessMode = 0;
									}
									osdelay_ms(10);
								}
							}									
							//删除流程
							if(HmiProcessMode==5)
							{
								DeleteProcessData();
								//退出删除模式
								HmiProcessMode = 0;
							}
							osdelay_ms(10);
						}
				}
			break;
			//取消任务
			case QuXiaoRenWuJieMian: 
			{		
				while(JieMianHao==QuXiaoRenWuJieMian)
				{
					if(QuXiaoRenWuQueDing==1)
					{
						QuXiaoRenWuQueDing = 0;
						All_flag.quxiaorenwu_flag = 1;
						HmiTask = 0;
						HmiTaskState = 0;
						//停车
						All_flag.stopAsk = 1;
						dir = 0;
						All_flag.speek_flag = 0;
						All_flag.speek1_flag = 0;
						All_flag.speek3_flag = 0;
						//删除任务
						OSTaskDel((OS_TCB*)&Task5_TaskTCB,&err);
						//重新创建任务
						OSTaskCreate((OS_TCB 	* )&Task5_TaskTCB,		
						(CPU_CHAR	* )"Task5 task", 		
									 (OS_TASK_PTR )Task5_task, 			
									 (void		* )0,					
									 (OS_PRIO	  )Task5_TASK_PRIO,     	
									 (CPU_STK   * )&Task5_TASK_STK[0],	
									 (CPU_STK_SIZE)Task5_STK_SIZE/10,	
									 (CPU_STK_SIZE)Task5_STK_SIZE,		
									 (OS_MSG_QTY  )0,					
									 (OS_TICK	  )0,					
									 (void   	* )0,				
									 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
									 (OS_ERR 	* )&err);
					}
					osdelay_ms(10);
				}							
			}
			break;
			case LiuChengSheZhiJieMian: 
				{		
					//如果路径号为零，则置一
					if(HmiProcessNum==0)
					{
						HmiProcessNum = 1;
					}
				}
			break;
			case LuJingSheZhiJieMian: 
				{		
					//如果路径号为零，则置一
					if(HmiRouteNum==0)
					{
						HmiRouteNum = 1;
					}
				}
			break;
			//执行路径
			case ZhiXingLuJingJieMian:
				{		
					while(JieMianHao==ZhiXingLuJingJieMian)
					{
						if(ZhiXingLuJingQueDing==1)
						{
							//保存路径号
							SetOneParameterToSystem(HmiRouteNum,6);
							HmiTask = 1;
							SystemParameter[8] = HmiTask;
							//保存任务号
							SetOneParameterToSystem(HmiTask,8);
							ZhiXingLuJingQueDing = 0;
							
							//自动界面显示信息重载
							HmiAutoReload();
						}
						osdelay_ms(10);
					}
				}
			break;
			//执行流程
			case ZhiXingLiuChengJieMian: 
			{		
				while(JieMianHao==ZhiXingLiuChengJieMian)
				{
					if(ZhiXingLiuChengQueDing==1)
					{
						//保存流程号
						SetOneParameterToSystem(HmiProcessNum,7);
						HmiTask = 2;
						SystemParameter[8] = HmiTask;
						//保存任务号
						SetOneParameterToSystem(HmiTask,8);
						ZhiXingLiuChengQueDing = 0;
						
						//任务状态为正在运行
						HmiTaskState = 5;
						
						//自动界面显示信息重载
						HmiAutoReload();
					}
					osdelay_ms(10);
				}							
			}
			break;				
            default :
            break ;
        }
        delay(0,0,0,10);
    }
}
//自动执行路径或流程
void Task5_task(void *p_arg)
{	
	u16 i,j,k;
	p_arg = p_arg;

	while(1)
	{
		if(All_flag.flag_szd == 0)
		{
			//执行路径
			if(HmiTask==1)
			{
				////清空地标
				dir=0;
				keynumber=0;
				All_flag.quxiaorenwu_flag = 0;
				HmiStationSerialNum = 0;
				//根据所选路径，执行相应动作
				for(i=0;i<HmiStationNum;i++)
				{
					StationAction(i);
				}
			}
			else
				//执行流程
				if(HmiTask == 2)
				{
					////清空地标
					dir=0;
					keynumber=0;
					All_flag.quxiaorenwu_flag = 0;
					HmiProcessSerialNum = 0;
					for(i=0;i<HmiStepNum;i++)
					{
						HmiProcessSerialNum++;
						switch(NowProcessInfor[i][1])
						{
							case 0://单次执行
								//更新路径号
								HmiRouteNum = NowProcessInfor[i][0];
							  //获取路径包含站点数
								GetRouteStationNum(HmiRouteNum);
								//获取当前路径信息
								GetRouteData(HmiRouteNum);

								HmiStationSerialNum = 0;
								//根据所选路径，执行相应动作
								for(j=0;j<HmiStationNum;j++)
								{
									StationAction(j);
								}
								break;
							case 1://顺序执行
								for(k=NowProcessInfor[i][0];k<=NowProcessInfor[i][2];k++)
								{
									//更新路径号
									HmiRouteNum = k;
									//获取路径包含站点数
									GetRouteStationNum(HmiRouteNum);
									//获取当前路径信息
									GetRouteData(HmiRouteNum);
									
									HmiStationSerialNum = 0;
									//根据所选路径，执行相应动作
									for(j=0;j<HmiStationNum;j++)
									{
										StationAction(j);
									}
								}
								break;
							case 2://倒序执行
								for(k=NowProcessInfor[i][0];k>=NowProcessInfor[i][2];k--)
								{
									//更新路径号
									HmiRouteNum = k;
									//获取路径包含站点数
									GetRouteStationNum(HmiRouteNum);
									//获取当前路径信息
									GetRouteData(HmiRouteNum);
  
									HmiStationSerialNum = 0;
 									//根据所选路径，执行相应动作
									for(j=0;j<HmiStationNum;j++)
									{
										StationAction(j);
									}
								}
								break;
							case 3://循环执行
								//更新路径号
								HmiRouteNum = NowProcessInfor[i][0];
							  //获取路径包含站点数
								GetRouteStationNum(HmiRouteNum);
								//获取当前路径信息
								GetRouteData(HmiRouteNum);
								for(k=0;k<NowProcessInfor[i][2];k++)
								{
									HmiStationSerialNum = 0;
									//根据所选路径，执行相应动作
									for(j=0;j<HmiStationNum;j++)
									{
										StationAction(j);
									}
								}
								break;
							default:break;
						}
					}
				}		
		}
		delay(0,0,0,5);
	}
}

//手自动模式避障处理
void Control_task(void *p_arg)
{
	u8 num=0;
	while(1)
	{
		num++;
		if(num==100)
		{
			LED3 = ~LED3;//运行灯
			num=0;
		}
		ld_juli = QianHouJuLi;//前后倒车雷达距离设置
		Manual_juli = QianHouJuLi;
		if(All_flag.flag_szd==0)//自动
		{
			if(Jhwai_switch&&(All_flag.flag_qd==1))
			{				
				if(dir==0)//正方向
				{
					if(((QianZuoLeiDa<=ld_juli)||(QianYouLeiDa<=ld_juli)))
					{
						All_flag.speek_flag = 1;
						HmiTaskState = 2;
						MotoStop(5);
					}
					else if(((QianZuoLeiDa>ld_juli)&&(QianYouLeiDa>ld_juli)))
					{						
						All_flag.speek_flag = 0;
						HmiTaskState = 5;
						delay(0,0,1,0);
						All_flag.startAsk = 1;		
					}
				}
				else if(dir == 1)//后退
				{
					if(((HouZuoLeiDa<=ld_juli)||(HouYouLeiDa<=ld_juli)))
					{
						All_flag.speek_flag = 1;						
						HmiTaskState = 2;
						MotoStop(5);
					}
					else if(((HouZuoLeiDa>ld_juli)&&(HouYouLeiDa>ld_juli)))
					{					
						All_flag.speek_flag = 0;
						HmiTaskState = 5;
						delay(0,0,1,0);
						All_flag.startAsk = 1;					
					}
				}
				else if(dir == 2)//左移
				{
					if(((ZuoQianLeiDa<=ld_juli)||(ZuoHouLeiDa<=ld_juli)))
					{
						All_flag.speek_flag = 1;						
						HmiTaskState = 2;
						MotoStop(5);
					}
					else if(((ZuoQianLeiDa>ld_juli)&&(ZuoHouLeiDa>ld_juli)))
					{
						All_flag.speek_flag = 0;						
						HmiTaskState = 5;
						delay(0,0,1,0);
						All_flag.startAsk = 1;				
					}
				}
				else if(dir == 3)//右移
				{
					if(((YouQianLeiDa<=ld_juli)||(YouHouLeiDa<=ld_juli)))
					{
						All_flag.speek_flag = 1;						
						HmiTaskState = 2;
						MotoStop(5);
					}
					else if(((YouQianLeiDa>ld_juli)&&(YouHouLeiDa>ld_juli)))
					{						
						All_flag.speek_flag = 0;
						HmiTaskState = 5;
						delay(0,0,1,0);
						All_flag.startAsk = 1;					
					}
				}
				else if(dir == 4)//左旋
				{
					if(((YouHouLeiDa<=ld_juli)||(ZuoQianLeiDa<=ld_juli)))
					{
						All_flag.speek_flag = 1;						
						HmiTaskState = 2;
						MotoStop(5);
					}
					else if(((YouHouLeiDa>ld_juli)&&(ZuoQianLeiDa>ld_juli)))
					{					
						All_flag.speek_flag = 0;
						HmiTaskState = 5;
						delay(0,0,1,0);
						All_flag.startAsk = 1;					
					}
				}
				else if(dir == 5)//右旋
				{
					if(((YouQianLeiDa<=ld_juli)||(ZuoHouLeiDa<=ld_juli)))
					{
						All_flag.speek_flag = 1;						
						HmiTaskState = 2;
						MotoStop(5);
					}
					else if(((YouQianLeiDa>ld_juli)&&(ZuoHouLeiDa>ld_juli)))
					{					
						All_flag.speek_flag = 0;
						HmiTaskState = 5;
						delay(0,0,1,0);
						All_flag.startAsk = 1;					
					}
				}				
			}			
		}
		else
		{
			if(SouDongBiZhang)
			{
				while(QianJin==0)
				{
					if((QianZuoLeiDa<Manual_juli)||(QianYouLeiDa<Manual_juli)||(QfangZ==0))
					{
						All_flag.speek_flag = 1;					
						MotoStop(5);							
					}
					else if((QianZuoLeiDa>Manual_juli)&&(QianYouLeiDa>Manual_juli)&&(QfangZ==1))
					{
						All_flag.speek_flag = 0;
					}
					delay(0,0,0,5);				
				}			
				
				while(HouTui==0)//后退
				{
					if((HouZuoLeiDa<Manual_juli)||(HouYouLeiDa<Manual_juli)||(HfangZ==0))
					{
						All_flag.speek_flag = 1;						
						MotoStop(5);										
					}	
					else if((HouZuoLeiDa>Manual_juli)&&(HouYouLeiDa>Manual_juli)&&(HfangZ==1))
					{
						All_flag.speek_flag = 0;
					}	
					delay(0,0,0,5);				
				}			
				while(ZuoYi==0)//左移
				{
					if(((ZuoQianLeiDa<Manual_juli)||(ZuoHouLeiDa<Manual_juli)))
					{
						All_flag.speek_flag = 1;						
						MotoStop(5);
					
					}	
					else if(((ZuoQianLeiDa>Manual_juli)&&(ZuoHouLeiDa>Manual_juli)))
					{
						All_flag.speek_flag = 0;
					}
					delay(0,0,0,5);				
				}
				while(YouYI==0)//右移
				{
					if(((YouQianLeiDa<Manual_juli)||(YouHouLeiDa<Manual_juli)))
					{
						All_flag.speek_flag = 1;						
						MotoStop(5);
						
					}	
					else if(((YouQianLeiDa>Manual_juli)&&(YouHouLeiDa>Manual_juli)))
					{
						All_flag.speek_flag = 0;
					}
					delay(0,0,0,5);				
				}
				while(ZuoXuan==0)//左旋
				{
					if(( (ZuoQianLeiDa<Manual_juli)||(YouHouLeiDa<Manual_juli)))
					{
						All_flag.speek_flag = 1;						
						MotoStop(5);
						
					}
					else if(((YouHouLeiDa>Manual_juli)&&(ZuoQianLeiDa>Manual_juli)))
					{
						All_flag.speek_flag = 0;
					}
					delay(0,0,0,5);				
				}
				while(YouXuan==0)//右旋
				{
					if(((YouQianLeiDa<Manual_juli)||(ZuoHouLeiDa<Manual_juli) ))
					{
						All_flag.speek_flag = 1;						
						MotoStop(5);
						
					}	
					else if(((YouQianLeiDa>Manual_juli)&&(ZuoHouLeiDa>Manual_juli)))
					{
						All_flag.speek_flag = 0;
					}
					delay(0,0,0,5);				
				}
				while(ZuoShang==0)//左上
				{
					if(((QianZuoLeiDa<Manual_juli)||(QianYouLeiDa<Manual_juli)||(ZuoQianLeiDa<Manual_juli)||(ZuoHouLeiDa<Manual_juli)))
					{
						All_flag.speek_flag = 1;						
						MotoStop(5);
						
					}
					else if(((QianZuoLeiDa>Manual_juli)&&(QianYouLeiDa>Manual_juli)&&(ZuoQianLeiDa>Manual_juli)&&(ZuoHouLeiDa>Manual_juli)))
					{
						All_flag.speek_flag = 0;
					}	
					delay(0,0,0,5);				
				}
				while(ZuoXia==0)//左下
				{
					if(((HouZuoLeiDa<Manual_juli)||(HouYouLeiDa<Manual_juli)||(ZuoQianLeiDa<Manual_juli)||(ZuoHouLeiDa<Manual_juli)))
					{
						All_flag.speek_flag = 1;						
						MotoStop(5);
						
					}	
					else if(((HouZuoLeiDa>Manual_juli)&&(HouYouLeiDa>Manual_juli)&&(ZuoQianLeiDa>Manual_juli)&&(ZuoHouLeiDa>Manual_juli)))
					{
						All_flag.speek_flag = 0;
					}	
					delay(0,0,0,5);				
				}
				while(YouShang==0)//右上
				{
					if(((QianZuoLeiDa<Manual_juli)||(QianYouLeiDa<Manual_juli)||(YouQianLeiDa<Manual_juli)||(YouHouLeiDa<Manual_juli)))
					{
						All_flag.speek_flag = 1;						
						MotoStop(5);
						
					}
					else if(((QianZuoLeiDa>Manual_juli)&&(QianYouLeiDa>Manual_juli)&&(YouQianLeiDa>Manual_juli)&&(YouHouLeiDa>Manual_juli)))
					{
						All_flag.speek_flag = 0;
					}	
					delay(0,0,0,5);				
				}
				while(YouXia==0)//右下
				{
					if(((HouZuoLeiDa<Manual_juli)||(HouYouLeiDa<Manual_juli)||(YouQianLeiDa<Manual_juli)||(YouHouLeiDa<Manual_juli)))
					{
						All_flag.speek_flag = 1;						
						MotoStop(5);
						
					}
					else if(((HouZuoLeiDa>Manual_juli)&&(HouYouLeiDa>Manual_juli)&&(YouQianLeiDa>Manual_juli)&&(YouHouLeiDa>Manual_juli)))
					{
						All_flag.speek_flag = 0;
					}	
					delay(0,0,0,5);				
				}
				All_flag.speek_flag = 0;
			}			
		}			
		delay(0,0,0,5);
	}
}
//语音处理
void WIFI_task(void *p_arg)
{	
	while(1)
	{
		if(All_flag.speek1_flag==1)
		{
			speek("前机械避障，请挪开障碍物!");
			delay(0,0,5,0);			
		}
		if(All_flag.speek3_flag==1)
		{
			speek("后机械避障，请挪开障碍物!");
			delay(0,0,5,0);			
		}		
		if(All_flag.speek_flag==1)
		{
			speek("前方有障碍！");
			delay(0,0,3,0);			
		}		
		if(All_flag.speek2_flag==1)
		{
			speek("电池电量不足，请及时充电！");
			delay(0,0,5,0);			
		}	
		delay(0,0,0,5);
	}
	
}
//判断平移或旋转是否到位到位
u8 onway=0;
void DEMO_task(void *p_arg)
{
	u16 cidaohang_now = 0,cidaohang_last = 0;
	while(1)
	{
		if(All_flag.flag_szd==0)
		{
			if(dir == 0)
			{
				cidaohang_now = QianCiDaoHangShuJu;
				if((cidaohang_last != 0x0000)&&(cidaohang_now == 0x0000))
				{
					tubian_num++;
				}
				cidaohang_last = cidaohang_now;
			}
			else if(dir == 1)
			{
				cidaohang_now = HouCiDaoHangShuJu;
				if((cidaohang_last != 0x0000)&&(cidaohang_now == 0x0000))
				{
					tubian_num++;
				}
				cidaohang_last = cidaohang_now;				
			}
			if(dir == 2)
			{
				cidaohang_now = QianCiDaoHangShuJu;
				if((cidaohang_last != 0xffff)&&(cidaohang_now == 0xffff))
				{
					onway=1;
				}
				if(onway==1)
				{
					if((abs(front_cdh16.Distance<1)))
					{
						onway=0;
						PingYiNum = 8;					
					}					
				}				
				cidaohang_last = cidaohang_now;
			}
			else if(dir == 3)
			{
				cidaohang_now = QianCiDaoHangShuJu;
				if((cidaohang_last != 0xffff)&&(cidaohang_now == 0xffff))
				{
					onway=1;
				}
				if(onway==1)
				{
					if((abs(front_cdh16.Distance<1)))
					{
						onway=0;
						PingYiNum = 8;					
					}					
				}				
				cidaohang_last = cidaohang_now;
			}
			else if(dir == 4)
			{
				cidaohang_now = QianCiDaoHangShuJu;
				if(((cidaohang_last != 0xffff)||(cidaohang_last == 0xffff))&&(cidaohang_now == 0xffff))
				{
					onway=1;
				}
				if(onway==1)
				{
					if((abs(front_cdh16.Distance<6)))
					{
						onway=0;
						XuanZhuanNUM++;					
					}					
				}				
				cidaohang_last = cidaohang_now;
			}
			else if(dir == 5)
			{
				cidaohang_now = QianCiDaoHangShuJu;
				if(((cidaohang_last != 0xffff)||(cidaohang_last == 0xffff))&&(cidaohang_now == 0xffff))
				{
					onway=1;
				}
				if(onway==1)
				{
					if((abs(front_cdh16.Distance<6)))
					{
						onway=0;
						XuanZhuanNUM++;					
					}					
				}				
				cidaohang_last = cidaohang_now;
			}			
		}			
		delay(0,0,0,5);   
	}
}

//启动
void DEMO1_task(void *p_arg)
{
	while(1)
	{
		if(All_flag.startAsk && (All_flag.jiting_flag == 0) &&(All_flag.flag_tz == 0) )
		{
			if(HmiTask == 0)
			{
				JieMianHao = 21;
				speek("请选择需要执行的任务！");
				All_flag.startAsk = 0;					
			}
			else
			{
				start();
				HmiTaskState = 5;
				HmiShouZiDongYinCang = 1;//隐藏启动显示停止
				All_flag.startAsk = 0;						
			}					
		}	
		delay(0,0,0,5);      
	}
}
//停止
void DEMO2_task(void *p_arg)
{
	u16 num=0;
	while(1)
	{
		num++;
		if(num==40)
		{
			num=0;
			IWDG_Feed();//喂狗
		}
		if(All_flag.stopAsk)
		{
			stop();
			HmiTaskState = 3;
			HmiShouZiDongYinCang = 0;//隐藏停止显示启动
			All_flag.stopAsk = 0;
		}
		delay(0,0,0,5);      
	}
}

