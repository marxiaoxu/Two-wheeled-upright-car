/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
* 技术讨论QQ群：一群：179029047(已满)  二群：244861897
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file				main
* @company			成都逐飞科技有限公司
* @author			逐飞科技(QQ3184284598)
* @version			查看doc内version文件 版本说明
* @Software			IAR 8.3 or MDK 5.24
* @Target core		MM32F3277
* @Taobao			https://seekfree.taobao.com/
* @date				2021-02-22
********************************************************************************************************************/
#include "headfile.h"
 //左上角坐标 右下角坐标，重心坐标，最大亮度，平均亮度，边界个数和面积，共10个 7.8v
int distinction_input[10];
float show1=0;
float show2;
float show3;
float show4;
float show5;
float show6;
//*************************//
int flag=1;
//int test=0;

int test3=0;
int light=0,width=0;
int turn_flag=0;
int biank = 0;
int all_pixel=0;
float e_angle=0,externangle=0,last_Yaw_Angle=0,Angle_f=0,Temp_Angle_f=0;
uint8 roi_tuxiang[120][188];
uint8 copy_tuxiang[120][188];
uint8 copy_tuxiang2[120][188];
//uint8 bianyan_tx[120][188];
int x1_0=0;
int  y1_0=0;
int  x2_120=120;
int  y2_188=188;
int center_gravityx[80],center_gravityy[80];
int max_light[80],average[80];
int left_up[80],right_down[80];
int left_upx[80],right_downx[80];
int left_upy[80],right_downy[80];
int boundary_number[80];
int max_number[80];
int count[80];
double date[10],adc_light=0;
double getmiddle=0;
int x_distence=0;
int x_distence_f=0;
int last_x_d=0;
int y_distence=0;

int wirelflag=1,stop_flag=1,speeed_low=0,lost_gf=0;
unsigned long writeflash[13];
unsigned long readflash[13];
uint8 uart4_get_buffer=1;
int temp2=0,temp3=0,temp1=0,temp4=0,temp5=0,temp6=0,temp7=0,temp8=0,temp9=0,roi=0,roi_number=0;	
	


int miss=0,fuck=55;
	double middle_t=105;//90
	//*****************************************************************************************//
void clean()//数组亲零
{	
			
	
			if(miss>=1)
			{
		  x1_0=fuck;//0
			 y1_0=0;
			 x2_120=120;
			 y2_188=188;
			}
			else
			{
				
				
		x1_0=y_distence-35;
		y1_0=x_distence-40;
		x2_120=y_distence+35;
		y2_188=x_distence+40;
//	
//		x1_0=y_distence-35;
//		y1_0=x_distence-40;
//		x2_120=y_distence+35;
//		y2_188=x_distence+40;
	
//	
//		x1_0=0;
//		y1_0=0;
//		x2_120=120;
//		y2_188=188;

			if(x1_0<fuck)
				x1_0=fuck;
			
			if(y1_0<0)
				y1_0=0;
			
			
			if(x1_0>120)
				x1_0=120;
			
			if(y1_0>188)
				y1_0=188;
			
			
			if(x2_120>120)
				x2_120=120;
			
			if(y2_188>188)
				y2_188=188;
			
				
			if(x2_120<0)
				x2_120=0;
			
			if(y2_188<0)
				y2_188=0;
			
		}
			
		
		
	
//			
//	ips114_showint16(185,1,x1_0);
//	ips114_showint16(185,2,y1_0);		
//	ips114_showint16(185,3,x2_120);
//	ips114_showint16(185,4,y2_188);	
			
//	x_distence=0;
//	y_distence=0;

		for(int k=80;k>=0;k--)
	{
		max_light[k]=0;
		average[k]=0;
		count[k]=0;
		center_gravityx[k]=0;
		center_gravityy[k]=0;	
		left_upx[k]=250;
		left_upy[k]=0;
		right_downx[k]=0;
		right_downy[k]=250;	
		boundary_number[k]=0;
		max_number[k]=0;
 }
	for (int i = 0; i < 120; i++)
				{
			for (int j = 0; j < 188; j++)
			{
			roi_tuxiang[i][j]=0;										
			}
				}
}	//gpio_set(D5,1);//D5 输出高电平void gpio_init (PIN_enum pin, GPIODIR_enum dir, uint8 dat, GPIOMODE_enum mode)
void  draw1()
{
		get_linex(center_gravityx[roi],120,left_upy[roi]+8,copy_tuxiang);	
	get_liney(center_gravityy[roi],188,right_downx[roi]+8,copy_tuxiang);
	get_linex(center_gravityx[roi],left_upx[roi]-8,0,copy_tuxiang);	
	get_liney(center_gravityy[roi],right_downy[roi]-8,0,copy_tuxiang);
		
	get_linex(right_downx[roi]+4,left_upy[roi]+4,left_upx[roi]-4,copy_tuxiang);	
	get_liney(left_upx[roi]-4,right_downx[roi]+4,right_downy[roi]-4,copy_tuxiang);
	get_linex(right_downy[roi]-4,left_upy[roi]+4,left_upx[roi]-4,copy_tuxiang);	
	get_liney(left_upy[roi]+4,right_downx[roi]+4,right_downy[roi]-4,copy_tuxiang);
	
}



