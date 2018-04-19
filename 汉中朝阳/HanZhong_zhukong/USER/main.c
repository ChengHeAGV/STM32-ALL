#include "sys.h"

//将这些优先级分配给了UCOSIII的5个系统内部任务
//优先级0：中断服务服务管理任务 OS_IntQTask()
//优先级1：时钟节拍任务 OS_TickTask()
//优先级2：定时任务 OS_TmrTask()
//优先级OS_CFG_PRIO_MAX-2：统计任务 OS_StatTask()
//优先级OS_CFG_PRIO_MAX-1：空闲任务 OS_IdleTask()
//任务优先级
#define START_TASK_PRIO     3
//任务堆栈大小
#define START_STK_SIZE      512
//任务控制块
OS_TCB StartTaskTCB;
//任务堆栈
CPU_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *p_arg);

//任务优先级
#define Transducer_TASK_PRIO        10
//任务堆栈大小
#define Transducer_STK_SIZE         512
//任务控制块
OS_TCB TransducerTaskTCB;
//任务堆栈
CPU_STK Transducer_TASK_STK[Transducer_STK_SIZE];
void Transducer_task(void *p_arg);


//任务优先级
#define Auto_TASK_PRIO      5
//任务堆栈大小
#define Auto_STK_SIZE       512
//任务控制块
OS_TCB AutoTaskTCB;
//任务堆栈
CPU_STK Auto_TASK_STK[Auto_STK_SIZE];
//任务函数
void Auto_task(void *p_arg);

//任务优先级
#define Manual_TASK_PRIO        6
//任务堆栈大小
#define Manual_STK_SIZE         512
//任务控制块
OS_TCB ManualTaskTCB;
//任务堆栈
CPU_STK Manual_TASK_STK[Manual_STK_SIZE];
//任务函数
void Manual_task(void *p_arg);

//任务优先级
#define FLOAT_TASK_PRIO     7
//任务堆栈大小
#define FLOAT_STK_SIZE      512
//任务控制块
OS_TCB  FloatTaskTCB;
//任务堆栈
CPU_STK FLOAT_TASK_STK[FLOAT_STK_SIZE];
//任务函数
void float_task(void *p_arg);

//任务优先级
#define DEMO_TASK_PRIO      8
//任务堆栈大小
#define DEMO_STK_SIZE       512
//任务控制块
OS_TCB DEMOTaskTCB;
//任务堆栈
CPU_STK DEMO_TASK_STK[DEMO_STK_SIZE];
//任务函数
void DEMO_task(void *p_arg);

//任务优先级
#define Task5_TASK_PRIO     9
//任务堆栈大小
#define Task5_STK_SIZE      512
//任务控制块
OS_TCB Task5_TaskTCB;
//任务堆栈
CPU_STK Task5_TASK_STK[Task5_STK_SIZE];
//任务函数
void Task5_task(void *p_arg);


//任务优先级
#define Control_TASK_PRIO       4
//任务堆栈大小
#define Control_STK_SIZE        512
//任务控制块
OS_TCB ControlTaskTCB;
//任务堆栈
CPU_STK Control_TASK_STK[Control_STK_SIZE];
//任务函数
void Control_task(void *p_arg);


//任务优先级
#define WIFI_TASK_PRIO      11
//任务堆栈大小
#define WIFI_STK_SIZE       512
//任务控制块
OS_TCB WIFITaskTCB;
//任务堆栈
CPU_STK WIFI_TASK_STK[WIFI_STK_SIZE];
//任务函数
void WIFI_task(void *p_arg);


//任务优先级
#define Screen_TASK_PRIO        12
//任务堆栈大小
#define Screen_STK_SIZE         512
//任务控制块
OS_TCB ScreenTaskTCB;
//任务堆栈
CPU_STK Screen_TASK_STK[Screen_STK_SIZE];
//任务函数
void Screen_task(void *p_arg);


