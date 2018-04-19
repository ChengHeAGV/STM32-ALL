#include "sys.h"

u8  USART6_TX_BUF[100],car_statu=0,dir=0;//0为正向即触摸屏方向，1为反向

u8 CAN1_Sebuf[5]={1,0,1,0,0x55},fencha_dir=0,tubian_num = 0,XuanZhuanNUM=0,PingYiNum=0;

u16 keynumber=0;

u8 ld_juli=40,Manual_juli=40,Jhwai_switch=1;//雷达蔽障距离与开关

float Cdh1_Inc=0,ADC_POWER;

battery_data lidian={0,8179,0};
flag All_flag;
sudu speed={200,130,100,0,0,0.0};
void u6_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART6_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART6_TX_BUF);//此次发送数据的长度
	for(j=0;j<i;j++)//循环发送数据
	{
	  while(USART_GetFlagStatus(USART6,USART_FLAG_TC)==RESET);  //等待上次传输完成 
		USART_SendData(USART6,(uint8_t)USART6_TX_BUF[j]); 	 //发送数据到串口6 
	}	
}
//启动
//dir为0，方向为正方向触摸屏方向
void start(void)
{
	car_statu = 1;	
	All_flag.flag_qd = 1;
	Moter_EnableAll();
	if(dir == 0)
	{		
		QJ();
	}
	else if(dir == 1)
	{
		HT();				
	}
	else if(dir == 2)
	{
		ZY();
	}
	else if(dir == 3)
	{
		YY();
	}
	else if(dir == 4)
	{
		ZX();
	}
	else if(dir == 5)
	{
		YX();
	}
}
//停止
void stop(void)
{
	MotoStop(5);
	All_flag.flag_qd = 0;car_statu = 0;	
}
//与继电器板通讯
void CanSend_data(u8 dir)
{
	if(dir == 1)//前进
	{
		CAN1_Sebuf[0] = 1;CAN1_Sebuf[1] = 0;
		CAN1_Sebuf[2] = 1;CAN1_Sebuf[3] = 0;
		CAN1_Send_Msg(CAN1_Sebuf,4);		
	}
	else if(dir == 2)//后退
	{
		CAN1_Sebuf[0] = 0;CAN1_Sebuf[1] = 1;
		CAN1_Sebuf[2] = 0;CAN1_Sebuf[3] = 1;
		CAN1_Send_Msg(CAN1_Sebuf,4);		
	}
	else if(dir == 3)//左移
	{
		CAN1_Sebuf[0] = 0;CAN1_Sebuf[1] = 0;
		CAN1_Sebuf[2] = 1;CAN1_Sebuf[3] = 1;
		CAN1_Send_Msg(CAN1_Sebuf,4);		
	}
	else if(dir == 4)//右移
	{
		CAN1_Sebuf[0] = 1;CAN1_Sebuf[1] = 1;
		CAN1_Sebuf[2] = 0;CAN1_Sebuf[3] = 0;
		CAN1_Send_Msg(CAN1_Sebuf,4);		
	}
	else if(dir == 5)//左上
	{
		CAN1_Sebuf[0] = 1;//4
		CAN1_Sebuf[1] = 0;//3
		CAN1_Sebuf[2] = 1;//2
		CAN1_Sebuf[3] = 0;//1
		CAN1_Send_Msg(CAN1_Sebuf,4);		
	}
	else if(dir == 6)//左下
	{
		CAN1_Sebuf[0] = 0;CAN1_Sebuf[1] = 0;
		CAN1_Sebuf[2] = 0;CAN1_Sebuf[3] = 1;
		CAN1_Send_Msg(CAN1_Sebuf,4);		
	}
	else if(dir == 7)//右上
	{
		CAN1_Sebuf[0] = 1;CAN1_Sebuf[1] = 0;
		CAN1_Sebuf[2] = 1;CAN1_Sebuf[3] = 0;
		CAN1_Send_Msg(CAN1_Sebuf,4);		
	}
	else if(dir == 8)//右下
	{
		CAN1_Sebuf[0] = 0;CAN1_Sebuf[1] = 1;
		CAN1_Sebuf[2] = 0;CAN1_Sebuf[3] = 0;
		CAN1_Send_Msg(CAN1_Sebuf,4);		
	}
	else if(dir == 9)//左旋
	{
		CAN1_Sebuf[0] = 1;CAN1_Sebuf[1] = 1;
		CAN1_Sebuf[2] = 1;CAN1_Sebuf[3] = 1;
		CAN1_Send_Msg(CAN1_Sebuf,4);		
	}
	else if(dir == 10)//右旋
	{
		CAN1_Sebuf[0] = 0;CAN1_Sebuf[1] = 0;
		CAN1_Sebuf[2] = 0;CAN1_Sebuf[3] = 0;
		CAN1_Send_Msg(CAN1_Sebuf,4);		
	}
}
//前进
void QJ(void)
{	
	CanSend_data(1);
}
//后退
void HT(void)
{
	CanSend_data(2);	
}
//左移
void ZY(void)
{	
	CanSend_data(3);
	Motor_SetVul(1,speed.pingyi_speed);
	Motor_SetVul(2,speed.pingyi_speed);
	Motor_SetVul(3,speed.pingyi_speed);
	Motor_SetVul(4,speed.pingyi_speed);	
}
//右移
void YY(void)
{		
	CanSend_data(4);
	Motor_SetVul(1,speed.pingyi_speed);
	Motor_SetVul(2,speed.pingyi_speed);
	Motor_SetVul(3,speed.pingyi_speed);
	Motor_SetVul(4,speed.pingyi_speed);	
}