void  draw2()
{
	
		get_linex(center_gravityx[roi],120,left_upy[roi]+8,copy_tuxiang2);	
	get_liney(center_gravityy[roi],188,right_downx[roi]+8,copy_tuxiang2);
	get_linex(center_gravityx[roi],left_upx[roi]-8,0,copy_tuxiang2);	
	get_liney(center_gravityy[roi],right_downy[roi]-8,0,copy_tuxiang2);
		
		
		
	get_linex(right_downx[roi]+4,left_upy[roi]+4,left_upx[roi]-4,copy_tuxiang2);	
	get_liney(left_upx[roi]-4,right_downx[roi]+4,right_downy[roi]-4,copy_tuxiang2);
	get_linex(right_downy[roi]-4,left_upy[roi]+4,left_upx[roi]-4,copy_tuxiang2);	
	get_liney(left_upy[roi]+4,right_downx[roi]+4,right_downy[roi]-4,copy_tuxiang2);
	
}


//*****************************************************************************************//

int main(void)
{


	My_Init();

	static int move_ui=0;
	while(1)
	{
				
//data_conversion(show1,Speed_PID_speed,0,0, virtual_scope_data);//使用虚拟示波器数据转换函数转换数据，至多同时转换四个数据
//uart_putbuff(UART_1,virtual_scope_data,10);  //数据转换完成后，使用串口发送将数组的内容发送出去
//			
if(uart_query(UART_4, &uart4_get_buffer))									// 查询是否收到数据
{
	uart_putchar(UART_4, uart4_get_buffer);		
}



		if(uart4_get_buffer==0)
			stop_flag=0;//
		if(uart4_get_buffer!=0)
		stop_flag=1;

		if(mt9v03x_finish_flag)
		{
		
			
	//systick_start();//开启计时（得到程序运行时间）


			
copy(copy_tuxiang2,mt9v03x_image);//out in	 复制
conv_bin_special(copy_tuxiang2,copy_tuxiang);//in out  边缘增强
//copy(bianyan_tx,copy_tuxiang);//out in
//binarization(65,copy_tuxiang);//80  二值化 0
			
			
			binarization2(65,copy_tuxiang);//80  二值化 
			
//Bin_Image_Filter2(copy_tuxiang, copy_tuxiang);//腐蚀膨胀
//Bin_Image_Filter(copy_tuxiang); 
pengzhang2(copy_tuxiang);//去除无效区域  减少计算量

//**********************************判断****************************//

roi_number=link_domain_label(copy_tuxiang[0],roi_tuxiang[0]);//连通域提取

if(roi_number>=1)//连通域大于等于1时，进行连通域判定找roi
{
	roi=Get_Roi(roi_tuxiang,roi_number);	


	if(roi!=0)
	{

		y_distence=center_gravityy[roi];
		
		
		x_distence=center_gravityx[roi];
		
//	ips114_showint16(65,2,(int)x_distence);//139
		width=(center_gravityx[roi]-right_downy[roi]);
		x_distence_f=x_distence;
//		if(temp3==1&&temp4==1)
//		{
//		  draw1();
//		}
//		if(temp1==1&&temp4==1)
//		{
//			draw2();
//		}
	
	}
	else
	{

		x_distence_f=0;
		width=0;
	}
	
}
	else
	{
	  x_distence_f=0;
	}
//****************控制传输*******************//

if(x_distence_f!=0)
{

	  getmiddle=(x_distence-middle_t/10)-94;//5   7.2
		miss=0;
	speeed_low=0;
		gpio_set(D8,0);
}
else
{
	
	gpio_set(D8,1);
	  miss++;
	
	
}

			
	
	if(width>6)
	{	speeed_low=1;
	//gpio_set(D8,1);
		}
	else 
	{
		//gpio_set(D8,0);
		}
	
		
		if(miss>=1)
		{getmiddle=loss_turn;
		speeed_low=2;}
		



if(temp1==1)
ips114_displayimage032(copy_tuxiang[0],188,120); //处理后的图	


temp1=gpio_get (C9);
temp2=gpio_get (A8);
temp3=gpio_get (A15);
temp4=gpio_get (C7);	
temp5=gpio_get (G15);
temp6=gpio_get (G13);
temp7=gpio_get (G11);
temp8=gpio_get (G14);
temp9=gpio_get (B3);

//获取按键的情况

//if(temp1==3)
{




if(temp7==0)  //shang0.
	
{
if(move_ui==0)
{middle_t++;
	systick_delay_ms(200);
}
if(move_ui==1)
{SpeedP++;
	
	
}
if(move_ui==2)
{AngleP++;
		systick_delay_ms(200);}
if(move_ui==3)
	{AngleD++;
		systick_delay_ms(200);}
if(move_ui==4)
	{GyroI++;
		systick_delay_ms(200);}
		if(move_ui==5)
	{	Speed_PID_speed++;
	systick_delay_ms(200);}
	if(move_ui==6)
	{	externangle++;
	systick_delay_ms(200);}
		if(move_ui==7)
	{	turn_kp++;
	systick_delay_ms(200);}
		if(move_ui==8)
	{	turn_kd++;
	systick_delay_ms(200);}
	if(move_ui==9)
	{	turn_kp2++;
	systick_delay_ms(200);}
		if(move_ui==10)
	{	turn_kd2++;
	systick_delay_ms(200);}
		if(move_ui==11)
	{	loss_turn++;
	systick_delay_ms(200);}
			if(move_ui==12)
	{	fuck++;
	systick_delay_ms(200);}
	
	systick_delay_ms(200);
}
if(temp5==0)  //xia
{	

if(move_ui==0)
{middle_t--;
systick_delay_ms(200);
}
if(move_ui==1)
{ SpeedP--;
	systick_delay_ms(200);}
if(move_ui==2)
{	AngleP--;
	systick_delay_ms(200);}
if(move_ui==3)
	{	AngleD--;
	systick_delay_ms(200);}
if(move_ui==4)
	{	GyroI--;
	systick_delay_ms(200);}
	if(move_ui==5)
	{	Speed_PID_speed--;
	systick_delay_ms(200);}
	if(move_ui==6)
	{	externangle--;
	systick_delay_ms(200);}
	if(move_ui==7)
		{	turn_kp--;
	systick_delay_ms(200);}
	if(move_ui==8)
	{	turn_kd--;
	systick_delay_ms(200);}
		if(move_ui==9)
	{	turn_kp2--;
	systick_delay_ms(200);}
		if(move_ui==10)
	{	turn_kd2--;
	systick_delay_ms(200);}
	
		if(move_ui==11)
	{	loss_turn--;
	systick_delay_ms(200);}
			if(move_ui==12)
	{	fuck--;
	systick_delay_ms(200);}
	
systick_delay_ms(200);
}


if(temp6==0)  //zuo   ？？？？？？？？？？
{	
	move_ui++;
	if(move_ui>12)
		move_ui=0;
	systick_delay_ms(200);
}
if(temp8==0)  //you
{	
	move_ui--;
	if(move_ui<0)
		move_ui=12;
systick_delay_ms(200);
}

if(temp9==0)  //you
{	
   test3=!test3;
systick_delay_ms(200);
}


// int flash_f=0;
//if(temp3==1)
//{
//		ips114_displayimage032(copy_tuxiang[0],188,120); //处理后的图		
//if(temp2==1)
//	seekfree_sendimg_03x(UART_1,copy_tuxiang[0],188,120);
//	if(test3==1)
//	{
////
//	//			//(FLASH_SECTION_127,FLASH_PAGE_3)

//		flash_page_read(FLASH_SECTION_127, FLASH_PAGE_3,readflash, 256);
//	systick_delay_ms(20);
//		
//GyroP=readflash[0]; 
//GyroI=readflash[1];
//GyroD=readflash[2];//153  0.17

//AngleP=readflash[3];//67
//AngleD=readflash[4];//420     111

//SpeedP=readflash[5];////20;//
//SpeedI=readflash[6];
//Speed_PID_speed=readflash[7];//-250         
//loss_turn=readflash[8];

//turn_kp=readflash[9];//7
//turn_kd=readflash[10];//1

//turn_kp2=readflash[11];//-18
//turn_kd2=readflash[12];//3

//if(Speed_PID_speed>=0)
//	Speed_PID_speed=-Speed_PID_speed;

//if(turn_kp>=0)
//	turn_kp=-turn_kp;

//if(turn_kd>=0)
//	turn_kd=-turn_kd;

//if(turn_kp2>=0)
//	turn_kp2=-turn_kp2;

//	
//if(turn_kd2>=0)
//	turn_kd2=-turn_kd2;


//	systick_delay_ms(20);
//	flash_f=0;
//}	

//}

//flag=1;
//if(temp1==1)
//{
//	ips114_displayimage032(copy_tuxiang2[0],188,120); //原图

//	if(temp2==1)
//	seekfree_sendimg_03x(UART_1,copy_tuxiang2[0],188,120);
//}

//if(temp2==1&&flash_f==0)
//{	
//	
//	if(test3==1&&flash_f==0)
//	{
//	int status;
//	flash_f=1;
//  if(flash_check(FLASH_SECTION_127,FLASH_PAGE_3))//校验当前 扇区所在页是否有数据，如果有数据则擦除整个扇区
//    {
//			//(FLASH_SECTION_127,FLASH_PAGE_3)
//        status = flash_erase_page(FLASH_SECTION_127,FLASH_PAGE_3);//擦除扇区，如果扇区已经有数据则必须擦除扇区之后才能再次写入新的数据
//				systick_delay_ms(200);
//        if(status)  while(1);//擦除失败
//				
//    }
//	
//writeflash[0]=GyroP; 
//writeflash[1]=GyroI;
//writeflash[2]=GyroD;//153  0.17

//writeflash[3]=AngleP;//67
//writeflash[4]=AngleD;//420     111

//writeflash[5]=SpeedP;////20;//
//writeflash[6]=SpeedI;
//	
//writeflash[7]=Speed_PID_speed;//-250         
//writeflash[8]=loss_turn;

//writeflash[9]=turn_kp;//7
//writeflash[10]=turn_kd;//1

//writeflash[11]=turn_kp2;//-18
//writeflash[12]=turn_kd2;//3
//	

//	flash_page_program(FLASH_SECTION_127, FLASH_PAGE_3,writeflash, 256);
////(FLASH_SECTION_127,FLASH_PAGE_3)
//	   status = flash_page_program(FLASH_SECTION_127, FLASH_PAGE_3,writeflash,256); 
//		 	systick_delay_ms(200);
//    if(status)  while(1);//写入失败

//}
//}
	
	if(test3)
{

	
	//flash_page_read(FLASH_SECTION_1, FLASH_PAGE_0,flash, 1);
	//systick_delay_ms(25);
	//systick_start();//开启计时（得到程序运行时间）
//show1=systick_getval()*6.00339E-06;// 运行时间	
	ips114_showstr(15,0,"middle_t");	//GyroP
	ips114_showstr(15,1,"SpeedP:");
	ips114_showstr(15,2,"AngleP:");
	ips114_showstr(15,3,"AngleD:");
	ips114_showstr(15,4,"GyroI:");
	ips114_showstr(15,5,"speed:");
	ips114_showstr(15,6,"angle:");
	ips114_showstr(15,7,"t_p:"); // float turn_kp2=0;float turn_kd2=0;
	//ips114_showfloat(180,0,show3,1,5);//SpeedI
	ips114_showstr(140,1,"fuck:");
	ips114_showstr(140,2,"A_n:");
	ips114_showstr(140,3,"Y_a:");
	ips114_showstr(140,4,"t_d:");
	ips114_showstr(140,5,"t_p2:");
	ips114_showstr(140,6,"t_d2:");
	ips114_showstr(140,7,"lo_t:");
	ips114_showint16(65,0,(int)middle_t);
	ips114_showint16(65,1,(int)SpeedP);
	//ips114_showint16(155,1,angel*10);

	ips114_showint16(65,2,(int)AngleP);
	//	ips114_showint16(115,2,SpeedI);
	ips114_showint16(65,3,(int)AngleD);
	ips114_showint16(65,4,(int)GyroI);
	ips114_showint16(65,5,(int)Speed_PID_speed);
	ips114_showint16(65,6,(int)externangle);
	ips114_showint16(65,7,(int)turn_kp);
	ips114_showint16(180,1,(int)fuck);
	ips114_showfloat(180,2,angel,3,2);
	ips114_showfloat(180,3,Yaw_Angle,3,2);
	ips114_showint16(180,4,(int)turn_kd);
	ips114_showint16(180,5,(int)turn_kp2);
	ips114_showint16(180,6,(int)turn_kd2);
	ips114_showint16(180,7,(int)loss_turn);

		
	
	if(move_ui==0)
	{	
	ips114_showstr(0,0,"->");
	ips114_showstr(0,1,"0>");
	ips114_showstr(0,2,"0>");
	ips114_showstr(0,4,"0>");
	ips114_showstr(0,5,"0>");
	ips114_showstr(0,6,"0>");
	ips114_showstr(0,7,"0>");
	ips114_showstr(120,5,"0>");
	ips114_showstr(120,6,"0>");
	ips114_showstr(120,7,"0>");
	ips114_showstr(120,4,"0>");
	ips114_showstr(120,1,"0>");
	}
	if(move_ui==1)
	{ips114_showstr(120,4,"0>");
	ips114_showstr(0,0,"0");
	ips114_showstr(0,1,"->");
	ips114_showstr(0,2,"0");
	ips114_showstr(0,3,"0");
	ips114_showstr(0,4,"0");
	ips114_showstr(0,5,"0");
	ips114_showstr(0,6,"0");
	ips114_showstr(0,7,"0");
	ips114_showstr(120,5,"0");
	ips114_showstr(120,6,"0");
	ips114_showstr(120,7,"0");
					ips114_showstr(120,1,"0>");
	}
	if(move_ui==2)
		{	ips114_showstr(120,4,"0>");
	ips114_showstr(0,0,"0");
	ips114_showstr(0,2,"->");
	ips114_showstr(0,1,"0");
	ips114_showstr(0,3,"0");
	ips114_showstr(0,4,"0");
	ips114_showstr(0,5,"0");
	ips114_showstr(0,6,"0");
	ips114_showstr(0,7,"0");
	ips114_showstr(120,5,"0");
						ips114_showstr(120,1,"0>");
				ips114_showstr(120,6,"0");
	ips114_showstr(120,7,"0");
	}
	if(move_ui==3)
	{		ips114_showstr(120,4,"0>");
	ips114_showstr(0,0,"0");
	ips114_showstr(0,3,"->");
	ips114_showstr(0,1,"0");
	ips114_showstr(0,2,"0");
	ips114_showstr(0,4,"0");
	ips114_showstr(0,5,"0");
	ips114_showstr(120,1,"0>");
	ips114_showstr(0,6,"0");
	ips114_showstr(0,7,"0");
	ips114_showstr(120,5,"0");
	ips114_showstr(120,6,"0");
	ips114_showstr(120,7,"0");
	}
	if(move_ui==4)
		{ips114_showstr(120,4,"0>");
	ips114_showstr(0,0,"0");
	ips114_showstr(0,4,"->");
	ips114_showstr(0,1,"0");
	ips114_showstr(0,2,"0");
	ips114_showstr(0,3,"0");
	ips114_showstr(0,5,"0");
	ips114_showstr(0,6,"0");
	ips114_showstr(120,1,"0>");
	ips114_showstr(0,7,"0");
	ips114_showstr(120,5,"0");
	ips114_showstr(120,6,"0");
	ips114_showstr(120,7,"0");
	}
		
		if(move_ui==5)
		{ips114_showstr(120,4,"0>");
	ips114_showstr(0,0,"0");
	ips114_showstr(0,5,"->");
	ips114_showstr(0,1,"0");
	ips114_showstr(0,2,"0");
	ips114_showstr(0,3,"0");
	ips114_showstr(0,4,"0");
	ips114_showstr(0,7,"0");
	ips114_showstr(120,5,"0");
	ips114_showstr(0,6,"0");
	ips114_showstr(120,6,"0");
	ips114_showstr(120,7,"0");
	ips114_showstr(120,1,"0>");
	}
		
		if(move_ui==6)
		{ips114_showstr(120,4,"0>");
	ips114_showstr(0,0,"0");
	ips114_showstr(0,6,"->");
	ips114_showstr(0,1,"0");
	ips114_showstr(0,2,"0");
	ips114_showstr(0,3,"0");
	ips114_showstr(0,5,"0");
	ips114_showstr(0,4,"0");
	ips114_showstr(0,7,"0");
	ips114_showstr(120,5,"0");
	ips114_showstr(120,6,"0");
	ips114_showstr(120,7,"0");
	ips114_showstr(120,1,"0>");
	}
	
		if(move_ui==7)
		{ips114_showstr(120,4,"0>");
	ips114_showstr(0,0,"0");
	ips114_showstr(0,7,"->");
	ips114_showstr(0,1,"0");
	ips114_showstr(0,2,"0");
	ips114_showstr(0,3,"0");
	ips114_showstr(0,5,"0");
	ips114_showstr(0,4,"0");
	ips114_showstr(0,6,"0");
	ips114_showstr(120,5,"0");
	ips114_showstr(120,6,"0");
	ips114_showstr(120,7,"0");
	ips114_showstr(120,1,"0>");
	}
			if(move_ui==9)
		{ips114_showstr(120,4,"0>");
	ips114_showstr(0,0,"0");
	ips114_showstr(120,5,"->");
	ips114_showstr(0,1,"0");
	ips114_showstr(0,2,"0");
	ips114_showstr(0,3,"0");
	ips114_showstr(0,5,"0");
	ips114_showstr(0,4,"0");
	ips114_showstr(0,7,"0");
	ips114_showstr(0,6,"0");
	ips114_showstr(120,6,"0");
	ips114_showstr(120,7,"0");
						ips114_showstr(120,1,"0>");
	}
			if(move_ui==10)
		{ips114_showstr(120,4,"0>");
	ips114_showstr(0,0,"0");
	ips114_showstr(120,5,"0");
	ips114_showstr(0,1,"0");
	ips114_showstr(0,2,"0");
	ips114_showstr(0,3,"0");
	ips114_showstr(0,5,"0");
	ips114_showstr(0,4,"0");
	ips114_showstr(0,7,"0");
	ips114_showstr(0,6,"0");
	ips114_showstr(120,6,"->");
	ips114_showstr(120,7,"0");
	ips114_showstr(120,1,"0>");
	}
			if(move_ui==11)
		{
	ips114_showstr(120,4,"0>");
	ips114_showstr(0,0,"0");
	ips114_showstr(120,5,"0");
	ips114_showstr(0,1,"0");
	ips114_showstr(0,2,"0");
	ips114_showstr(0,3,"0");
	ips114_showstr(0,5,"0");
	ips114_showstr(0,4,"0");
	ips114_showstr(0,7,"0");
	ips114_showstr(0,6,"0");
	ips114_showstr(120,6,"0");
	ips114_showstr(120,7,"->");
	ips114_showstr(120,1,"0>");
	}
		
	
		if(move_ui==8)
		{
	ips114_showstr(120,4,"->");
	ips114_showstr(0,0,"0");
	ips114_showstr(120,5,"0");
	ips114_showstr(0,1,"0");
	ips114_showstr(0,2,"0");
	ips114_showstr(0,3,"0");
	ips114_showstr(0,5,"0");
	ips114_showstr(0,4,"0");
	ips114_showstr(0,7,"0");
	ips114_showstr(0,6,"0");
	ips114_showstr(120,6,"0");
	ips114_showstr(120,7,"0");
	ips114_showstr(120,1,"0>");
	}
		
		if(move_ui==12)
		{
	ips114_showstr(120,4,"0");
	ips114_showstr(0,0,"0");
	ips114_showstr(120,5,"0");
	ips114_showstr(0,1,"0");
	ips114_showstr(0,2,"0");
	ips114_showstr(0,3,"0");
	ips114_showstr(0,5,"0");
	ips114_showstr(0,4,"0");
	ips114_showstr(0,7,"0");
	ips114_showstr(0,6,"0");
	ips114_showstr(120,1,"->");
	ips114_showstr(120,6,"0");
	ips114_showstr(120,7,"0");
	}	
	
}
}

x_distence=center_gravityx[roi];

clean();
	

//	ips114_showint16(65,3,systick_getval()*6.00339E-06);
mt9v03x_finish_flag = 0;	 
		}						
	
}
	}
