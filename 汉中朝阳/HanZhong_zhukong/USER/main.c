#include "sys.h"

//����Щ���ȼ��������UCOSIII��5��ϵͳ�ڲ�����
//���ȼ�0���жϷ������������� OS_IntQTask()
//���ȼ�1��ʱ�ӽ������� OS_TickTask()
//���ȼ�2����ʱ���� OS_TmrTask()
//���ȼ�OS_CFG_PRIO_MAX-2��ͳ������ OS_StatTask()
//���ȼ�OS_CFG_PRIO_MAX-1���������� OS_IdleTask()
//�������ȼ�
#define START_TASK_PRIO     3
//�����ջ��С
#define START_STK_SIZE      512
//������ƿ�
OS_TCB StartTaskTCB;
//�����ջ
CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);

//�������ȼ�
#define Transducer_TASK_PRIO        10
//�����ջ��С
#define Transducer_STK_SIZE         512
//������ƿ�
OS_TCB TransducerTaskTCB;
//�����ջ
CPU_STK Transducer_TASK_STK[Transducer_STK_SIZE];
void Transducer_task(void *p_arg);


//�������ȼ�
#define Auto_TASK_PRIO      5
//�����ջ��С
#define Auto_STK_SIZE       512
//������ƿ�
OS_TCB AutoTaskTCB;
//�����ջ
CPU_STK Auto_TASK_STK[Auto_STK_SIZE];
//������
void Auto_task(void *p_arg);

//�������ȼ�
#define Manual_TASK_PRIO        6
//�����ջ��С
#define Manual_STK_SIZE         512
//������ƿ�
OS_TCB ManualTaskTCB;
//�����ջ
CPU_STK Manual_TASK_STK[Manual_STK_SIZE];
//������
void Manual_task(void *p_arg);

//�������ȼ�
#define FLOAT_TASK_PRIO     7
//�����ջ��С
#define FLOAT_STK_SIZE      512
//������ƿ�
OS_TCB  FloatTaskTCB;
//�����ջ
CPU_STK FLOAT_TASK_STK[FLOAT_STK_SIZE];
//������
void float_task(void *p_arg);

//�������ȼ�
#define DEMO_TASK_PRIO      8
//�����ջ��С
#define DEMO_STK_SIZE       512
//������ƿ�
OS_TCB DEMOTaskTCB;
//�����ջ
CPU_STK DEMO_TASK_STK[DEMO_STK_SIZE];
//������
void DEMO_task(void *p_arg);

//�������ȼ�
#define Task5_TASK_PRIO     9
//�����ջ��С
#define Task5_STK_SIZE      512
//������ƿ�
OS_TCB Task5_TaskTCB;
//�����ջ
CPU_STK Task5_TASK_STK[Task5_STK_SIZE];
//������
void Task5_task(void *p_arg);


//�������ȼ�
#define Control_TASK_PRIO       4
//�����ջ��С
#define Control_STK_SIZE        512
//������ƿ�
OS_TCB ControlTaskTCB;
//�����ջ
CPU_STK Control_TASK_STK[Control_STK_SIZE];
//������
void Control_task(void *p_arg);


//�������ȼ�
#define WIFI_TASK_PRIO      11
//�����ջ��С
#define WIFI_STK_SIZE       512
//������ƿ�
OS_TCB WIFITaskTCB;
//�����ջ
CPU_STK WIFI_TASK_STK[WIFI_STK_SIZE];
//������
void WIFI_task(void *p_arg);


//�������ȼ�
#define Screen_TASK_PRIO        12
//�����ջ��С
#define Screen_STK_SIZE         512
//������ƿ�
OS_TCB ScreenTaskTCB;
//�����ջ
CPU_STK Screen_TASK_STK[Screen_STK_SIZE];
//������
void Screen_task(void *p_arg);


//�������ȼ�
#define DEMO1_TASK_PRIO     13
//�����ջ��С
#define DEMO1_STK_SIZE      512
//������ƿ�
OS_TCB DEMO1TaskTCB;
//�����ջ
CPU_STK DEMO1_TASK_STK[DEMO1_STK_SIZE];
//������
void DEMO1_task(void *p_arg);

//�������ȼ�
#define DEMO2_TASK_PRIO     14
//�����ջ��С
#define DEMO2_STK_SIZE      512
//������ƿ�
OS_TCB DEMO2TaskTCB;
//�����ջ
CPU_STK DEMO2_TASK_STK[DEMO2_STK_SIZE];
//������
void DEMO2_task(void *p_arg);