//右旋	
void YX()
{	
	CanSend_data(10);
	Motor_SetVul(1,speed.xunzhuan_speed);
	Motor_SetVul(2,speed.xunzhuan_speed);
	Motor_SetVul(3,speed.xunzhuan_speed);
	Motor_SetVul(4,speed.xunzhuan_speed);
}
//左旋
void ZX()
{	
	CanSend_data(9);
	Motor_SetVul(1,speed.xunzhuan_speed);
	Motor_SetVul(2,speed.xunzhuan_speed);
	Motor_SetVul(3,speed.xunzhuan_speed);
	Motor_SetVul(4,speed.xunzhuan_speed);
}

//延时函数
void delay(u32 h,u32 m,u32 s,u32 ms)
{
	OS_ERR err;
	OSTimeDlyHMSM(h,m,s,ms,OS_OPT_TIME_HMSM_STRICT,&err);
}
//用户参数设置与存储
void UserConfigInit(void)
{
	LED4=0;
	W25QXX_Init();			//W25QXX初始化
	LED4=1;
	while(W25QXX_ReadID()!=W25Q128)//检测不到W25Q128，LED闪烁
	{
		LED4=~LED4;//DS0闪烁
		delay(0, 0,0 , 100);
	}
	LED4=0;
	
	//获取所有系统参数
	GetAllParameterFromSystem();

	if(SystemParameter[0]!=6)
	{
		//判断标志位
		SystemParameter[0]=6;
		
		//备用
		SystemParameter[1]=0;
		SystemParameter[2]=0;
		SystemParameter[3]=0;
		SystemParameter[4]=0;
		SystemParameter[5]=0;	
		
		SystemParameter[6] = 1;	//路径号		
		SystemParameter[7] = 1;	//流程号
		SystemParameter[8] = 0;	//任务号	
		//档位速度
		SystemParameter[9]=50;
		SystemParameter[10]=150;		
		SystemParameter[11]=250;
		SystemParameter[12]=0;		
		SystemParameter[13]=0;
		//手动速度
		SystemParameter[14] = 200;
		//自动速度
		SystemParameter[15] = 200;
		
		//手动避障开关		
		SystemParameter[16] = 1;
		//语音开关		
		SystemParameter[17] = 1;
		
		//语音音量		
		SystemParameter[18] = 2;
		
		//PID调试周期		
		SystemParameter[19] = 5;			
		//P		
		SystemParameter[20] = 50;			
		//I		
		SystemParameter[21] = 3;		
		//D		
		SystemParameter[22] = 2;
		//前后避障距离		
		SystemParameter[23] = 3;
		
		//路径总数
		SystemParameter[24] = RouteNum;
		
		//车号
		SystemParameter[25] = 1;	
			
		SystemParameter[26] = 0;
		SystemParameter[27] = 0;
		SystemParameter[28] = 0;		
		SystemParameter[29] = 0;
		SystemParameter[30] = 0;
		SystemParameter[31] = 0;		
		SystemParameter[32] = 0;
		SystemParameter[33] = 0;
		SystemParameter[34] = 0;		
		SystemParameter[35] = 0;
		SystemParameter[36] = 0;
		SystemParameter[37] = 0;		
		SystemParameter[38] = 0;
		SystemParameter[39] = 0;
		SystemParameter[40] = 0;
		SystemParameter[41] = 0;		
		SystemParameter[42] = 0;
		SystemParameter[43] = 0;
		SystemParameter[44] = 0;		
		SystemParameter[45] = 0;
		SystemParameter[46] = 0;
		SystemParameter[47] = 0;
		SystemParameter[48] = 0;		
		SystemParameter[49] = 0;
		SystemParameter[50] = 0;
		SystemParameter[51] = 0;
		SystemParameter[52] = 0;
		SystemParameter[53] = 0;
		SystemParameter[54] = 0;		
		SystemParameter[55] = 0;
		SystemParameter[56] = 0;
		SystemParameter[57] = 0;
		SystemParameter[58] = 0;
		SystemParameter[59] = 0;
		SystemParameter[60] = 0;		
		SystemParameter[61] = 0;
		SystemParameter[62] = 0;
		SystemParameter[63] = 0;
		SystemParameter[64] = 0;
		SystemParameter[65] = 0;		
		SystemParameter[66] = 0;
		SystemParameter[67] = 0;
		SystemParameter[68] = 0;
		SystemParameter[69] = 0;
		SystemParameter[70] = 0;
		SystemParameter[71] = 0;		
		SystemParameter[72] = 0;
		SystemParameter[73] = 0;
		SystemParameter[74] = 0;
		SystemParameter[75] = 0;
		SystemParameter[76] = 0;		
		SystemParameter[77] = 0;
		SystemParameter[78] = 0;
		SystemParameter[79] = 0;
		SystemParameter[80] = 0;
		SystemParameter[81] = 0;
		SystemParameter[82] = 0;
		SystemParameter[83] = 0;
		SystemParameter[84] = 0;
		SystemParameter[85] = 0;
		SystemParameter[86] = 0;
		SystemParameter[87] = 0;
		SystemParameter[88] = 0;
		SystemParameter[89] = 0;
		SystemParameter[90] = 0;
		SystemParameter[91] = 0;
		SystemParameter[92] = 0;
		SystemParameter[93] = 0;
		SystemParameter[94] = 0;
		SystemParameter[95] = SystemParaNum;
		SystemParameter[96] = StaiionInfor;
		SystemParameter[97] = StepInfor;		
		SystemParameter[98] = 500;
		SystemParameter[99] = 500;
		SystemParameter[100] = 0;		
		//存储所有系统参数
		SetAllParameterToSystem();
		
		//清除路径包含站点数
		memset(RouteStationNum,0,RouteNum);
		//保存所有路径包含的站点数
		SetAllStationNum();
		
		//清除流程包含步数
		memset(ProcessStepNum,0,ProcessNum);
		//保存所有流程包含的步数
		SetAllStepNum();
	}
	
	//初始化参数
	HmiRouteNum = SystemParameter[6];   //路径号
	HmiProcessNum = SystemParameter[7]; //流程号
//	HmiTask = SystemParameter[8]; //任务号
	
	HmiAutoReload();
	
	//刷新速度
	PLC_Data[22] =  SystemParameter[9];//慢速
	PLC_Data[23] =  SystemParameter[10];//中速
	PLC_Data[24] =  SystemParameter[11];//快速

	PLC_Data[1] = 0;	//当前地标号
	PLC_OutPut[0] = 0;//默认不显示自动/手动
	PLC_OutPut[1] = 0;//默认不显示停留时间
	PLC_OutPut[2] = 0;//默认不不可以输入，插入站点时可以输入
	HmiTask = 0;
	
	
	SouDongSuDu = SystemParameter[14];
	ZiDongJiSu = SystemParameter[15];
	SouDongBiZhang = SystemParameter[16];
	YuYinKaiGuan = SystemParameter[17];
	YinLiang = SystemParameter[18];
	
	//语音模式初始化
	if(YinLiang == 0)
	{
		speek("[v1]");//默认低音量
		delay(0,0,0,500);
	}
	else if(YinLiang == 1)
	{
		speek("[v5]");//默认中音量
		delay(0,0,0,500);
	}
	else
	{
		speek("[v9]");//默认高音量
		delay(0,0,0,500);
	}
	speek("[g2]");//默认中英混读
	
	PIDZhouQi = SystemParameter[19];
	SPID_P = SystemParameter[20];
	SPID_I = SystemParameter[21];
	SPID_D = SystemParameter[22];
	QianHouJuLi = SystemParameter[23];
	LiuChengZongShu = SystemParameter[98];
	LuJingZongShu = SystemParameter[99];
	CheHao	= SystemParameter[25];
	
	//获取路径包含站点数
	GetRouteStationNum(HmiRouteNum);

	//获取当前路径信息
	GetRouteData(HmiRouteNum);
		
	//获取及更新流程数据
	GetProcessData();
}
//手动模式电机PWM设置
void Motor_Zzhuan(u8 Motor,u32 PWM)
{
	switch(Motor)
	{
		case 1:	
			PDout(4)=1;//为0时停止，为1时启动					
			TIM_SetCompare1(TIM4,1000-PWM);		
		break;
		case 2:
			PDout(3)=1;
			TIM_SetCompare2(TIM4,1000-PWM);
		break;
		case 3:
			PDout(1)=1;
			TIM_SetCompare3(TIM4,1000-PWM);
		break;
		case 4:
			PDout(0)=1;
			TIM_SetCompare4(TIM4,1000-PWM);
		break;
		default:
		break;
	}
}

