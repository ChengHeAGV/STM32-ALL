#ifndef __FUNCTION_H
#define __FUNCTION_H	
#include "sys.h"

void delay(u32 h,u32 m,u32 s,u32 ms);
long FloatTohex(float HEX);
float HexTofloat(long HEX);
void Clear_ReceBuf(u8 num);
void PLC_DongZuo(u8 dir,u16 sudu);
void PLC_MoterStop(void);
void DianGang_DongZuo(u8 dir);
void DianGangStop(void);
u8 HexToChar(u8 bChar);
void UserConfigInit(void);
extern u8 Manual_juli,JianSu_juli;
typedef struct
{
	u8 beep_flag;
	u8 flag_tz;
	u8 DJQD2_GZ;
	u8 DJQD3_GZ;
	u8 DJQD4_GZ;
	u8 DJQD5_GZ;
}flag;
extern flag All_flag;
#endif
