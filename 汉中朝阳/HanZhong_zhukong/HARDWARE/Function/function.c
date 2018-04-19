#include "sys.h"

u8 Manual_juli = 50,JianSu_juli = 100; //雷达蔽障距离与开关
flag All_flag;

//延时函数
void delay(u32 h, u32 m, u32 s, u32 ms)
{
    OS_ERR err;
    OSTimeDlyHMSM(h, m, s, ms, OS_OPT_TIME_HMSM_STRICT, &err);
}
void PLC_DongZuo(u8 dir, u16 sudu)
{
    if(dir == 1)//前进
    {
        PLC_FangXiang_1 = 1;
        PLC_FangXiang_2 = 1;
        PLC_FangXiang_3 = 1;
        PLC_FangXiang_4 = 0;
        TLC5620_OUTnum(1, sudu);
    }
    else if(dir == 2)//后退
    {
        PLC_FangXiang_1 = 1;
        PLC_FangXiang_2 = 1;
        PLC_FangXiang_3 = 0;
        PLC_FangXiang_4 = 1;
        TLC5620_OUTnum(1, sudu);
    }
	else if(dir == 3)//左移
    {
        PLC_FangXiang_1 = 1;
        PLC_FangXiang_2 = 0;
        PLC_FangXiang_3 = 1;
        PLC_FangXiang_4 = 1;
        TLC5620_OUTnum(1, sudu);
    }
    else if(dir == 4)//右移
    {
        PLC_FangXiang_1 = 1;
        PLC_FangXiang_2 = 1;
        PLC_FangXiang_3 = 0;
        PLC_FangXiang_4 = 0;
        TLC5620_OUTnum(1, sudu);
    }
    else if(dir == 6)//左上
    {
        PLC_FangXiang_1 = 1;
        PLC_FangXiang_2 = 0;
        PLC_FangXiang_3 = 1;
        PLC_FangXiang_4 = 0;
        TLC5620_OUTnum(1, sudu);
    }
    else if(dir == 5)//右上
    {
        PLC_FangXiang_1 = 1;
        PLC_FangXiang_2 = 0;
        PLC_FangXiang_3 = 0;
        PLC_FangXiang_4 = 1;
        TLC5620_OUTnum(1, sudu);
    }
    else if(dir == 8)//左下
    {
        PLC_FangXiang_1 = 1;
        PLC_FangXiang_2 = 0;
        PLC_FangXiang_3 = 0;
        PLC_FangXiang_4 = 0;
        TLC5620_OUTnum(1, sudu);
    }
    else if(dir == 7)//右下
    {
        PLC_FangXiang_1 = 0;
        PLC_FangXiang_2 = 1;
        PLC_FangXiang_3 = 1;
        PLC_FangXiang_4 = 1;
        TLC5620_OUTnum(1, sudu);
    }
    else if(dir == 10)//左旋
    {
        PLC_FangXiang_1 = 0;
        PLC_FangXiang_2 = 1;
        PLC_FangXiang_3 = 1;
        PLC_FangXiang_4 = 0;
        TLC5620_OUTnum(1, sudu);
    }
    else if(dir == 9)//右旋
    {
        PLC_FangXiang_1 = 0;
        PLC_FangXiang_2 = 1;
        PLC_FangXiang_3 = 0;
        PLC_FangXiang_4 = 1;
        TLC5620_OUTnum(1, sudu);
    }
    else if(dir == 0)//停止
    {
		if((All_flag.DJQD2_GZ == 0)&&(All_flag.DJQD3_GZ == 0)&&(All_flag.DJQD4_GZ == 0)&&(All_flag.DJQD5_GZ == 0))//无故障
		{
			PLC_FangXiang_1 = 1;
			PLC_FangXiang_2 = 1;
			PLC_FangXiang_3 = 1;
			PLC_FangXiang_4 = 1;			
		}
        TLC5620_OUTnum(1, 0);
    }
}
void PLC_MoterStop(void)
{
	if((All_flag.DJQD2_GZ == 0)&&(All_flag.DJQD3_GZ == 0)&&(All_flag.DJQD4_GZ == 0)&&(All_flag.DJQD5_GZ == 0))//无故障
	{
		PLC_FangXiang_1 = 1;
		PLC_FangXiang_2 = 1;
		PLC_FangXiang_3 = 1;
		PLC_FangXiang_4 = 1;			
	}
    TLC5620_OUTnum(1, 0);
}
void DianGang_DongZuo(u8 dir)
{
    if(dir == 2)//起升
    {
        PLC_FangXiang_1 = 0;
        PLC_FangXiang_2 = 1;
        PLC_FangXiang_3 = 0;
        PLC_FangXiang_4 = 0;
		TLC5620_OUTnum(1, 0);
    }
    else if(dir == 1)//下降
    {
        PLC_FangXiang_1 = 0;
        PLC_FangXiang_2 = 0;
        PLC_FangXiang_3 = 1;
        PLC_FangXiang_4 = 1;
		TLC5620_OUTnum(1, 0);
    }
    else if(dir == 0)//停止
    {
        PLC_FangXiang_1 = 1;
        PLC_FangXiang_2 = 1;
        PLC_FangXiang_3 = 1;
        PLC_FangXiang_4 = 1;
		TLC5620_OUTnum(1, 0);
    }	
}
void DianGangStop(void)
{
    PLC_FangXiang_1 = 1;
    PLC_FangXiang_2 = 1;
    PLC_FangXiang_3 = 1;
    PLC_FangXiang_4 = 1;
	TLC5620_OUTnum(1, 0);
}
//清空数组
void Clear_ReceBuf(u8 num)
{
    if(num == 2)
    {
        memset(rece2_buf, 0, rece2_index);
    }
    else if(num == 6)
    {
        memset(rece6_buf, 0, sizeof(rece6_buf));
    }
}
//将16进制转换为字符
u8 HexToChar(u8 bChar)
{
    if((bChar >= 0x30) && (bChar <= 0x39))
    {
        bChar -= 0x30;
    }
    else if((bChar >= 0x41) && (bChar <= 0x46))
    {
        bChar -= 0x37;
    }
    else if((bChar >= 0x61) && (bChar <= 0x66))
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

	if(SystemParameter[0]!=10)
	{
		//判断标志位
		SystemParameter[0]=10;
	
		SystemParameter[98] = 100;
		SystemParameter[99] = 1;
		//存储所有系统参数
		SetAllParameterToSystem();
	}
}