void Motor_Fzhuan(u8 Motor,u32 PWM)
{
	switch(Motor)
	{
		case 1:	
			PDout(4)=1;			
			TIM_SetCompare1(TIM4,1000-PWM);
		break;
		case 2:
			PDout(3)=1;
			TIM_SetCompare2(TIM4,1000-PWM);
		break;
		case 3:
			PDout(1)=1;
			TIM_SetCompare3(TIM4,1000-PWM);
		break;
		case 4:
			PDout(0)=1;
			TIM_SetCompare4(TIM4,1000-PWM);
		break;
		default:
		break;
	}
}
//自动模式设置电机PWM值
void Motor_SetVul(u8 Motor,u32 PWM)
{
	switch(Motor)
	{
		case 1:				
			TIM_SetCompare1(TIM4,1000-PWM);
		break;
		case 2:
			TIM_SetCompare2(TIM4,1000-PWM);
		break;
		case 3:
			TIM_SetCompare3(TIM4,1000-PWM);
		break;
		case 4:
			TIM_SetCompare4(TIM4,1000-PWM);
		break;
		default:
		break;
	}
}
void Moter_EnableAll(void)
{
	PDout(4)=1;//使能
	PDout(3)=1;//使能		
	PDout(1)=1;//使能		
	PDout(0)=1;//使能	
}
void MotoStop(u8 num)
{
	if(num==1)
	{
		PDout(4)=0;//使能
		TIM_SetCompare1(TIM4,0);
	}
	else if(num==2)
	{
		PDout(3)=0;//使能
		TIM_SetCompare2(TIM4,0);		
	}
	else if(num==3)
	{
		PDout(1)=0;//使能	
		TIM_SetCompare3(TIM4,0);		
	}
	else if(num==4)
	{

		PDout(0)=0;//使能
		TIM_SetCompare4(TIM4,0);
	}
	else
	{
		car_statu = 0;
		PDout(4)=0;//使能
		PDout(3)=0;//使能		
		PDout(1)=0;//使能		
		PDout(0)=0;//使能
		TIM_SetCompare1(TIM4,0);
		TIM_SetCompare2(TIM4,0);
		TIM_SetCompare3(TIM4,0);
		TIM_SetCompare4(TIM4,0);
	}
}

