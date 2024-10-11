#ifndef _IMGAGE_HANDLE_h
#define _IMGAGE_HANDLE_h
#include "headfile.h"
void get_linex(int x,int s,int e,uint8 image[][188]);
void get_liney(int x,int s,int e,uint8 image[][188]);
void copy(uint8 SrcImg[][188], uint8 CannyImg[][188]);
void two_piecture(uint8 SrcImg[][188], uint8 CannyImg[][188]);
void binarization3(int k, int k2,int k3,unsigned char image[120][188]);
void picture_255(uint8 SrcImg[][188]);
void picture_x(uint8 SrcImg[][188],int k);
void binarization(int k,uint8 image[][188]);
void binarization2(int k,uint8 image[][188]);
void sobel(unsigned char imag[120][188], unsigned char charimag1[120][188]);
void Reduction(uint8 image[][188],uint8 image2[][188],uint8 image3[][188]);
void picutre_with(unsigned char image1[][188],unsigned char image2[][188]);
void Canny(uint8 SrcImg[][188],uint8 CAnny[][188],int sobel_threshold);
void yasuo(uint8 SrcImg[][188],uint8 wif[][125]);
void key_Init();
void find_light(unsigned char img[120][188]);
void fuck_image(int hang_s,int hang_e,uint8 image[][188]);

#endif





