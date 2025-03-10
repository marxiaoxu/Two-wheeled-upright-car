/*---------------------------------------------------------------------
                          驺吾图传工具函数
													
【平    台】RT1064
【编    写】满心欢喜
【联系方式】QQ：320388825 微信：LHD0617_
【最后更新】2021.11.30
【编译平台】MDK 5.28.0
【功    能】驺吾图传工具函数
【注意事项】本程序只供学习使用，未经作者许可，不得用于其它任何用途。
---------------------------------------------------------------------*/
#ifndef _ZW_TOOLS_H_
#define _ZW_TOOLS_H_

/*本函数基于逐飞驱动库进行开发需要包含逐飞UART函数头文件可根据自己的库自行更改*/
#include "zf_uart.h"


/*图像尺寸大小		切记必须与上位机填写的尺寸对应否则无法使用*/
/*图像尺寸大小		不得超过 长×宽<=10000*/
#define		ZW_ImgSize_H		80
#define		ZW_ImgSize_W		125

/*UART数据发宏定义	需要用户更改为自己的UART发送函数*/
#define 	ZW_Putchar(ZW_data)		uart_putchar(UART_1,ZW_data)

/*数据类型*/
typedef         unsigned char       ZW_uint8;

/*函数声明*/
void ZW_Send_Image(ZW_uint8 ZW_Image[ZW_ImgSize_H][ZW_ImgSize_W]);
 

																																						
#endif


