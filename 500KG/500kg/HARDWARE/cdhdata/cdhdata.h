#ifndef __CDHDATA_H
#define __CDHDATA_H	 
#include "sys.h"

typedef struct 		
{
	u8 zeroNum;			//磁导航空点的个数
	u8 zeroLoctaion[16];//磁导航空点的位置
	u8 zeroContinue;	//断点是否连续
	
	u8 Num;				//有效点（磁导航的亮点）的个数
	int Distance;		//有效点与中心的距离
	u8 Error;			//异常点（出轨、分叉和一些不在考虑点数范围内的情况）时返回值
}Fencha_struct;				


extern u8 n,a;
extern Fencha_struct front_cdh16,back_cdh16,backl_cdh8,backr_cdh8; //外部定义一个Fencha_struct类型的全局变量
extern Fencha_struct findtemp;//孙先生函数中的结构体数组外部定义


Fencha_struct FindSpace(u16 dst,u8 num,u8 dir);//16位处理检测到磁导航的数据函数
Fencha_struct FindSpace1(u8 dst,u8 num,u8 dir);//8位处理检测到磁导航的数据函数
 				    
#endif
