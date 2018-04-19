#include "sys.h"

u8 Manual_juli = 50,JianSu_juli = 100; //�״���Ͼ����뿪��
flag All_flag;

//��ʱ����
void delay(u32 h, u32 m, u32 s, u32 ms)
{
    OS_ERR err;
    OSTimeDlyHMSM(h, m, s, ms, OS_OPT_TIME_HMSM_STRICT, &err);
}
void PLC_DongZuo(u8 dir, u16 sudu)
{
    if(dir == 1)//ǰ��
    {
        PLC_FangXiang_1 = 1;
        PLC_FangXiang_2 = 1;
        PLC_FangXiang_3 = 1;
        PLC_FangXiang_4 = 0;
        TLC5620_OUTnum(1, sudu);
    }
    else if(dir == 2)//����
    {
        PLC_FangXiang_1 = 1;
        PLC_FangXiang_2 = 1;
        PLC_FangXiang_3 = 0;
        PLC_FangXiang_4 = 1;
        TLC5620_OUTnum(1, sudu);
    }
	else if(dir == 3)//����
    {
        PLC_FangXiang_1 = 1;
        PLC_FangXiang_2 = 0;
        PLC_FangXiang_3 = 1;
        PLC_FangXiang_4 = 1;
        TLC5620_OUTnum(1, sudu);
    }
    else if(dir == 4)//����
    {
        PLC_FangXiang_1 = 1;
        PLC_FangXiang_2 = 1;
        PLC_FangXiang_3 = 0;
        PLC_FangXiang_4 = 0;
        TLC5620_OUTnum(1, sudu);
    }
    else if(dir == 6)//����
    {
        PLC_FangXiang_1 = 1;
        PLC_FangXiang_2 = 0;
        PLC_FangXiang_3 = 1;
        PLC_FangXiang_4 = 0;
        TLC5620_OUTnum(1, sudu);
    }
    else if(dir == 5)//����
    {
        PLC_FangXiang_1 = 1;
        PLC_FangXiang_2 = 0;
        PLC_FangXiang_3 = 0;
        PLC_FangXiang_4 = 1;
        TLC5620_OUTnum(1, sudu);
    }
    else if(dir == 8)//����
    {
        PLC_FangXiang_1 = 1;
        PLC_FangXiang_2 = 0;
        PLC_FangXiang_3 = 0;
        PLC_FangXiang_4 = 0;
        TLC5620_OUTnum(1, sudu);
    }
    else if(dir == 7)//����
    {
        PLC_FangXiang_1 = 0;
        PLC_FangXiang_2 = 1;
        PLC_FangXiang_3 = 1;
        PLC_FangXiang_4 = 1;
        TLC5620_OUTnum(1, sudu);
    }
    else if(dir == 10)//����
    {
        PLC_FangXiang_1 = 0;
        PLC_FangXiang_2 = 1;
        PLC_FangXiang_3 = 1;
        PLC_FangXiang_4 = 0;
        TLC5620_OUTnum(1, sudu);
    }
    else if(dir == 9)//����
    {
        PLC_FangXiang_1 = 0;
        PLC_FangXiang_2 = 1;
        PLC_FangXiang_3 = 0;
        PLC_FangXiang_4 = 1;
        TLC5620_OUTnum(1, sudu);
    }
    else if(dir == 0)//ֹͣ
    {
		if((All_flag.DJQD2_GZ == 0)&&(All_flag.DJQD3_GZ == 0)&&(All_flag.DJQD4_GZ == 0)&&(All_flag.DJQD5_GZ == 0))//�޹���
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
	if((All_flag.DJQD2_GZ == 0)&&(All_flag.DJQD3_GZ == 0)&&(All_flag.DJQD4_GZ == 0)&&(All_flag.DJQD5_GZ == 0))//�޹���
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
    if(dir == 2)//����
    {
        PLC_FangXiang_1 = 0;
        PLC_FangXiang_2 = 1;
        PLC_FangXiang_3 = 0;
        PLC_FangXiang_4 = 0;
		TLC5620_OUTnum(1, 0);
    }
    else if(dir == 1)//�½�
    {
        PLC_FangXiang_1 = 0;
        PLC_FangXiang_2 = 0;
        PLC_FangXiang_3 = 1;
        PLC_FangXiang_4 = 1;
		TLC5620_OUTnum(1, 0);
    }
    else if(dir == 0)//ֹͣ
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
//�������
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
//��16����ת��Ϊ�ַ�
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
//��������ת��Ϊ16������
long FloatTohex(float HEX)
{
    return *( long *)&HEX;//ע��˴���long��ָ��ǿ��ָ�򸡵���HEX�ĵ�ַ
}
//��16����ת��Ϊ������
float HexTofloat(long HEX)
{
    return *( float *)&HEX;
}
void UserConfigInit(void)
{
	LED4=0;
	W25QXX_Init();			//W25QXX��ʼ��
	LED4=1;
	while(W25QXX_ReadID()!=W25Q128)//��ⲻ��W25Q128��LED��˸
	{
		LED4=~LED4;//DS0��˸
		delay(0, 0,0 , 100);
	}
	LED4=0;
	
	//��ȡ����ϵͳ����
	GetAllParameterFromSystem();

	if(SystemParameter[0]!=10)
	{
		//�жϱ�־λ
		SystemParameter[0]=10;
	
		SystemParameter[98] = 100;
		SystemParameter[99] = 1;
		//�洢����ϵͳ����
		SetAllParameterToSystem();
	}
}