//�������ȼ�
#define PID_TASK_PRIO       15
//�����ջ��С
#define PID_STK_SIZE        512
//������ƿ�
OS_TCB PIDTaskTCB;
//�����ջ
CPU_STK PID_TASK_STK[PID_STK_SIZE];
//������
void PID_task(void *p_arg);

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();

	
	delay_init(168);    //ʱ�ӳ�ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�жϷ�������

	LED_Init();         //LED��ʼ��
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
	               CAN_Mode_Normal); //CAN1��ʼ����ͨģʽ,������500Kbps
	CAN2_Mode_Init(CAN_SJW_1tq, CAN_BS2_6tq,
	               CAN_BS1_7tq, 6,
	               CAN_Mode_Normal); //CAN2��ʼ����ͨģʽ,������500Kbps
	IWDG_Init(4, 500);
	TLC5620_Init();
	//���ͼ̵�����ͬ����Ϣ
	CAN2_Send_Msg(can_Sebuf, 4);
	can_Sebuf[3] = 0;

	send3_buf[0] = 1;//��ң�������͸�λ�ź�
	send3_buf[1] = 0;
	send3_buf[2] = 1;
	Uart3_Start_DMA_Tx(3);


	OSInit(&err);       //��ʼ��UCOSIII
	OS_CRITICAL_ENTER();//�����ٽ���
	//������ʼ����
	OSTaskCreate((OS_TCB *)
	             &StartTaskTCB,           //������ƿ�
	             (CPU_CHAR *)"start task",          //��������
	             (OS_TASK_PTR)start_task,           //������
	             (void *)0,                         //���ݸ��������Ĳ���
	             (OS_PRIO)START_TASK_PRIO,          //�������ȼ�
	             (CPU_STK *)
	             &START_TASK_STK[0],     //�����ջ����ַ
	             (CPU_STK_SIZE)START_STK_SIZE /
	             10, //�����ջ�����λ
	             (CPU_STK_SIZE)START_STK_SIZE,      //�����ջ��С
	             (OS_MSG_QTY)
	             0,                     //�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
	             (OS_TICK)0,                        //��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
	             (void *)0,                         //�û�����Ĵ洢��
	             (OS_OPT)OS_OPT_TASK_STK_CHK |
	             OS_OPT_TASK_STK_CLR, //����ѡ��
	             (OS_ERR *)
	             &err);                   //��Ÿú�������ʱ�ķ���ֵ
	OS_CRITICAL_EXIT(); //�˳��ٽ���
	OSStart(&err);  //����UCOSIII
	while(1);
}
//��ʼ������
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
	OSStatTaskCPUUsageInit(&err);   //ͳ������
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN      //���ʹ���˲����жϹر�ʱ��
	CPU_IntDisMeasMaxCurReset();
#endif

#if OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	//ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED, 1, &err);
#endif

	OS_CRITICAL_ENTER();    //�����ٽ���
	//����Transducer����
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

	//�����Զ�����
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

	//���������������
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

	//��������������
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

	//�����ֶ�����
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
	               &err);      //����ʼ����
	OS_CRITICAL_EXIT(); //�����ٽ���
}
//ң��������
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
			if(YaoKong.JiTing == 1)//û���¼�ͣ�������ߺ�����
			{
				if(YaoKong.XingZou_OR_ShengJiang == 1) //��ǰ������״̬

				{
					if((All_flag.DJQD2_GZ == 0)&&(All_flag.DJQD3_GZ == 0)&&(All_flag.DJQD4_GZ == 0)&&(All_flag.DJQD5_GZ == 0))//�޹���
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
							if(All_flag.flag_tz == 0) //�״�û�б��ϣ���������
							{
								PLC_DongZuo(YaoKong.DongZuo, YaoKong.SuDu);
							}
							else//�״���ϣ�ֹͣ����
							{
								PLC_MoterStop();
							}							
						}						
					}
				}
				else//��ǰ������״̬
				{
					PLC_KuaiMan = YaoKong.KuaiSu_OR_ManSu;
					PLC_XingZou_OR_ShengJiang = 0;
					PLC_MoterStop();				
					PLC_ShangSheng = YaoKong.QiSheng;
					PLC_XiaJiang =  YaoKong.XiaJiang;
				}
			}
			else//���¼�ͣ�������߲�������
			{
				PLC_MoterStop();
				PLC_ShangSheng = 1;
				PLC_XiaJiang =  1;
			}			
		}			
		delay(0, 0, 0, 10); //��ʱ10ms
	}
}
//����������
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
		delay(0, 0, 0, 10); //��ʱ10ms
	}
}
//�ֶ�����
void Manual_task(void *p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		delay(0, 0, 0, 10); //��ʱ10ms
	}
}
//���PID����
u8 cy_time = 10;
void PID_task(void *p_arg)
{
	while(1)
	{
		delay(0, 0, 0, cy_time);
	}
}
//������
void float_task(void *p_arg)
{
	u8 num = 0;
	p_arg = p_arg;
	while(1)
	{
		num++;
		if(num == 50)
		{
			LED1 = ~LED1;//���е�
			TongXunDeng = ~TongXunDeng; //������ͨѶָʾ��
			num = 0;
		}

		delay(0, 0, 0, 10); //��ʱ5ms
	}
}
//��������·�����̲�������
u8 xintiao_buf[4] = {0xff, 0xff, 0xff, 0xff};
void Screen_task(void *p_arg)
{
	while(1)
	{
		CAN2_Send_Msg(xintiao_buf, 4);
		delay(0, 0, 0, 500);
	}
}
//�Զ�ִ��·��������
void Task5_task(void *p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		delay(0, 0, 0, 10);
	}
}

//���ϴ���
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
		while(YaoKong.DongZuo == 2) //����
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
		while(YaoKong.DongZuo == 3) //����
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
		while(YaoKong.DongZuo == 4) //����
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
		while(YaoKong.DongZuo == 9) //����
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
		while(YaoKong.DongZuo == 10) //����
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
		while(YaoKong.DongZuo == 5) //����
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
		while(YaoKong.DongZuo == 7) //����
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
		while(YaoKong.DongZuo == 6) //����
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
		while(YaoKong.DongZuo == 8) //����
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
//��������
void WIFI_task(void *p_arg)
{
	while(1)
	{
		delay(0, 0, 0, 10);
	}

}
//OLED��Ϣ��ʾ
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

//��ң����֪ͨ�Ƿ����
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
//���Ź�
void DEMO2_task(void *p_arg)
{
	u16 num = 0;
	while(1)
	{
		num++;
		if(num == 20)
		{
			num = 0;
			IWDG_Feed();//ι��
		}
		delay(0, 0, 0, 10);
	}
}

