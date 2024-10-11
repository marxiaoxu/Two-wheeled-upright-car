#ifndef _motor_h
#define _motor_h


#include "headfile.h"
#define left_f  TIM_2_CH3_A02
#define left_z  TIM_2_CH2_A01
#define right_z  TIM_2_CH1_A00
#define right_f  TIM_2_CH4_A03
extern int gyro_Y;
void motor_Init();
int Get_Attitude();
void My_Init();
void pwn_out(int speed,int final_speed,int turn);
float Get_Gyro();
float Yaw_angle();
void map(int lef,int rig);
void get_map_angle();
//float IMUupdate2();
float IMUupdate(float gx, float gy, float gz, float ax, float ay, float az);
float Compute_Angle(void);
#endif



