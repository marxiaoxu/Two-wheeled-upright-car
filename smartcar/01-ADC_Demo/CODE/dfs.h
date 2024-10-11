
#ifndef _DFS_h
#define _DFS_h
#include "headfile.h"
int ConnectedComponentLabeling(unsigned char *bitmap, int width, int height, int *labelmap);
void seek_con(unsigned char Bin_Image[][188]);
int link_domain_label(unsigned char imagedata[],unsigned char buff[]);
int Get_Roi(unsigned char image[][188],int temp);
#endif 



