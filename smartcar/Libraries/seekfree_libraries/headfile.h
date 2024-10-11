/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
* ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
*
* �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file				headfile.h
* @company			�ɶ���ɿƼ����޹�˾
* @author			��ɿƼ�(QQ3184284598)
* @version			�鿴doc��version�ļ� �汾˵��
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

//***********ȫ�ֱ���**************//
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
//------��ɿƼ� ���ܺ���ͷ�ļ�
#include "SEEKFREE_ASSERT.h"
#include "SEEKFREE_FUN.h"
#include "SEEKFREE_PRINTF.h"

//------��ɿƼ� ��Ƭ����������ͷ�ļ�
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
//------��ɿƼ� ��Ʒģ������ͷ�ļ�
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



