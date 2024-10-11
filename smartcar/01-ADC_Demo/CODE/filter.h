
#ifndef _filter_h
#define _filter_h
#include "headfile.h"
#define M_PI_F 3.141592653589793f
#define LPF_1_(hz,t,in,out) ((out) += ( 1 / ( 1 + 1 / ( (hz) *6.28f *(t) ) ) ) *( (in) - (out) ))

typedef struct
{
	float in_est_d;   //Estimator
	float in_obs;    //Observation
	
	float fix_kp;
	float e_limit;

	float e;

	float out;
}_fix_inte_filter_st;

typedef struct
{
  float a[3];
  float b[3];
}Butter_Parameter;

typedef struct
{
	unsigned char cnt;

	long int lst_pow_sum;
	
	long int now_out;
	long int lst_out;
	long int now_velocity_xdt;
} _steepest_st;


void Bin_Image_Filter (unsigned char Bin_Image[][188]);
void Bin_Image_Filter2(unsigned char Bin_Image[120][188],unsigned char Bin_Image2[120][188]);
void fuck_zaodian(const unsigned char img[120][188],unsigned char out[120][188]);

#endif