//任务优先级
#define DEMO1_TASK_PRIO     13
//任务堆栈大小
#define DEMO1_STK_SIZE      512
//任务控制块
OS_TCB DEMO1TaskTCB;
//任务堆栈
CPU_STK DEMO1_TASK_STK[DEMO1_STK_SIZE];
//任务函数
void DEMO1_task(void *p_arg);

//任务优先级
#define DEMO2_TASK_PRIO     14
//任务堆栈大小
#define DEMO2_STK_SIZE      512
//任务控制块
OS_TCB DEMO2TaskTCB;
//任务堆栈
CPU_STK DEMO2_TASK_STK[DEMO2_STK_SIZE];
//任务函数
void DEMO2_task(void *p_arg);

//任务优先级
#define PID_TASK_PRIO       15
//任务堆栈大小
#define PID_STK_SIZE        512
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

	
	delay_init(168);    //时钟初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组配置

	LED_Init();         //LED初始化
	DMA_adc1_Init();
	DMA_Uart4_Init();
	DMA_Uart2_Init();
	//  DMA_Uart6_Init();
	DMA_Uart3_Init();
	ADC1_Configuration();
	USART1_Configuration(9600);
	USART4_Configuration(9600);
	//  USART6_Configuration(115200);
	USART2_Configuration(9600);
	USART3_Configuration(9600);

	OLED_Init();
	OLED_CLS();
	CAN1_Mode_Init(CAN_SJW_1tq, CAN_BS2_6tq,
	               CAN_BS1_7tq, 6,
	               CAN_Mode_Normal); //CAN1初始化普通模式,波特率500Kbps
	CAN2_Mode_Init(CAN_SJW_1tq, CAN_BS2_6tq,
	               CAN_BS1_7tq, 6,
	               CAN_Mode_Normal); //CAN2初始化普通模式,波特率500Kbps
	IWDG_Init(4, 500);
	TLC5620_Init();
	//发送继电器板同步信息
	CAN2_Send_Msg(can_Sebuf, 4);
	can_Sebuf[3] = 0;

	send3_buf[0] = 1;//给遥控器发送复位信号
	send3_buf[1] = 0;
	send3_buf[2] = 1;
	Uart3_Start_DMA_Tx(3);


	OSInit(&err);       //初始化UCOSIII
	OS_CRITICAL_ENTER();//进入临界区
	//创建开始任务
	OSTaskCreate((OS_TCB *)
	             &StartTaskTCB,           //任务控制块
	             (CPU_CHAR *)"start task",          //任务名字
	             (OS_TASK_PTR)start_task,           //任务函数
	             (void *)0,                         //传递给任务函数的参数
	             (OS_PRIO)START_TASK_PRIO,          //任务优先级
	             (CPU_STK *)
	             &START_TASK_STK[0],     //任务堆栈基地址
	             (CPU_STK_SIZE)START_STK_SIZE /
	             10, //任务堆栈深度限位
	             (CPU_STK_SIZE)START_STK_SIZE,      //任务堆栈大小
	             (OS_MSG_QTY)
	             0,                     //任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
	             (OS_TICK)0,                        //当使能时间片轮转时的时间片长度，为0时为默认长度，
	             (void *)0,                         //用户补充的存储区
	             (OS_OPT)OS_OPT_TASK_STK_CHK |
	             OS_OPT_TASK_STK_CLR, //任务选项
	             (OS_ERR *)
	             &err);                   //存放该函数错误时的返回值
	OS_CRITICAL_EXIT(); //退出临界区
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
	OSStatTaskCPUUsageInit(&err);   //统计任务
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN      //如果使能了测量中断关闭时间
	CPU_IntDisMeasMaxCurReset();
#endif