//磁导航PID调节
void PID_Adjust(u16 j_speed,float kp,float ki,float kd)
{
	u8 num = 0;
	PID.Kp = kp;
	PID.Ki = ki;
	PID.Kd = kd; 
	
	if(dir == 0)
	{
		while(front_cdh16.Num==0&&num!=100)
		{
			num++;
			delay(0,0,0,10);
		}			
		if(front_cdh16.Num==0)
		{
			MotoStop(5);
			HmiTaskState = 4;
		}
		else
		{
			HmiTaskState = 5;
			Cdh1_Inc = PosPIDCalc(front_cdh16.Distance);
		
			speed.moter1_speed = j_speed+Cdh1_Inc;
			speed.moter2_speed = j_speed-Cdh1_Inc;

			if(abs(front_cdh16.Distance)>4)
			{
				if(Cdh1_Inc<0)
				{
					speed.moter3_speed = j_speed;
					speed.moter4_speed = j_speed-Cdh1_Inc;						
				}
				else
				{
					speed.moter3_speed = j_speed+Cdh1_Inc;
					speed.moter4_speed = j_speed;						
				}
			}
			else
			{
				speed.moter3_speed = j_speed;
				speed.moter4_speed = j_speed;					
			}
			if(speed.moter1_speed>1000)	speed.moter1_speed = 1000;
			if(speed.moter2_speed>1000)	speed.moter2_speed = 1000;
			if(speed.moter3_speed>1000)	speed.moter3_speed = 1000;
			if(speed.moter4_speed>1000)	speed.moter4_speed = 1000;
			if(speed.moter1_speed<0)	speed.moter1_speed = 0;
			if(speed.moter2_speed<0)	speed.moter2_speed = 0;
			if(speed.moter3_speed<0)	speed.moter3_speed = 0;
			if(speed.moter4_speed<0)	speed.moter4_speed = 0;

			Motor_SetVul(1,speed.moter1_speed);
			Motor_SetVul(2,speed.moter2_speed);
			Motor_SetVul(3,speed.moter3_speed);
			Motor_SetVul(4,speed.moter4_speed);								
		}
	}
	else if(dir == 1)
	{
		while(back_cdh16.Num==0&&num!=100)
		{
			num++;
			delay(0,0,0,10);
		}
		if(back_cdh16.Num==0)
		{
			MotoStop(5);
			HmiTaskState = 4;
		}
		else
		{
			HmiTaskState = 5;
			Cdh1_Inc = PosPIDCalc(back_cdh16.Distance);
		
			speed.moter3_speed = j_speed-Cdh1_Inc;
			speed.moter4_speed = j_speed+Cdh1_Inc;
			if(abs(back_cdh16.Distance)>4)
			{
				if(Cdh1_Inc<0)
				{
					speed.moter1_speed = j_speed;
					speed.moter2_speed = j_speed+Cdh1_Inc;						
				}
				else
				{
					speed.moter1_speed = j_speed-Cdh1_Inc;
					speed.moter2_speed = j_speed;						
				}
			}
			else
			{
				speed.moter1_speed = j_speed;
				speed.moter2_speed = j_speed;					
			}
			if(speed.moter1_speed>1000)	speed.moter1_speed = 1000;
			if(speed.moter2_speed>1000)	speed.moter2_speed = 1000;
			if(speed.moter3_speed>1000)	speed.moter3_speed = 1000;
			if(speed.moter4_speed>1000)	speed.moter4_speed = 1000;
			if(speed.moter1_speed<0)	speed.moter1_speed = 0;
			if(speed.moter2_speed<0)	speed.moter2_speed = 0;
			if(speed.moter3_speed<0)	speed.moter3_speed = 0;
			if(speed.moter4_speed<0)	speed.moter4_speed = 0;
		
			Motor_SetVul(1,speed.moter1_speed);
			Motor_SetVul(2,speed.moter2_speed);
			Motor_SetVul(3,speed.moter3_speed);
			Motor_SetVul(4,speed.moter4_speed);				
		}

	}
}
//清空数组
void Clear_ReceBuf(u8 num)
{
	if(num==2)
	{
		memset(rece2_buf,0,rece2_index);
	}
	else if(num==6)
	{
		memset(rece6_buf,0,sizeof(rece6_buf));
	}
}
//与锂电池通讯
void LiDian_send(void)
{
//	7E 32 35 30 30 34 36 34 32 45 30 30 32 30 31 46 44 33 31 0D  获取模拟量  （PACK = 0x01）
	send3_buf[0] = 0x7e;
	send3_buf[1] = 0x32;
	send3_buf[2] = 0x35;
	send3_buf[3] = 0x30;
	send3_buf[4] = 0x30;
	send3_buf[5] = 0x34;
	send3_buf[6] = 0x36;
	send3_buf[7] = 0x34;
	send3_buf[8] = 0x32;
	send3_buf[9] = 0x45;
	send3_buf[10] = 0x30;
	send3_buf[11] = 0x30;
	send3_buf[12] = 0x32;
	send3_buf[13] = 0x30;
	send3_buf[14] = 0x31;
	send3_buf[15] = 0x46;
	send3_buf[16] = 0x44;
	send3_buf[17] = 0x33;
	send3_buf[18] = 0x31;
	send3_buf[19] = 0x0D;
	Uart3_Start_DMA_Tx(20);
}
//将16进制转换为字符
u8 HexToChar(u8 bChar)
{
	if((bChar>=0x30)&&(bChar<=0x39))
	{
		bChar -= 0x30;
	}
	else if((bChar>=0x41)&&(bChar<=0x46))
	{
		bChar -= 0x37;
	}
	else if((bChar>=0x61)&&(bChar<=0x66))
	{
		bChar -= 0x57;
	}
	else 
	{
		bChar = 0xff;
	}
	return bChar;
}
//将浮点数转换为16进制数
long FloatTohex(float HEX)
{
	return *( long *)&HEX;//注意此处将long型指针强行指向浮点型HEX的地址
}
//将16进制转化为浮点数
float HexTofloat(long HEX)
{
	return *( float *)&HEX;
}
//执行站点动作
void StationAction(u16 num)
{
	HmiNextRfidNum = NowRouteInfor[num][5];
	tubian_num = 0;
	while(keynumber==0||keynumber!=NowRouteInfor[num][5])	//扫到地标，是目标值的话则跳出while
	{		
		if(NowRouteInfor[num][2]>0)
		{
			if(NowRouteInfor[num][2] == tubian_num)
			{
				keynumber = NowRouteInfor[num][5];
			}
		}
		HmiRfidNum = keynumber;
		osdelay_ms(20);			
	}	
	
	XuanZhuanNUM = 0;
	PingYiNum = 0;		
	
	//避障开关		
	Jhwai_switch=NowRouteInfor[num][0];
	//更新到车体
	//速度
	if(NowRouteInfor[num][4] == 0)	speed.jisu_speed=PLC_Data[22];
	if(NowRouteInfor[num][4] == 1)	speed.jisu_speed=PLC_Data[23];
	if(NowRouteInfor[num][4] == 2)	speed.jisu_speed=PLC_Data[24];	
	
	//运动方向
	//正向
	if(NowRouteInfor[num][6]==0)
	{
		All_flag.stopAsk=1 ;
		while(All_flag.stopAsk) 
		{
			delay(0,0,0,10);
		} 
		dir = 0;						
		if(NowRouteInfor[num][7]==0)
		{
			delay(0,0,NowRouteInfor[num][8],0);
			All_flag.startAsk=1 ;
			while(All_flag.startAsk)
			{
				delay(0,0,0,10);
			}
		}			
	}
	//通过
	else if(NowRouteInfor[num][6]==1)
	{

	}
	//停车
	else if(NowRouteInfor[num][6]==2)
	{
		All_flag.stopAsk=1 ;
		while(All_flag.stopAsk) 
		{
			delay(0,0,0,10);
		}                     
	}
	
	//反向
	else if(NowRouteInfor[num][6]==3)
	{
		All_flag.stopAsk=1 ;
		while(All_flag.stopAsk)
		{
			delay(0,0,0,10);
		}                        
		dir = 1;
		if(NowRouteInfor[num][7]==0)
		{
			delay(0,0,NowRouteInfor[num][8],0);
			All_flag.startAsk=1 ;
			while(All_flag.startAsk)
			{
				delay(0,0,0,10);
			}
		}
	}
	 
	//左移正向
	else if(NowRouteInfor[num][6]==4)
	{
		All_flag.stopAsk=1 ;
		while(All_flag.stopAsk)
		{
			delay(0,0,0,10);
		}
		dir=2;
		if(NowRouteInfor[num][7]==0)
		{
			delay(0,0,NowRouteInfor[num][8],0);
			All_flag.startAsk=1 ;
			while(PingYiNum != 8)
			{
				delay(0,0,0,10);
			}
			dir=0;
			MotoStop(5);
			delay(0,0,NowRouteInfor[num][8],0);	
			if(NowRouteInfor[num][4] == 0)	speed.jisu_speed=PLC_Data[22];
			if(NowRouteInfor[num][4] == 1)	speed.jisu_speed=PLC_Data[23];
			if(NowRouteInfor[num][4] == 2)	speed.jisu_speed=PLC_Data[24];			
			All_flag.startAsk=1 ;
			while(All_flag.startAsk)
			{
				delay(0,0,0,10);
			}											
		}
	}
	
	//左移反向
   else if(NowRouteInfor[num][6]==5)
	{
		All_flag.stopAsk=1 ;
		while(All_flag.stopAsk)
		{
			delay(0,0,0,10);
		}
		dir=2;
		if(NowRouteInfor[num][7]==0)
		{
			delay(0,0,NowRouteInfor[num][8],0);
			All_flag.startAsk=1 ;
			while(PingYiNum != 8)
			{
				delay(0,0,0,10);
			}
			dir=1;
			MotoStop(5);
			delay(0,0,NowRouteInfor[num][8],0);	
			if(NowRouteInfor[num][4] == 0)	speed.jisu_speed=PLC_Data[22];
			if(NowRouteInfor[num][4] == 1)	speed.jisu_speed=PLC_Data[23];
			if(NowRouteInfor[num][4] == 2)	speed.jisu_speed=PLC_Data[24];			
			All_flag.startAsk=1 ;
			while(All_flag.startAsk)
			{
				delay(0,0,0,10);
			}											
		}						
	}
	
	//左移停止
   else if(NowRouteInfor[num][6]==6)
	{
		All_flag.stopAsk=1 ;
		while(All_flag.stopAsk)
		{
			delay(0,0,0,10);
		}
		dir=2;
		All_flag.startAsk=1 ;
		while(PingYiNum != 8)
		{
			delay(0,0,0,10);
		}
		dir=0;
		MotoStop(5);
		delay(0,0,NowRouteInfor[num][8],0);	
		if(NowRouteInfor[num][4] == 0)	speed.jisu_speed=PLC_Data[22];
		if(NowRouteInfor[num][4] == 1)	speed.jisu_speed=PLC_Data[23];
		if(NowRouteInfor[num][4] == 2)	speed.jisu_speed=PLC_Data[24];							
	}
	
	//右移正向
	else if(NowRouteInfor[num][6]==7)
	{
		All_flag.stopAsk=1 ;
		while(All_flag.stopAsk)
		{
			delay(0,0,0,10);
		}
		dir=3;
		if(NowRouteInfor[num][7]==0)
		{
			delay(0,0,NowRouteInfor[num][8],0);
			All_flag.startAsk=1 ;
			while(PingYiNum != 8)
			{
				delay(0,0,0,10);
			}
			dir=0;
			MotoStop(5);
			delay(0,0,NowRouteInfor[num][8],0);	
			if(NowRouteInfor[num][4] == 0)	speed.jisu_speed=PLC_Data[22];
			if(NowRouteInfor[num][4] == 1)	speed.jisu_speed=PLC_Data[23];
			if(NowRouteInfor[num][4] == 2)	speed.jisu_speed=PLC_Data[24];			
			All_flag.startAsk=1 ;
			while(All_flag.startAsk)
			{
				delay(0,0,0,10);
			}										
		}						
	}
	
	//右移反向
	else if(NowRouteInfor[num][6]==8)
	{
		All_flag.stopAsk=1 ;
		while(All_flag.stopAsk)
		{
			delay(0,0,0,10);
		}
		dir=3;
		if(NowRouteInfor[num][7]==0)
		{
			delay(0,0,NowRouteInfor[num][8],0);
			All_flag.startAsk=1 ;
			while(PingYiNum != 8)
			{
				delay(0,0,0,10);
			}
			dir=1;
			MotoStop(5);
			delay(0,0,NowRouteInfor[num][8],0);	
			if(NowRouteInfor[num][4] == 0)	speed.jisu_speed=PLC_Data[22];
			if(NowRouteInfor[num][4] == 1)	speed.jisu_speed=PLC_Data[23];
			if(NowRouteInfor[num][4] == 2)	speed.jisu_speed=PLC_Data[24];			
			All_flag.startAsk=1 ;
			while(All_flag.startAsk)
			{
				delay(0,0,0,10);
			}											
		}
	}                    
	//右移停止
	else if(NowRouteInfor[num][6]==9)
	{
		All_flag.stopAsk=1 ;
		while(All_flag.stopAsk)
		{
			delay(0,0,0,10);
		}
		dir=3;
		All_flag.startAsk=1 ;
		while(PingYiNum != 8)
		{
			delay(0,0,0,10);
		}
		dir=0;
		MotoStop(5);
		delay(0,0,NowRouteInfor[num][8],0);	
		if(NowRouteInfor[num][4] == 0)	speed.jisu_speed=PLC_Data[22];
		if(NowRouteInfor[num][4] == 1)	speed.jisu_speed=PLC_Data[23];
		if(NowRouteInfor[num][4] == 2)	speed.jisu_speed=PLC_Data[24];							
	} 
	//左旋正向
	else if(NowRouteInfor[num][6]==10)
	{		
		All_flag.stopAsk=1 ;
		while(All_flag.stopAsk)
		{
			delay(0,0,0,10);
		}
		dir=4;
		if(NowRouteInfor[num][7]==0)
		{
			delay(0,0,NowRouteInfor[num][8],0);
			
			All_flag.startAsk=1 ;
			
			while(XuanZhuanNUM != NowRouteInfor[num][3])
			{
				delay(0,0,0,10);
			}
			dir=0;
			MotoStop(5);
			delay(0,0,NowRouteInfor[num][8],0);	
			if(NowRouteInfor[num][4] == 0)	speed.jisu_speed=PLC_Data[22];
			if(NowRouteInfor[num][4] == 1)	speed.jisu_speed=PLC_Data[23];
			if(NowRouteInfor[num][4] == 2)	speed.jisu_speed=PLC_Data[24];			
			All_flag.startAsk=1;
			while(All_flag.startAsk)
			{
				delay(0,0,0,10);
			}									
		}							
	}
	
	//左旋反向
	else if(NowRouteInfor[num][6]==11)
	{		
		All_flag.stopAsk=1 ;
		while(All_flag.stopAsk)
		{
			delay(0,0,0,10);
		}
		dir=4;
		if(NowRouteInfor[num][7]==0)
		{
			delay(0,0,NowRouteInfor[num][8],0);
			All_flag.startAsk=1 ;
			while(XuanZhuanNUM != NowRouteInfor[num][3])
			{
				delay(0,0,0,10);
			}
			dir=1;
			MotoStop(5);
			delay(0,0,NowRouteInfor[num][8],0);	
			if(NowRouteInfor[num][4] == 0)	speed.jisu_speed=PLC_Data[22];
			if(NowRouteInfor[num][4] == 1)	speed.jisu_speed=PLC_Data[23];
			if(NowRouteInfor[num][4] == 2)	speed.jisu_speed=PLC_Data[24];			
			All_flag.startAsk=1;
			while(All_flag.startAsk)
			{
				delay(0,0,0,10);
			}																
		}
	}
	//右旋正向
	else if(NowRouteInfor[num][6]==12)
	{
		All_flag.stopAsk=1 ;
		while(All_flag.stopAsk)
		{
			delay(0,0,0,10);
		}
		dir=5;
		if(NowRouteInfor[num][7]==0)
		{
			delay(0,0,NowRouteInfor[num][8],0);
			All_flag.startAsk=1 ;
			while(XuanZhuanNUM != NowRouteInfor[num][3])
			{
				delay(0,0,0,10);
			}
			dir=0;			
			MotoStop(5);
			delay(0,0,NowRouteInfor[num][8],0);	
			if(NowRouteInfor[num][4] == 0)	speed.jisu_speed=PLC_Data[22];
			if(NowRouteInfor[num][4] == 1)	speed.jisu_speed=PLC_Data[23];
			if(NowRouteInfor[num][4] == 2)	speed.jisu_speed=PLC_Data[24];			
			All_flag.startAsk=1;
			while(All_flag.startAsk)
			{
				delay(0,0,0,10);
			}																
		}								
	}
	
	//右旋反向
	else if(NowRouteInfor[num][6]==13)
	{			
		All_flag.stopAsk=1 ;
		while(All_flag.stopAsk)
		{
			delay(0,0,0,10);
		}
		dir=5;
		if(NowRouteInfor[num][7]==0)
		{
			delay(0,0,NowRouteInfor[num][8],0);
			All_flag.startAsk=1 ;
			while(XuanZhuanNUM != NowRouteInfor[num][3])
			{
				delay(0,0,0,10);
			}
			dir=1;			
			MotoStop(5);
			delay(0,0,NowRouteInfor[num][8],0);	
			if(NowRouteInfor[num][4] == 0)	speed.jisu_speed=PLC_Data[22];
			if(NowRouteInfor[num][4] == 1)	speed.jisu_speed=PLC_Data[23];
			if(NowRouteInfor[num][4] == 2)	speed.jisu_speed=PLC_Data[24];					
			All_flag.startAsk=1;
			while(All_flag.startAsk)
			{
				delay(0,0,0,10);
			}									
		}							
	}
	//分叉口
	if(NowRouteInfor[num][1]==0)	fencha_dir = 0;
	if(NowRouteInfor[num][1]==1) 	fencha_dir = 1;
	if(NowRouteInfor[num][1]==2) 	fencha_dir = 2;
	
}
