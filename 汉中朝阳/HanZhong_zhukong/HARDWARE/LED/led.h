#ifndef __LED_H
#define __LED_H
#include "sys.h"
//端口定义
#define QD		PFin(5)
#define TZ		PFin(4)
#define QfangZ  PFin(9)
#define HfangZ	PFin(8)
#define BEEP	PAout(3)

#define LED1 PBout(8)
#define LED2 PBout(9)
#define LED3 PEout(0)
#define LED4 PEout(1)


#define JieMianHao PLC_Data[15]
#define PIDZhouQi PLC_Data[32]
#define SPID_P PLC_Data[33]
#define SPID_I PLC_Data[34]
#define SPID_D PLC_Data[35]
#define QianCiDaoHangShuJu PLC_Data[36]
#define QianZhongDianPianCha PLC_Data[37]
#define ZiDongJiSu PLC_Data[38]
#define QianZuoLeiDa PLC_Data[39]
#define QianYouLeiDa PLC_Data[40]
#define HouZuoLeiDa PLC_Data[41]
#define HouYouLeiDa PLC_Data[42]
#define ZuoQianLeiDa PLC_Data[43]
#define ZuoHouLeiDa PLC_Data[44]
#define YouQianLeiDa PLC_Data[45]
#define YouHouLeiDa PLC_Data[46]
#define QianHouJuLi PLC_Data[47]
#define ZuoYouJuLi PLC_Data[48]
#define YinLiang PLC_Data[49]
#define SouDongSuDu PLC_Data[50]
#define DianChiDianLiang PLC_Data[51]
#define DianChiDianLiu PLC_Data[73]
#define HouZhongDianPianCha PLC_Data[77]
#define HouCiDaoHangShuJu PLC_Data[78]

#define QianFangZhuang PLC_OutPut[8]
#define HouFangZhuang PLC_OutPut[9]
#define SouDongBiZhang PLC_OutPut[10]
#define YuYinKaiGuan PLC_OutPut[11]
#define TongXunDeng PLC_OutPut[7]

#define PLC_FangXiang_1 PDout(4)
#define PLC_FangXiang_2 PDout(3)
#define PLC_FangXiang_3 PDout(1)
#define PLC_FangXiang_4 PDout(0)
#define PLC_JianSu PAout(15)
#define PLC_JiTing PAout(8)
#define PLC_XingZou_OR_ShengJiang PBout(10)
#define PLC_ShangSheng PBout(0)
#define PLC_XiaJiang PCout(5)
#define PLC_KuaiMan PCout(4)

#define PLC_FanKui PFin(14)
void LED_Init(void);//初始化	


#endif