#if OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	//使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED, 1, &err);
#endif

	OS_CRITICAL_ENTER();    //进入临界区
	//创建Transducer任务
	OSTaskCreate((OS_TCB *)&TransducerTaskTCB,
	             (CPU_CHAR *)"Transducer task",
	             (OS_TASK_PTR)Transducer_task,
	             (void *)0,
	             (OS_PRIO)Transducer_TASK_PRIO,
	             (CPU_STK *)&Transducer_TASK_STK[0],
	             (CPU_STK_SIZE)Transducer_STK_SIZE / 10,
	             (CPU_STK_SIZE)Transducer_STK_SIZE,
	             (OS_MSG_QTY)0,
	             (OS_TICK)0,
	             (void *)0,
	             (OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR *)&err);

	//创建自动任务
	OSTaskCreate((OS_TCB *)&AutoTaskTCB,
	             (CPU_CHAR *)"Auto task",
	             (OS_TASK_PTR)Auto_task,
	             (void *)0,
	             (OS_PRIO)Auto_TASK_PRIO,
	             (CPU_STK *)&Auto_TASK_STK[0],
	             (CPU_STK_SIZE)Auto_STK_SIZE / 10,
	             (CPU_STK_SIZE)Auto_STK_SIZE,
	             (OS_MSG_QTY)0,
	             (OS_TICK)0,
	             (void *)0,
	             (OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR *)&err);

	//创建浮点测试任务
	OSTaskCreate((OS_TCB *)&FloatTaskTCB,
	             (CPU_CHAR *)"float test task",
	             (OS_TASK_PTR)float_task,
	             (void *)0,
	             (OS_PRIO)FLOAT_TASK_PRIO,
	             (CPU_STK *)&FLOAT_TASK_STK[0],
	             (CPU_STK_SIZE)FLOAT_STK_SIZE / 10,
	             (CPU_STK_SIZE)FLOAT_STK_SIZE,
	             (OS_MSG_QTY)0,
	             (OS_TICK)0,
	             (void *)0,
	             (OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR *)&err);

	//创建触摸屏任务
	OSTaskCreate((OS_TCB *)&ScreenTaskTCB,
	             (CPU_CHAR *)"Screen task",
	             (OS_TASK_PTR)Screen_task,
	             (void *)0,
	             (OS_PRIO)Screen_TASK_PRIO,
	             (CPU_STK *)&Screen_TASK_STK[0],
	             (CPU_STK_SIZE)Screen_STK_SIZE / 10,
	             (CPU_STK_SIZE)Screen_STK_SIZE,
	             (OS_MSG_QTY)0,
	             (OS_TICK)0,
	             (void *)0,
	             (OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR *)&err);

	//PID
	OSTaskCreate((OS_TCB *)&PIDTaskTCB,
	             (CPU_CHAR *)"PID task",
	             (OS_TASK_PTR)PID_task,
	             (void *)0,
	             (OS_PRIO)PID_TASK_PRIO,
	             (CPU_STK *)&PID_TASK_STK[0],
	             (CPU_STK_SIZE)PID_STK_SIZE / 10,
	             (CPU_STK_SIZE)PID_STK_SIZE,
	             (OS_MSG_QTY)0,
	             (OS_TICK)0,
	             (void *)0,
	             (OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR *)&err);
	//Control
	OSTaskCreate((OS_TCB *)&ControlTaskTCB,
	             (CPU_CHAR *)"Control task",
	             (OS_TASK_PTR)Control_task,
	             (void *)0,
	             (OS_PRIO)Control_TASK_PRIO,
	             (CPU_STK *)&Control_TASK_STK[0],
	             (CPU_STK_SIZE)Control_STK_SIZE / 10,
	             (CPU_STK_SIZE)Control_STK_SIZE,
	             (OS_MSG_QTY)0,
	             (OS_TICK)0,
	             (void *)0,
	             (OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR *)&err);
	//DEMO
	OSTaskCreate((OS_TCB *)&DEMOTaskTCB,
	             (CPU_CHAR *)"DEMO task",
	             (OS_TASK_PTR)DEMO_task,
	             (void *)0,
	             (OS_PRIO)DEMO_TASK_PRIO,
	             (CPU_STK *)&DEMO_TASK_STK[0],
	             (CPU_STK_SIZE)DEMO_STK_SIZE / 10,
	             (CPU_STK_SIZE)DEMO_STK_SIZE,
	             (OS_MSG_QTY)0,
	             (OS_TICK)0,
	             (void *)0,
	             (OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR *)&err);
	//DEMO1
	OSTaskCreate((OS_TCB *)&DEMO1TaskTCB,
	             (CPU_CHAR *)"DEMO1 task",
	             (OS_TASK_PTR)DEMO1_task,
	             (void *)0,
	             (OS_PRIO)DEMO1_TASK_PRIO,
	             (CPU_STK *)&DEMO1_TASK_STK[0],
	             (CPU_STK_SIZE)DEMO1_STK_SIZE / 10,
	             (CPU_STK_SIZE)DEMO1_STK_SIZE,
	             (OS_MSG_QTY)0,
	             (OS_TICK)0,
	             (void *)0,
	             (OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR *)&err);
	//DEMO2
	OSTaskCreate((OS_TCB *)&DEMO2TaskTCB,
	             (CPU_CHAR *)"DEMO2 task",
	             (OS_TASK_PTR)DEMO2_task,
	             (void *)0,
	             (OS_PRIO)DEMO2_TASK_PRIO,
	             (CPU_STK *)&DEMO2_TASK_STK[0],
	             (CPU_STK_SIZE)DEMO2_STK_SIZE / 10,
	             (CPU_STK_SIZE)DEMO2_STK_SIZE,
	             (OS_MSG_QTY)0,
	             (OS_TICK)0,
	             (void *)0,
	             (OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR *)&err);

	//创建手动任务
	OSTaskCreate((OS_TCB *)&ManualTaskTCB,
	             (CPU_CHAR *)"Manual task",
	             (OS_TASK_PTR)Manual_task,
	             (void *)0,
	             (OS_PRIO)Manual_TASK_PRIO,
	             (CPU_STK *)&Manual_TASK_STK[0],
	             (CPU_STK_SIZE)Manual_STK_SIZE / 10,
	             (CPU_STK_SIZE)Manual_STK_SIZE,
	             (OS_MSG_QTY)0,
	             (OS_TICK)0,
	             (void *)0,
	             (OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR *)&err);

	OSTaskCreate((OS_TCB *)&WIFITaskTCB,
	             (CPU_CHAR *)"WIFI task",
	             (OS_TASK_PTR)WIFI_task,
	             (void *)0,
	             (OS_PRIO)WIFI_TASK_PRIO,
	             (CPU_STK *)&WIFI_TASK_STK[0],
	             (CPU_STK_SIZE)WIFI_STK_SIZE / 10,
	             (CPU_STK_SIZE)WIFI_STK_SIZE,
	             (OS_MSG_QTY)0,
	             (OS_TICK)0,
	             (void *)0,
	             (OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR *)&err);

	OSTaskCreate((OS_TCB *)&Task5_TaskTCB,
	             (CPU_CHAR *)"Task5 task",
	             (OS_TASK_PTR)Task5_task,
	             (void *)0,
	             (OS_PRIO)Task5_TASK_PRIO,
	             (CPU_STK *)&Task5_TASK_STK[0],
	             (CPU_STK_SIZE)Task5_STK_SIZE / 10,
	             (CPU_STK_SIZE)Task5_STK_SIZE,
	             (OS_MSG_QTY)0,
	             (OS_TICK)0,
	             (void *)0,
	             (OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR *)&err);

	OS_TaskSuspend((OS_TCB *)&StartTaskTCB,
	               &err);      //挂起开始任务
	OS_CRITICAL_EXIT(); //进入临界区
}
//遥控器动作
void Transducer_task(void *p_arg)
{
	UserConfigInit();
	SystemParameter[98] -= 1;
	if(SystemParameter[98] <= 1)	SystemParameter[98] = 1;
	SetAllParameterToSystem();
	while(1)
	{
		if((SystemParameter[98]<=1)&&(SystemParameter[99])==1)
		{
			LED1 = 0;LED2 = 0;LED3 = 0;LED4 = 0;
		}
		else
		{
			if(YaoKong.JiTing == 1)//没按下急停可以行走和升降
			{
				if(YaoKong.XingZou_OR_ShengJiang == 1) //当前是行走状态

				{
					if((All_flag.DJQD2_GZ == 0)&&(All_flag.DJQD3_GZ == 0)&&(All_flag.DJQD4_GZ == 0)&&(All_flag.DJQD5_GZ == 0))//无故障
					{
						PLC_ShangSheng = 1;
						PLC_XiaJiang =  1;
						PLC_XingZou_OR_ShengJiang = 1;
						if(PLC_FanKui == 0)
						{
							PLC_DongZuo(YaoKong.DongZuo, YaoKong.SuDu);
						}
						else
						{
							if(All_flag.flag_tz == 0) //雷达没有避障，可以行走
							{
								PLC_DongZuo(YaoKong.DongZuo, YaoKong.SuDu);
							}
							else//雷达避障，停止车辆
							{
								PLC_MoterStop();
							}							
						}						
					}
				}
				else//当前是升降状态
				{
					PLC_KuaiMan = YaoKong.KuaiSu_OR_ManSu;
					PLC_XingZou_OR_ShengJiang = 0;
					PLC_MoterStop();				
					PLC_ShangSheng = YaoKong.QiSheng;
					PLC_XiaJiang =  YaoKong.XiaJiang;
				}
			}
			else//按下急停不可行走不可升降
			{
				PLC_MoterStop();
				PLC_ShangSheng = 1;
				PLC_XiaJiang =  1;
			}			
		}			
		delay(0, 0, 0, 10); //延时10ms
	}
}
//开关量处理
void Auto_task(void *p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		PLC_JiTing = YaoKong.JiTing;
		if((YaoKong.QiSheng==0)&&(YaoKong.XiaJiang==0)&&(YaoKong.YaoGan_Key==0)&&(YaoKong.XingZou_OR_ShengJiang==1))
		{
			SystemParameter[99] = 0;
			SetAllParameterToSystem();
		}
		delay(0, 0, 0, 10); //延时10ms
	}
}
//手动操作
void Manual_task(void *p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		delay(0, 0, 0, 10); //延时10ms
	}
}
//电机PID调节
u8 cy_time = 10;
void PID_task(void *p_arg)
{
	while(1)
	{
		delay(0, 0, 0, cy_time);
	}
}
//蜂鸣器
void float_task(void *p_arg)
{
	u8 num = 0;
	p_arg = p_arg;
	while(1)
	{
		num++;
		if(num == 50)
		{
			LED1 = ~LED1;//运行灯
			TongXunDeng = ~TongXunDeng; //触摸屏通讯指示灯
			num = 0;
		}

		delay(0, 0, 0, 10); //延时5ms
	}
}
//触摸屏上路径流程参数设置
u8 xintiao_buf[4] = {0xff, 0xff, 0xff, 0xff};
void Screen_task(void *p_arg)
{
	while(1)
	{
		CAN2_Send_Msg(xintiao_buf, 4);
		delay(0, 0, 0, 500);
	}
}
//自动执行路径或流程
void Task5_task(void *p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		delay(0, 0, 0, 10);
	}
}

