/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
* 技术讨论QQ群：一群：179029047(已满)  二群：244861897
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file				headfile.h
* @company			成都逐飞科技有限公司
* @author			逐飞科技(QQ3184284598)
* @version			查看doc内version文件 版本说明
* @Software			IAR 8.32.4 or MDK 5.28
* @Target core		MM32F3277
* @Taobao			https://seekfree.taobao.com/
* @date				2021-02-22
********************************************************************************************************************/
 
#ifndef _headfile_h
#define _headfile_h

#include <stdint.h>


extern float GyroD,GyroP,GyroI,Speed_PID_speed,turn_kp,turn_kd,turn_kp2,turn_kd2,AngleP, AngleD, SpeedP,SpeedI,turn_kp,turn_kd;
extern int wirelflag;
extern float loss_turn;

extern	int temp2,temp3,temp1,temp4,temp5,temp6,temp7,temp8,temp9,roi,roi_number;
extern float show1,show2;
extern int y_aflag;
extern float show3;
extern float show4;
extern float show5;
extern float show6;
//*************************//

//***********全局变量**************//
extern double getmiddle;
extern  float angel,externangle;
extern int turn_flag;
extern int tim ;
extern	int center_gravityx[80];
extern int center_gravityy[80];
extern int max_light[80];
extern int average[80];
extern	int left_up[80],right_down[80];
extern	int left_upx[80],right_downx[80];
extern  int left_upy[80],right_downy[80];
extern int boundary_number[80],max_number[80];
extern int stop_flag,speeed_low;
extern int roi;
extern int light,miss;
extern  int count[80];
extern double date[10];
extern float e_angle,Yaw_Angle;
extern int x_distence;
extern int y_distence;
extern  int Move_Distence,Map_turn;
extern int Map_Angle;
extern 		int  x1_0;
extern 		int  y1_0;
extern 	int x2_120;
extern 		int  y2_188,fuck;
extern unsigned char copy_tuxiang2[120][188];
//extern unsigned char bianyan_tx[120][188];

  struct _filter{
	double inBuf[7];
	double outBuf[7];
};
	
extern struct _filter groy_filter[1];
//*************************//
#include "dfs.h"
#include "filter.h" 
#include "ZW_Tools.h"
#include "pengzhang.h"
#include "OTSU.h"
#include "common.h"
#include "core_cm3.h"
#include "board.h"
//*************************//
#include "motor.h"
#include "math.h"
#include "PID.H"
#include "stdio.h"
#include "karman.h"
#include "bp.h"
#include "image_handle.h"
#include "fuzzy.h"
#include "filter.h"
#include "ADRC.h"
#include "mymath.h"

//#define dt 10
//*************************//
//------逐飞科技 功能函数头文件
#include "SEEKFREE_ASSERT.h"
#include "SEEKFREE_FUN.h"
#include "SEEKFREE_PRINTF.h"

//------逐飞科技 单片机外设驱动头文件
#include "zf_adc.h"
#include "zf_camera.h"
#include "zf_exti.h"
#include "zf_flash.h"
#include "zf_gpio.h"
#include "zf_spi.h"
#include "zf_systick.h"
#include "zf_pit.h"
#include "zf_pwm.h"
#include "zf_tim.h"
#include "zf_uart.h"
#include "zf_fsmc.h"
#include "delay.h"
//------逐飞科技 产品模块驱动头文件
#include "SEEKFREE_18TFT.h"
#include "SEEKFREE_7725.h"
#include "SEEKFREE_ABSOLUTE_ENCODER.h"
#include "SEEKFREE_FONT.h"
#include "SEEKFREE_ICM20602.h"
#include "SEEKFREE_IIC.h"
#include "SEEKFREE_IPS114_SPI.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
#include "SEEKFREE_L3G4200D.h"
#include "SEEKFREE_MMA8451.h"
#include "SEEKFREE_MPU6050.h"
#include "SEEKFREE_OLED.h"
#include "SEEKFREE_TSL1401.h"
#include "SEEKFREE_UART_7725.h"
#include "SEEKFREE_VIRSCO.h"
#include "SEEKFREE_WIRELESS.h"
#include "SEEKFREE_MT9V03X.h"
#endif



