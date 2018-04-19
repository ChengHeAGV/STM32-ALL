#include "sys.h"


//孙先生的点数处理函数（类似于我的CDH_read_dataa函数功能）
Fencha_struct front_cdh16,back_cdh16,backl_cdh8,backr_cdh8;//定义一个Fencha_struct类型的全局变量
Fencha_struct findtemp={0,0,0,0,0,0};//孙先生函数中的结构体数组定义

//16位磁导航数据处理函数

//dst:磁导航的原始16进制的16位数
//num:处理时正常情况的最多点数（1~15）
//dir:分叉方向1：左分叉，2：右分叉
//返回值：Fencha_struct结构体

Fencha_struct FindSpace(u16 dst,u8 num,u8 dir)
{
	u16 i=0,dirr=dir;
	u16 p=~dst,numr=0,numl=0;
	Fencha_struct find;
	AA:	
	find.zeroNum = 0;
	find.zeroContinue = 0;
	find.Num = 0;
	find.Distance = 0;
	find.Error = 0;
	//计算有效点的个数
	for(i=0;i<16;i++)
	{
		if((p>>i)&0x0001)
		{
			find.Num++;
		}
	}
	//判断右边0的个数
	for(i=0;i<16;i++)
	{
		if(((p>>i)&0x0001)==0)
		{
			numr++;
		}
		else
		{
			i=16;//直接退出
		}
	}
	
	//判断左边0的个数
	for(i=0;i<16;i++)
	{
		if(((p<<i)&0x8000)==0)
		{
			numl++;
		}
		else
		{
			i=16;//直接退出
		}
	}		
	//计算0的个数，并计算0出现的位置
	for(i=numr;i<(16-numl);i++)
	{
		if(((p>>i)&0x0001)==0)
		{
			find.zeroLoctaion[find.zeroNum]=i;
			find.zeroNum++;
		}
	}
		
	//判断断点是否连续
	if(find.zeroNum>0)
	{
		find.zeroContinue = 1;
		if(find.zeroNum>1)
		{
			for(i = 0;i<(find.zeroNum-1);i++)
			{
				if(find.zeroLoctaion[i+1]-find.zeroLoctaion[i]==1)
				{
					continue;
				}
				else
				{
					find.zeroContinue++;
				}
			}
		}
	}
	//计算有效点距离中心位置的距离
	if(find.Num==0)//没找到有效点，距离返回0
	{
		find.Distance = 16;
		find.Error = 1;		
	}

	else
	{
		if(find.zeroNum>0)//有断点，返回0
		{
			if(find.zeroContinue==1)//一个分叉
			{
				if(dirr==2)//右分叉
				{
					for(i=numr;i<16;i++)
					{
						if((p>>i)&0x0001)
						{
							p = p&(~(0x0001<<i));
						}
						else
						{
							i = 16;
						}
					}
					goto AA;
				}
				else if(dirr==1)//左分叉
				{
					for(i=numl;i<16;i++)
					{
						if((p<<i)&0x8000)
						{
							p = p&(~(0x8000>>i));
						}
						else
						{
							i = 16;
						}
					}
					goto AA;
				}
				else
				{
					find.Error = 1;
				}
			}
			
		}
		else//正常情况
		{
			if(find.Num<=num)
			{				
				find.Distance = numl - numr ;
			}
			else
			{
				find.Error = 1;
			}
		}
	}
	
	findtemp = find;
	return find;

}
//8位磁导航数据处理函数
//dst:磁导航的原始16进制的8位数
//num:处理时正常情况的最多点数（1~7）
//dir:分叉方向1：左分叉，2：右分叉
//返回值：Fencha_struct结构体

Fencha_struct FindSpace1(u8 dst,u8 num,u8 dir)
{
	u8 i=0,dirr=dir;
	u8 p=~dst,numr=0,numl=0;
	Fencha_struct find;
	AA:	
	find.zeroNum = 0;
	find.zeroContinue = 0;
	find.Num = 0;
	find.Distance = 0;
	find.Error = 0;
	//计算有效点的个数
	for(i=0;i<8;i++)
	{
		if((p>>i)&0x01)
		{
			find.Num++;
		}
	}
	//判断右边0的个数
	for(i=0;i<8;i++)
	{
		if(((p>>i)&0x01)==0)
		{
			numr++;
		}
		else
		{
			i=8;//直接退出
		}
	}
	
	//判断左边0的个数
	for(i=0;i<8;i++)
	{
		if(((p<<i)&0x80)==0)
		{
			numl++;
		}
		else
		{
			i=8;//直接退出
		}
	}		
	//计算0的个数，并计算0出现的位置
	for(i=numr;i<(8-numl);i++)
	{
		if(((p>>i)&0x01)==0)
		{
			find.zeroLoctaion[find.zeroNum]=i;
			find.zeroNum++;
		}
	}
		
	//判断断点是否连续
	if(find.zeroNum>0)
	{
		find.zeroContinue = 1;
		if(find.zeroNum>1)
		{
			for(i = 0;i<(find.zeroNum-1);i++)
			{
				if(find.zeroLoctaion[i+1]-find.zeroLoctaion[i]==1)
				{
					continue;
				}
				else
				{
					find.zeroContinue++;
				}
			}
		}
	}
	//计算有效点距离中心位置的距离
	if(find.Num==0)//没找到有效点，距离返回0
		find.Error = 1;
	else
	{
//		if((findtemp.zeroNum==0)&&(find.zeroNum>4)&&(findtemp.Num>0))
//		{
//				if(find.zeroLoctaion[find.zeroNum/2]>=9)
//					dirr = 2;
//				else
//					dirr = 1;
//		}
		if(find.zeroNum>0)//有断点，返回0
		{
			if(find.zeroContinue==1)//一个分叉
			{
				if(dirr==2)//右分叉
				{
					for(i=numr;i<8;i++)
					{
						if((p>>i)&0x01)
						{
							p = p&(~(0x01<<i));
						}
						else
						{
							i = 8;
						}
					}
					goto AA;
				}
				else if(dirr==1)//左分叉
				{
					for(i=numl;i<8;i++)
					{
						if((p<<i)&0x80)
						{
							p = p&(~(0x80>>i));
						}
						else
						{
							i = 8;
						}
					}
					goto AA;
				}
				else
				{
					find.Error = 1;
				}
			}
			
		}
		else//正常情况
		{
			if(find.Num<=num)
			{
				find.Distance = numl - numr + 8;
			}
			else
			{
				find.Error = 1;
			}
		}
	}
	
	findtemp = find;
	return find;

}

