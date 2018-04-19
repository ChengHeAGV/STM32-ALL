#include "sys.h"
//����Щ���ȼ��������UCOSIII��5��ϵͳ�ڲ�����
//���ȼ�0���жϷ������������� OS_IntQTask()
//���ȼ�1��ʱ�ӽ������� OS_TickTask()
//���ȼ�2����ʱ���� OS_TmrTask()
//���ȼ�OS_CFG_PRIO_MAX-2��ͳ������ OS_StatTask()
//���ȼ�OS_CFG_PRIO_MAX-1���������� OS_IdleTask()
//�������ȼ�
#define START_TASK_PRIO		3
//�����ջ��С
#define START_STK_SIZE 		512
//������ƿ�
OS_TCB StartTaskTCB;
//�����ջ
CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);

//�������ȼ�
#define Transducer_TASK_PRIO		4
//�����ջ��С
#define Transducer_STK_SIZE 		512
//������ƿ�
OS_TCB TransducerTaskTCB;
//�����ջ
CPU_STK Transducer_TASK_STK[Transducer_STK_SIZE];
void Transducer_task(void *p_arg);


//�������ȼ�
#define Auto_TASK_PRIO		5
//�����ջ��С
#define Auto_STK_SIZE 		512
//������ƿ�
OS_TCB AutoTaskTCB;
//�����ջ
CPU_STK Auto_TASK_STK[Auto_STK_SIZE];
//������
void Auto_task(void *p_arg);

//�������ȼ�
#define Manual_TASK_PRIO		6
//�����ջ��С
#define Manual_STK_SIZE 		512
//������ƿ�
OS_TCB ManualTaskTCB;
//�����ջ
CPU_STK Manual_TASK_STK[Manual_STK_SIZE];
//������
void Manual_task(void *p_arg);

//�������ȼ�
#define FLOAT_TASK_PRIO		7
//�����ջ��С
#define FLOAT_STK_SIZE		512
//������ƿ�
OS_TCB	FloatTaskTCB;
//�����ջ
CPU_STK	FLOAT_TASK_STK[FLOAT_STK_SIZE];
//������
void float_task(void *p_arg);

//�������ȼ�
#define DEMO_TASK_PRIO		8
//�����ջ��С
#define DEMO_STK_SIZE 		512
//������ƿ�
OS_TCB DEMOTaskTCB;
//�����ջ
CPU_STK DEMO_TASK_STK[DEMO_STK_SIZE];
//������
void DEMO_task(void *p_arg);

//�������ȼ�
#define Task5_TASK_PRIO		9
//�����ջ��С
#define Task5_STK_SIZE 		512
//������ƿ�
OS_TCB Task5_TaskTCB;
//�����ջ
CPU_STK Task5_TASK_STK[Task5_STK_SIZE];
//������
void Task5_task(void *p_arg);


//�������ȼ�
#define Control_TASK_PRIO		10
//�����ջ��С
#define Control_STK_SIZE 		512
//������ƿ�
OS_TCB ControlTaskTCB;
//�����ջ
CPU_STK Control_TASK_STK[Control_STK_SIZE];
//������
void Control_task(void *p_arg);


//�������ȼ�
#define WIFI_TASK_PRIO		11
//�����ջ��С
#define WIFI_STK_SIZE 		512
//������ƿ�
OS_TCB WIFITaskTCB;
//�����ջ
CPU_STK WIFI_TASK_STK[WIFI_STK_SIZE];
//������
void WIFI_task(void *p_arg);


//�������ȼ�
#define DEMO1_TASK_PRIO		13
//�����ջ��С
#define DEMO1_STK_SIZE 		512
//������ƿ�
OS_TCB DEMO1TaskTCB;
//�����ջ
CPU_STK DEMO1_TASK_STK[DEMO1_STK_SIZE];
//������
void DEMO1_task(void *p_arg);

//�������ȼ�
#define DEMO2_TASK_PRIO		12
//�����ջ��С
#define DEMO2_STK_SIZE 		512
//������ƿ�
OS_TCB DEMO2TaskTCB;
//�����ջ
CPU_STK DEMO2_TASK_STK[DEMO2_STK_SIZE];
//������
void DEMO2_task(void *p_arg);