//避障处理
void Control_task(void *p_arg)
{
	while(1)
	{
		Manual_juli = 60;
		JianSu_juli = 110;
		while(YaoKong.DongZuo == 1)
		{
			if((leida.QianZuoLeiDa_1 > JianSu_juli) && (leida.QianZuoLeiDa_2 > JianSu_juli)
				&& (leida.QianZuoLeiDa_3 > JianSu_juli)&& (leida.QianZuoLeiDa_4 > JianSu_juli))
			{
				PLC_JianSu = 1;
			}
			else
			{				
				PLC_JianSu = 0;
				if((leida.QianZuoLeiDa_1 > Manual_juli) && (leida.QianZuoLeiDa_2 > Manual_juli)
					&& (leida.QianZuoLeiDa_3 > Manual_juli)&& (leida.QianZuoLeiDa_4 > Manual_juli))
				{
					All_flag.flag_tz = 0;
				}
				else
				{
					All_flag.flag_tz = 1;
				}				
			}
			delay(0, 0, 0, 5);
		}
		while(YaoKong.DongZuo == 2) //后退
		{
			if((leida.HouZuoLeiDa_1 > JianSu_juli) && (leida.HouZuoLeiDa_2 > JianSu_juli)
				&& (leida.HouZuoLeiDa_3 > JianSu_juli)&& (leida.HouZuoLeiDa_4 > JianSu_juli))
			{
				PLC_JianSu = 1;				
			}
			else
			{
				PLC_JianSu = 0;
				if((leida.HouZuoLeiDa_1 > Manual_juli) && (leida.HouZuoLeiDa_2 > Manual_juli)
					&& (leida.HouZuoLeiDa_3 > Manual_juli)&& (leida.HouZuoLeiDa_4 > Manual_juli))
				{
					All_flag.flag_tz = 0;
				}
				else
				{
					All_flag.flag_tz = 1;
				}				
			}
			delay(0, 0, 0, 5);
		}
		while(YaoKong.DongZuo == 3) //左移
		{
			if(((leida.ZuoQianLeiDa_1 > JianSu_juli) && (leida.ZuoQianLeiDa_2 > JianSu_juli)
				&& (leida.ZuoQianLeiDa_3 > JianSu_juli) && (leida.ZuoQianLeiDa_4 > JianSu_juli)))
			{
				PLC_JianSu = 1;
			}
			else
			{
				PLC_JianSu = 0;
				if(((leida.ZuoQianLeiDa_1 > Manual_juli) && (leida.ZuoQianLeiDa_2 > Manual_juli)
					&& (leida.ZuoQianLeiDa_3 > Manual_juli) && (leida.ZuoQianLeiDa_4 > Manual_juli)))
				{
					All_flag.flag_tz = 0;
				}
				else
				{
					All_flag.flag_tz = 1;
				}				
			}
			delay(0, 0, 0, 5);
		}
		while(YaoKong.DongZuo == 4) //右移
		{
			if(((leida.YouQianLeiDa_1 > JianSu_juli) && (leida.YouQianLeiDa_2 > JianSu_juli)
				 && (leida.YouQianLeiDa_3 > JianSu_juli) && (leida.YouQianLeiDa_4 > JianSu_juli)))
			{
				PLC_JianSu = 1;
			}
			else
			{
				PLC_JianSu = 0;
				if(((leida.YouQianLeiDa_1 > Manual_juli) && (leida.YouQianLeiDa_2 > Manual_juli)
					 && (leida.YouQianLeiDa_3 > Manual_juli) && (leida.YouQianLeiDa_4 > Manual_juli)))
				{
					All_flag.flag_tz = 0;
				}
				else
				{
					All_flag.flag_tz = 1;
				}				
			}
			delay(0, 0, 0, 5);
		}
		while(YaoKong.DongZuo == 9) //左旋
		{
			if(((leida.ZuoQianLeiDa_1 > JianSu_juli) && (leida.ZuoQianLeiDa_2 > JianSu_juli)
				&& (leida.ZuoQianLeiDa_3 > JianSu_juli) && (leida.ZuoQianLeiDa_4 > JianSu_juli)))
			{
				PLC_JianSu = 1;				
			}
			else
			{
				PLC_JianSu = 0;
				if(((leida.ZuoQianLeiDa_1 > Manual_juli) && (leida.ZuoQianLeiDa_2 > Manual_juli)
					&& (leida.ZuoQianLeiDa_3 > Manual_juli) && (leida.ZuoQianLeiDa_4 > Manual_juli)))
				{
					All_flag.flag_tz = 0;
				}	
				else
				{
					All_flag.flag_tz = 1;					
				}
			}
			delay(0, 0, 0, 5);
		}
		while(YaoKong.DongZuo == 10) //右旋
		{
			if(((leida.YouQianLeiDa_1 > JianSu_juli) && (leida.YouQianLeiDa_2 > JianSu_juli)
				 && (leida.YouQianLeiDa_3 > JianSu_juli) && (leida.YouQianLeiDa_4 > JianSu_juli)))
			{
				PLC_JianSu = 1;
			}
			else
			{
				PLC_JianSu = 0;
				if(((leida.YouQianLeiDa_1 > Manual_juli) && (leida.YouQianLeiDa_2 > Manual_juli)
					 && (leida.YouQianLeiDa_3 > Manual_juli) && (leida.YouQianLeiDa_4 > Manual_juli)))
				{
					All_flag.flag_tz = 0;					
				}
				else
				{
					All_flag.flag_tz = 1;					
				}
			}			
			delay(0, 0, 0, 5);
		}
		while(YaoKong.DongZuo == 5) //左上
		{
			if(((leida.ZuoQianLeiDa_1 > JianSu_juli) && (leida.ZuoQianLeiDa_2 > JianSu_juli)
				&& (leida.ZuoQianLeiDa_3 > JianSu_juli) && (leida.ZuoQianLeiDa_4 > JianSu_juli)
			&& (leida.QianZuoLeiDa_1 > JianSu_juli) && (leida.QianZuoLeiDa_2 > JianSu_juli)
				 && (leida.QianZuoLeiDa_3 > JianSu_juli) && (leida.QianZuoLeiDa_4 > JianSu_juli)))
			{
				PLC_JianSu = 1;
			}
			else
			{
				PLC_JianSu = 0;
				if(((leida.ZuoQianLeiDa_1 > Manual_juli) && (leida.ZuoQianLeiDa_2 > Manual_juli)
					&& (leida.ZuoQianLeiDa_3 > Manual_juli) && (leida.ZuoQianLeiDa_4 > Manual_juli)
				&& (leida.QianZuoLeiDa_1 > Manual_juli) && (leida.QianZuoLeiDa_2 > Manual_juli)
					 && (leida.QianZuoLeiDa_3 > Manual_juli) && (leida.QianZuoLeiDa_4 > Manual_juli)))
				{
					All_flag.flag_tz = 0;
				}	
				else
				{
					All_flag.flag_tz = 1;					
				}
			}
			delay(0, 0, 0, 5);
		}
		while(YaoKong.DongZuo == 7) //左下
		{
			if(((leida.ZuoQianLeiDa_1 > JianSu_juli) && (leida.ZuoQianLeiDa_2 > JianSu_juli)
				&& (leida.ZuoQianLeiDa_3 > JianSu_juli) && (leida.ZuoQianLeiDa_4 > JianSu_juli)
			&& (leida.HouZuoLeiDa_1 > JianSu_juli) && (leida.HouZuoLeiDa_2 > JianSu_juli)
				 && (leida.HouZuoLeiDa_3 > JianSu_juli) && (leida.HouZuoLeiDa_4 > JianSu_juli)))
			{
				PLC_JianSu = 1;
			}
			else
			{
				PLC_JianSu = 0;
				if(((leida.ZuoQianLeiDa_1 > Manual_juli) && (leida.ZuoQianLeiDa_2 > Manual_juli)
					&& (leida.ZuoQianLeiDa_3 > Manual_juli) && (leida.ZuoQianLeiDa_4 > Manual_juli)
				&& (leida.HouZuoLeiDa_1 > Manual_juli) && (leida.HouZuoLeiDa_2 > Manual_juli)
					 && (leida.HouZuoLeiDa_3 > Manual_juli) && (leida.HouZuoLeiDa_4 > Manual_juli)))
				{
					All_flag.flag_tz = 0;
				}
				else
				{
					All_flag.flag_tz = 1;					
				}
			}			
			delay(0, 0, 0, 5);
		}
		while(YaoKong.DongZuo == 6) //右上
		{
			if(((leida.YouQianLeiDa_1 > JianSu_juli) && (leida.YouQianLeiDa_2 > JianSu_juli)
				&& (leida.YouQianLeiDa_3 > JianSu_juli) && (leida.YouQianLeiDa_4 > JianSu_juli)
			&& (leida.QianZuoLeiDa_1 > JianSu_juli) && (leida.QianZuoLeiDa_2 > JianSu_juli)
				 && (leida.QianZuoLeiDa_3 > JianSu_juli) && (leida.QianZuoLeiDa_4 > JianSu_juli)))
			{
				PLC_JianSu = 1;
			}
			else
			{
				PLC_JianSu = 0;
				if(((leida.YouQianLeiDa_1 > Manual_juli) && (leida.YouQianLeiDa_2 > Manual_juli)
					&& (leida.YouQianLeiDa_3 > Manual_juli) && (leida.YouQianLeiDa_4 > Manual_juli)
				&& (leida.QianZuoLeiDa_1 > Manual_juli) && (leida.QianZuoLeiDa_2 > Manual_juli)
					 && (leida.QianZuoLeiDa_3 > Manual_juli) && (leida.QianZuoLeiDa_4 > Manual_juli)))	
				{
					All_flag.flag_tz = 0;
				}
				else
				{
					All_flag.flag_tz = 1;					
				}
			}
			delay(0, 0, 0, 5);
		}
		while(YaoKong.DongZuo == 8) //右下
		{
			if(((leida.YouQianLeiDa_1 > JianSu_juli) && (leida.YouQianLeiDa_2 > JianSu_juli)
				&& (leida.YouQianLeiDa_3 > JianSu_juli) && (leida.YouQianLeiDa_4 > JianSu_juli)
			&& (leida.HouZuoLeiDa_1 > JianSu_juli) && (leida.HouZuoLeiDa_2 > JianSu_juli)
				 && (leida.HouZuoLeiDa_3 > JianSu_juli) && (leida.HouZuoLeiDa_4 > JianSu_juli)))
			{
				PLC_JianSu = 1;
			}
			else
			{
				PLC_JianSu = 0;
				if(((leida.YouQianLeiDa_1 > Manual_juli) && (leida.YouQianLeiDa_2 > Manual_juli)
					&& (leida.YouQianLeiDa_3 > Manual_juli) && (leida.YouQianLeiDa_4 > Manual_juli)
				&& (leida.HouZuoLeiDa_1 > Manual_juli) && (leida.HouZuoLeiDa_2 > Manual_juli)
					 && (leida.HouZuoLeiDa_3 > Manual_juli) && (leida.HouZuoLeiDa_4 > Manual_juli)))
				{
					All_flag.flag_tz = 0;
				}
				else
				{
					All_flag.flag_tz = 1;
				}			
			}
			delay(0, 0, 0, 5);
		}
		All_flag.flag_tz = 0;
		PLC_JianSu = 1;
		delay(0, 0, 0, 5);
	}
}
//语音处理
void WIFI_task(void *p_arg)
{
	while(1)
	{
		delay(0, 0, 0, 10);
	}

}
//OLED信息显示
u8 QDQ2_SEND[4] = {0X04,0X02,0XD2,0X00};
u8 QDQ3_SEND[4] = {0X04,0X03,0XD2,0X00};
u8 QDQ4_SEND[4] = {0X04,0X04,0XD2,0X00};
u8 QDQ5_SEND[4] = {0X04,0X05,0XD2,0X00};
void DEMO_task(void *p_arg)
{
	while(1)
	{
		CAN1_Send_Msg_stdid(QDQ2_SEND, 4, 0x02);
		delay(0, 0, 0, 20);
		CAN1_Send_Msg_stdid(QDQ3_SEND, 4, 0x03);
		delay(0, 0, 0, 20);
		CAN1_Send_Msg_stdid(QDQ4_SEND, 4, 0x04);
		delay(0, 0, 0, 20);
		CAN1_Send_Msg_stdid(QDQ5_SEND, 4, 0x05);
		delay(0, 0, 1, 0);
	}
}

//向遥控器通知是否故障
void DEMO1_task(void *p_arg)
{
	while(1)
	{
		send3_buf[0] = 1;
		send3_buf[1] = 1;
		send3_buf[2] = 1;
		Uart3_Start_DMA_Tx(3);
		delay(0, 0, 0, 500);
	}
}
//看门狗
void DEMO2_task(void *p_arg)
{
	u16 num = 0;
	while(1)
	{
		num++;
		if(num == 20)
		{
			num = 0;
			IWDG_Feed();//喂狗
		}
		delay(0, 0, 0, 10);
	}
}

