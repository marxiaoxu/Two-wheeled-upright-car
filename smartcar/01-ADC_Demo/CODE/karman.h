#ifndef _karman_h
#define _karman_h



#include "headfile.h"



float KalmanFilter(float Accel,float Gyro);
double IIRLowPass(double x, struct _filter *Acc);
#endif 