//�������ȼ�
#define Screen_TASK_PRIO		14
//�����ջ��С
#define Screen_STK_SIZE 		512
//������ƿ�
OS_TCB ScreenTaskTCB;
//�����ջ
CPU_STK Screen_TASK_STK[Screen_STK_SIZE];
//������
void Screen_task(void *p_arg);


//�������ȼ�
#define PID_TASK_PRIO		15
//�����ջ��С
#define PID_STK_SIZE 		512
//������ƿ�
OS_TCB PIDTaskTCB;
//�����ջ
CPU_STK PID_TASK_STK[PID_STK_SIZE];
//������
void PID_task(void *p_arg);

#define SOCK_TCPS        0
#define SOCK_UDPS        1
#define DATA_BUF_SIZE   2048
/* Private macro -------------------------------------------------------------*/
uint8_t gDATABUF[DATA_BUF_SIZE];
uint32_t CPU_ID[3];
// Default Network Configuration
wiz_NetInfo gWIZNETINFO = { .mac = {0x00, 0x08, 0xdc, 0x00, 0xab, 0xcd},
                            .ip = {192, 168, 1, 123},
                            .sn = {255, 255, 255, 0},
                            .gw = {192, 168, 1, 1},
                            .dns = {0, 0, 0, 0},
                            .dhcp = NETINFO_STATIC
                          };
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void platform_init(void);								// initialize the dependent host peripheral
void network_init(void);								// Initialize Network information and display it
int32_t loopback_tcps(uint8_t, uint8_t *, uint16_t);		// Loopback TCP server
int32_t loopback_udps(uint8_t, uint8_t *, uint16_t);		// Loopback UDP server

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();

	delay_init(168);  	//ʱ�ӳ�ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�жϷ�������
	LED_Init();         //LED��ʼ��
	DMA_adc1_Init();
	DMA_Uart4_Init();
	DMA_Uart2_Init();
	DMA_Uart6_Init();
	DMA_Uart3_Init();
	DMA_Uart5_Init();
	ADC1_Configuration();
	USART1_Configuration(9600);
	USART4_Configuration(9600);
	USART6_Configuration(9600);
	USART2_Configuration(9600);
	USART3_Configuration(9600);
	USART5_Configuration(9600);
	TIM4_PWM_Init(1000 - 1, 8 - 1);	//84M/8=10Mhz?????,????1000,??PWM??? 10M/50000=200hz. //500-10   20hz-1000hz
	CAN1_Mode_Init(CAN_SJW_1tq, CAN_BS2_6tq, CAN_BS1_7tq, 6, CAN_Mode_Normal); //CAN1��ʼ����ͨģʽ,������500Kbps
	CAN2_Mode_Init(CAN_SJW_1tq, CAN_BS2_6tq, CAN_BS1_7tq, 6, CAN_Mode_Normal); //CAN2��ʼ����ͨģʽ,������500Kbps
	PID_Init();
	TIM2_Int_Init(5000 - 1, 840 - 1);			//Tout=((arr+1)*(psc+1))/Ft us.  50ms
	IWDG_Init(4, 500);

	SPI1_Init();

	OSInit(&err);		//��ʼ��UCOSIII
	OS_CRITICAL_ENTER();//�����ٽ���
	//������ʼ����
	OSTaskCreate((OS_TCB * )&StartTaskTCB,		//������ƿ�
	             (CPU_CHAR * )"start task", 		//��������
	             (OS_TASK_PTR )start_task, 			//������
	             (void * )0,					//���ݸ��������Ĳ���
	             (OS_PRIO	  )START_TASK_PRIO,     //�������ȼ�
	             (CPU_STK * )&START_TASK_STK[0],	//�����ջ����ַ
	             (CPU_STK_SIZE)START_STK_SIZE / 10,	//�����ջ�����λ
	             (CPU_STK_SIZE)START_STK_SIZE,		//�����ջ��С
	             (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
	             (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
	             (void * )0,					//�û�����Ĵ洢��
	             (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR, //����ѡ��
	             (OS_ERR * )&err);				//��Ÿú�������ʱ�ķ���ֵ
	OS_CRITICAL_EXIT();	//�˳��ٽ���
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
	OSStatTaskCPUUsageInit(&err);  	//ͳ������
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
	CPU_IntDisMeasMaxCurReset();
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	//ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED, 1, &err);
#endif

	OS_CRITICAL_ENTER();	//�����ٽ���
	//����Transducer����
	OSTaskCreate((OS_TCB * )&TransducerTaskTCB,
	             (CPU_CHAR * )"Transducer task",
	             (OS_TASK_PTR )Transducer_task,
	             (void * )0,
	             (OS_PRIO	  )Transducer_TASK_PRIO,
	             (CPU_STK * )&Transducer_TASK_STK[0],
	             (CPU_STK_SIZE)Transducer_STK_SIZE / 10,
	             (CPU_STK_SIZE)Transducer_STK_SIZE,
	             (OS_MSG_QTY  )0,
	             (OS_TICK	  )0,
	             (void * )0,
	             (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR * )&err);

	//�����Զ�����
	OSTaskCreate((OS_TCB * )&AutoTaskTCB,
	             (CPU_CHAR * )"Auto task",
	             (OS_TASK_PTR )Auto_task,
	             (void * )0,
	             (OS_PRIO	  )Auto_TASK_PRIO,
	             (CPU_STK * )&Auto_TASK_STK[0],
	             (CPU_STK_SIZE)Auto_STK_SIZE / 10,
	             (CPU_STK_SIZE)Auto_STK_SIZE,
	             (OS_MSG_QTY  )0,
	             (OS_TICK	  )0,
	             (void * )0,
	             (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR * )&err);

	//���������������
	OSTaskCreate((OS_TCB * )&FloatTaskTCB,
	             (CPU_CHAR * )"float test task",
	             (OS_TASK_PTR )float_task,
	             (void * )0,
	             (OS_PRIO	  )FLOAT_TASK_PRIO,
	             (CPU_STK * )&FLOAT_TASK_STK[0],
	             (CPU_STK_SIZE)FLOAT_STK_SIZE / 10,
	             (CPU_STK_SIZE)FLOAT_STK_SIZE,
	             (OS_MSG_QTY  )0,
	             (OS_TICK	  )0,
	             (void * )0,
	             (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR * )&err);

	//��������������
	OSTaskCreate((OS_TCB * )&ScreenTaskTCB,
	             (CPU_CHAR * )"Screen task",
	             (OS_TASK_PTR )Screen_task,
	             (void * )0,
	             (OS_PRIO	  )Screen_TASK_PRIO,
	             (CPU_STK * )&Screen_TASK_STK[0],
	             (CPU_STK_SIZE)Screen_STK_SIZE / 10,
	             (CPU_STK_SIZE)Screen_STK_SIZE,
	             (OS_MSG_QTY  )0,
	             (OS_TICK	  )0,
	             (void * )0,
	             (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR * )&err);

	//PID
	OSTaskCreate((OS_TCB * )&PIDTaskTCB,
	             (CPU_CHAR * )"PID task",
	             (OS_TASK_PTR )PID_task,
	             (void * )0,
	             (OS_PRIO	  )PID_TASK_PRIO,
	             (CPU_STK * )&PID_TASK_STK[0],
	             (CPU_STK_SIZE)PID_STK_SIZE / 10,
	             (CPU_STK_SIZE)PID_STK_SIZE,
	             (OS_MSG_QTY  )0,
	             (OS_TICK	  )0,
	             (void * )0,
	             (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR * )&err);
	//Control
	OSTaskCreate((OS_TCB * )&ControlTaskTCB,
	             (CPU_CHAR * )"Control task",
	             (OS_TASK_PTR )Control_task,
	             (void * )0,
	             (OS_PRIO	  )Control_TASK_PRIO,
	             (CPU_STK * )&Control_TASK_STK[0],
	             (CPU_STK_SIZE)Control_STK_SIZE / 10,
	             (CPU_STK_SIZE)Control_STK_SIZE,
	             (OS_MSG_QTY  )0,
	             (OS_TICK	  )0,
	             (void * )0,
	             (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR * )&err);
	//DEMO
	OSTaskCreate((OS_TCB * )&DEMOTaskTCB,
	             (CPU_CHAR * )"DEMO task",
	             (OS_TASK_PTR )DEMO_task,
	             (void * )0,
	             (OS_PRIO	  )DEMO_TASK_PRIO,
	             (CPU_STK * )&DEMO_TASK_STK[0],
	             (CPU_STK_SIZE)DEMO_STK_SIZE / 10,
	             (CPU_STK_SIZE)DEMO_STK_SIZE,
	             (OS_MSG_QTY  )0,
	             (OS_TICK	  )0,
	             (void * )0,
	             (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR * )&err);
	//DEMO1
	OSTaskCreate((OS_TCB * )&DEMO1TaskTCB,
	             (CPU_CHAR * )"DEMO1 task",
	             (OS_TASK_PTR )DEMO1_task,
	             (void * )0,
	             (OS_PRIO	  )DEMO1_TASK_PRIO,
	             (CPU_STK * )&DEMO1_TASK_STK[0],
	             (CPU_STK_SIZE)DEMO1_STK_SIZE / 10,
	             (CPU_STK_SIZE)DEMO1_STK_SIZE,
	             (OS_MSG_QTY  )0,
	             (OS_TICK	  )0,
	             (void * )0,
	             (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR * )&err);
	//DEMO2
	OSTaskCreate((OS_TCB * )&DEMO2TaskTCB,
	             (CPU_CHAR * )"DEMO2 task",
	             (OS_TASK_PTR )DEMO2_task,
	             (void * )0,
	             (OS_PRIO	  )DEMO2_TASK_PRIO,
	             (CPU_STK * )&DEMO2_TASK_STK[0],
	             (CPU_STK_SIZE)DEMO2_STK_SIZE / 10,
	             (CPU_STK_SIZE)DEMO2_STK_SIZE,
	             (OS_MSG_QTY  )0,
	             (OS_TICK	  )0,
	             (void * )0,
	             (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR * )&err);

	//�����ֶ�����
	OSTaskCreate((OS_TCB * )&ManualTaskTCB,
	             (CPU_CHAR * )"Manual task",
	             (OS_TASK_PTR )Manual_task,
	             (void * )0,
	             (OS_PRIO	  )Manual_TASK_PRIO,
	             (CPU_STK * )&Manual_TASK_STK[0],
	             (CPU_STK_SIZE)Manual_STK_SIZE / 10,
	             (CPU_STK_SIZE)Manual_STK_SIZE,
	             (OS_MSG_QTY  )0,
	             (OS_TICK	  )0,
	             (void * )0,
	             (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR * )&err);

	OSTaskCreate((OS_TCB * )&WIFITaskTCB,
	             (CPU_CHAR * )"WIFI task",
	             (OS_TASK_PTR )WIFI_task,
	             (void * )0,
	             (OS_PRIO	  )WIFI_TASK_PRIO,
	             (CPU_STK * )&WIFI_TASK_STK[0],
	             (CPU_STK_SIZE)WIFI_STK_SIZE / 10,
	             (CPU_STK_SIZE)WIFI_STK_SIZE,
	             (OS_MSG_QTY  )0,
	             (OS_TICK	  )0,
	             (void * )0,
	             (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR * )&err);

	OSTaskCreate((OS_TCB * )&Task5_TaskTCB,
	             (CPU_CHAR * )"Task5 task",
	             (OS_TASK_PTR )Task5_task,
	             (void * )0,
	             (OS_PRIO	  )Task5_TASK_PRIO,
	             (CPU_STK * )&Task5_TASK_STK[0],
	             (CPU_STK_SIZE)Task5_STK_SIZE / 10,
	             (CPU_STK_SIZE)Task5_STK_SIZE,
	             (OS_MSG_QTY  )0,
	             (OS_TICK	  )0,
	             (void * )0,
	             (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
	             (OS_ERR * )&err);

	OS_TaskSuspend((OS_TCB *)&StartTaskTCB, &err);		//����ʼ����
	OS_CRITICAL_EXIT();	//�����ٽ���
}
//���Զ��л�
void Transducer_task(void *p_arg)
{
	p_arg = p_arg;
	HmiScreenControlMode = 1;
	while(1)
	{
		if(((SouZiDongQieHuan == 0) && (All_flag.flag_szd == 0)) || (PLC_OutPut[18] == 1))
		{
			All_flag.stopAsk = 1;
			All_flag.flag_tz = 1;
			All_flag.flag_szd = 1;
			speek("�ֶ�");
			HmiShouZiDongYinCang = 0;
			HmiScreenControlMode = 1;
			while(SouZiDongQieHuan == 0)
			{
				delay(0, 0, 0, 10);
			}
		}
		else if(((SouZiDongQieHuan == 0) && (All_flag.flag_szd == 1)) || (PLC_OutPut[17] == 1))
		{
			All_flag.stopAsk = 1;
			All_flag.flag_szd = 0;
			speek("�Զ�");
			HmiShouZiDongYinCang = 0;
			speed.jisu_speed = ZiDongJiSu;	//�Զ�һ��ʼûɨ���ر�֮ǰ�����ٶ�
			HmiScreenControlMode = 0;
			while(SouZiDongQieHuan == 0)
			{
				delay(0, 0, 0, 10);
			}
		}
		delay(0, 0, 0, 5); //��ʱ5ms
	}
}
//�Զ���ť���
void Auto_task(void *p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		delay(0, 0, 0, 5); //��ʱ5ms
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
u8 cy_time = 5;
void PID_task(void *p_arg)
{
	while(1)
	{
		delay(0, 0, 0, cy_time);
	}
}
//����������ص����澯���������λ��ͨѶ
void float_task(void *p_arg)
{
	while(1)
	{
		delay(0, 0, 0, 5); //��ʱ5ms
	}
}
//��������·�����̲�������
void Screen_task(void *p_arg)
{
	while(1)
	{
		delay(0, 0, 0, 10);
	}
}
//�Զ�ִ��·��������
void Task5_task(void *p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		delay(0, 0, 0, 5);
	}
}

//���Զ�ģʽ���ϴ���
float adc_dwq1, adc_dwq2, adc_pow;
void Control_task(void *p_arg)
{
	while(1)
	{
		adc_pow = After_filter[0] * 3.3 * 11 / 4096;
		adc_dwq1 = After_filter[1] *	3.3 / 4096;
		adc_dwq2 = After_filter[2] *	3.3 / 4096;
		delay(0, 0, 0, 5);
	}
}
//��������
void WIFI_task(void *p_arg)
{
	send3_buf[0] = 0x11;
	send3_buf[1] = 0x22;
	send6_buf[0] = 0x11;
	send6_buf[1] = 0x22;
	send2_buf[0] = 0x11;
	send2_buf[1] = 0x22;
	send5_buf[0] = 0x11;
	send5_buf[1] = 0x22;
	sendBuf[0] = 0x11;
	sendBuf[1] = 0x22;	
	while(1)
	{

		Uart3_Start_DMA_Tx(2);
		Uart6_Start_DMA_Tx(2);
		Uart2_Start_DMA_Tx(2);

		CAN1_Send_Msg(send2_buf,2);
		CAN2_Send_Msg(send2_buf,2);
//		Uart5_Start_DMA_Tx(2);//����5��DMA����ʱ�����CPU��λ������ԭ��δ�ҵ���DMA�����������ģ�����ͨ�ķ���û������
		Uart4_Start_DMA_Tx(2);
		delay(0, 0, 2, 0);
	}

}
//�ж�ƽ�ƻ���ת�Ƿ�λ��λ
u8 onway = 0;
void DEMO_task(void *p_arg)
{

	while(1)
	{
		speek("OK");
		BEEP = 0;
		LED1 = ~LED1;
		LED2 = ~LED2;
		LED3 = ~LED3;
		LED4 = ~LED4;
		delay(0, 0, 2, 0);
	}
}

//����
void DEMO1_task(void *p_arg)
{
	uint8_t tmp;
	int32_t ret = 0;
	uint8_t memsize[2][8] = {{2, 2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2, 2, 2}};
	//Host dependent peripheral initialized
	platform_init();
	// First of all, Should register SPI callback functions implemented by user for accessing WIZCHIP
	/* Critical section callback */
	reg_wizchip_cris_cbfunc(SPI_CrisEnter, SPI_CrisExit);	//ע���ٽ�������
	/* Chip selection call back */
#if   _WIZCHIP_IO_MODE_ == _WIZCHIP_IO_MODE_SPI_VDM_
	reg_wizchip_cs_cbfunc(SPI1_CS_Select, SPI1_CS_Deselect);//ע��SPIƬѡ�źź���
#elif _WIZCHIP_IO_MODE_ == _WIZCHIP_IO_MODE_SPI_FDM_
	reg_wizchip_cs_cbfunc(SPI1_CS_Select, SPI1_CS_Deselect);  // CS must be tried with LOW.
#else
#if (_WIZCHIP_IO_MODE_ & _WIZCHIP_IO_MODE_SIP_) != _WIZCHIP_IO_MODE_SIP_
#error "Unknown _WIZCHIP_IO_MODE_"
#else
	reg_wizchip_cs_cbfunc(wizchip_select, wizchip_deselect);
#endif
#endif
	/* SPI Read & Write callback function */
	reg_wizchip_spi_cbfunc(SPI1_ReadByte, SPI1_WriteByte);	//ע���д����

	/* WIZCHIP SOCKET Buffer initialize */
	if(ctlwizchip(CW_INIT_WIZCHIP, (void *)memsize) == -1)
	{
		printf("WIZCHIP Initialized fail.\r\n");
		while(1);
	}

	/* PHY link status check */
	do
	{
		if(ctlwizchip(CW_GET_PHYLINK, (void *)&tmp) == -1)
		{
			printf("Unknown PHY Link stauts.\r\n");
		}
	}
	while(tmp == PHY_LINK_OFF);

	/* Network initialization */
	network_init();
	
	while(1)
	{
		/* Loopback Test */
		// TCP server loopback test
		if( (ret = loopback_tcps(SOCK_TCPS, gDATABUF, 5000)) < 0) {
			printf("SOCKET ERROR : %ld\r\n", ret);
		}
    // UDP server loopback test
		if( (ret = loopback_udps(SOCK_UDPS, gDATABUF, 3000)) < 0) {
			printf("SOCKET ERROR : %ld\r\n", ret);
		}
		delay(0, 0, 0, 10);
	}
}
//ֹͣ
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
		delay(0, 0, 0, 5);
	}
}

/**
  * @brief  Intialize the network information to be used in WIZCHIP
  * @retval None
  */
void network_init(void)
{
	uint8_t tmpstr[6];
	CPU_ID[0] = *(vu32 *)(0x1FFF7A10);
	CPU_ID[1] = *(vu32 *)(0x1FFF7A14);
	CPU_ID[2] = *(vu32 *)(0x1FFF7A18);
	gWIZNETINFO.mac[0] = (CPU_ID[0] >> 16) & 0XFF;
	gWIZNETINFO.mac[1] = (CPU_ID[0] >> 8) & 0XFFF;
	gWIZNETINFO.mac[2] = CPU_ID[0] & 0XFF;
	gWIZNETINFO.mac[3] = (CPU_ID[1] >> 16) & 0XFF;
	gWIZNETINFO.mac[4] = (CPU_ID[1] >> 8) & 0XFFF;
	gWIZNETINFO.mac[5] = CPU_ID[1] & 0XFF;
	
	ctlnetwork(CN_SET_NETINFO, (void *)&gWIZNETINFO);
	ctlnetwork(CN_GET_NETINFO, (void *)&gWIZNETINFO);

	// Display Network Information
	ctlwizchip(CW_GET_ID, (void *)tmpstr);
	printf("\r\n=== %s NET CONF ===\r\n", (char *)tmpstr);
	printf("MAC: %02X:%02X:%02X:%02X:%02X:%02X\r\n", gWIZNETINFO.mac[0], gWIZNETINFO.mac[1], gWIZNETINFO.mac[2],
	       gWIZNETINFO.mac[3], gWIZNETINFO.mac[4], gWIZNETINFO.mac[5]);
	printf("SIP: %d.%d.%d.%d\r\n", gWIZNETINFO.ip[0], gWIZNETINFO.ip[1], gWIZNETINFO.ip[2], gWIZNETINFO.ip[3]);
	printf("GAR: %d.%d.%d.%d\r\n", gWIZNETINFO.gw[0], gWIZNETINFO.gw[1], gWIZNETINFO.gw[2], gWIZNETINFO.gw[3]);
	printf("SUB: %d.%d.%d.%d\r\n", gWIZNETINFO.sn[0], gWIZNETINFO.sn[1], gWIZNETINFO.sn[2], gWIZNETINFO.sn[3]);
	printf("DNS: %d.%d.%d.%d\r\n", gWIZNETINFO.dns[0], gWIZNETINFO.dns[1], gWIZNETINFO.dns[2], gWIZNETINFO.dns[3]);
	printf("======================\r\n");
}

/**
  * @brief  Loopback Test Example Code using ioLibrary_BSD
  * @retval None
  */
int32_t loopback_tcps(uint8_t sn, uint8_t *buf, uint16_t port)
{
	int32_t ret;
	uint16_t size = 0, sentsize = 0;
	switch(getSn_SR(sn))
	{
		case SOCK_ESTABLISHED :
			if(getSn_IR(sn) & Sn_IR_CON)
			{
				printf("%d:Connected\r\n", sn);
				setSn_IR(sn, Sn_IR_CON);
			}
			if((size = getSn_RX_RSR(sn)) > 0)
			{
				if(size > DATA_BUF_SIZE) { size = DATA_BUF_SIZE; }
				ret = recv(sn, buf, size);
				if(ret <= 0) { return ret; }
				sentsize = 0;
				while(size != sentsize)
				{
					ret = send(sn, buf + sentsize, size - sentsize);
					if(ret < 0)
					{
						close(sn);
						return ret;
					}
					sentsize += ret; // Don't care SOCKERR_BUSY, because it is zero.
				}
			}
			break;
		case SOCK_CLOSE_WAIT :
			printf("%d:CloseWait\r\n", sn);
			if((ret = disconnect(sn)) != SOCK_OK) { return ret; }
			printf("%d:Closed\r\n", sn);
			break;
		case SOCK_INIT :
			printf("%d:Listen, port [%d]\r\n", sn, port);
			if( (ret = listen(sn)) != SOCK_OK) { return ret; }
			break;
		case SOCK_CLOSED:
			printf("%d:LBTStart\r\n", sn);
			if((ret = socket(sn, Sn_MR_TCP, port, 0x00)) != sn)
			{ return ret; }
			printf("%d:Opened\r\n", sn);
			break;
		default:
			break;
	}
	return 1;
}

/**
  * @brief  Loopback Test Example Code using ioLibrary_BSD
  * @retval None
  */
int32_t loopback_udps(uint8_t sn, uint8_t *buf, uint16_t port)
{
	int32_t  ret;
	uint16_t size, sentsize;
	uint8_t  destip[4];
	uint16_t destport;
	//uint8_t  packinfo = 0;
	switch(getSn_SR(sn))
	{
		case SOCK_UDP :
			if((size = getSn_RX_RSR(sn)) > 0)
			{
				if(size > DATA_BUF_SIZE) { size = DATA_BUF_SIZE; }
				ret = recvfrom(sn, buf, size, destip, (uint16_t *)&destport);
				if(ret <= 0)
				{
					printf("%d: recvfrom error. %ld\r\n", sn, ret);
					return ret;
				}
				size = (uint16_t) ret;
				sentsize = 0;
				while(sentsize != size)
				{
					ret = sendto(sn, buf + sentsize, size - sentsize, destip, destport);
					if(ret < 0)
					{
						printf("%d: sendto error. %ld\r\n", sn, ret);
						return ret;
					}
					sentsize += ret; // Don't care SOCKERR_BUSY, because it is zero.
				}
			}
			break;
		case SOCK_CLOSED:
			printf("%d:LBUStart\r\n", sn);
			if((ret = socket(sn, Sn_MR_UDP, port, 0x00)) != sn)
			{ return ret; }
			printf("%d:Opened, port [%d]\r\n", sn, port);
			break;
		default :
			break;
	}
	return 1;
}
/**
  * @brief  Loopback Test Example Code using ioLibrary_BSD
  * @retval None
  */
void platform_init(void)
{
	printf("\x0c");
	printf("\x0c");//�����ն�����
	printf("\033[1;40;32m");//���ó����ն˱���Ϊ��ɫ���ַ�Ϊ��ɫ
	printf("\r\n*******************************************************************************");
	printf("\r\n************************ Copyright 2009-2018, EmbedNet ************************");
	printf("\r\n*************************** http://www.embed-net.com **************************");
	printf("\r\n***************************** All Rights Reserved *****************************");
	printf("\r\n*******************************************************************************");
	printf("\r\n");
}
