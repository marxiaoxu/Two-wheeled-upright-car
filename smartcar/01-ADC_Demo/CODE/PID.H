#ifndef _PID_h
#define _PID_h
#include"headfile.h"


//float KalmanFilter(float Accel,float Gyro);
int Vertical(float Med,float Angle,float gyro_Y);
//int32 PID_Increase(Error *sptr, PID *pid, int32 NowPlace, int32 Point);

// int Turn(int gyro_Z);

#define PID_W_MAX   2000
#define PID_W_MIN   1000
extern int all_flag;
extern int  Setpointw, Outputw;
extern int Lastinputw,Lasterrorw;
extern float Kpw,Kiw,Kdw;
int velocity(int Encoder_Left,int Encoder_Right);
int Velocity2(int Target,int Movement,int encoder_left,int encoder_right);

float Gyro_PID(float Gyro_Data,float Gyro_m);
float Angle_PID(float Angle_Data,float Angle_m,float balance_angle);
float Speed_PID(float Speed_New,float Speed_m,int speeed_low);
float out_Turn(int gyro_z);
float In_Turn(int gyro_Z,int gyro_z);

void SetTuningsW(float KP,float KI,float KD);
void PID_Compute_W(void);
float PID_OUT_W(int speed);
float Speed_Measure();
float Angspeed(float t_new,int t_angle);  //角速度环);  //角速度环//角速度环
//int Angspeed(float  error,int speed);

#endif 




