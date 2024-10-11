#include "PID.H"//50000   0-5000

//******************************************************************************//

float GyroP=5; //5
float GyroI=14.;//7
float GyroD=0;


float AngleP=60;
float AngleD=0;


float SpeedP=-85;//3.5
float SpeedI=-5;//100
float Speed_PID_speed=1500; //1850


float loss_turn=32;//64

float turn_kp=-10;//-10
float turn_kd=-0;


float turn_kp2=-200;//150
float turn_kd2=-50;

float turnkp2=0,turnkd2=0;//分段pd

float dt_turn_kp2=-0; //fuzzy
float dt_turn_kd2=-0 ;








float Gyro_PID(float Gyro_Data,float Gyro_m)
{
		//static float Gyro_Error_Count=0;
	static	float Realize=0,Gyro_Error=0,last_gyro_error=0,LAST_Gyro_Data=0,Gyro_Error_Count=0;
		Gyro_Data=0.75*Gyro_Data+0.25*LAST_Gyro_Data;
      //偏差计算
	
	//	ips114_showint16(0,3,Gyro_Data);
	//ips114_showint16(0,4,Gyro_m);
		if(Gyro_Data>-20&&Gyro_Data<20)
		Gyro_Data=0;
				LAST_Gyro_Data=Gyro_Data;
      Gyro_Error = Gyro_m - Gyro_Data;

  Realize += GyroP*(Gyro_Error-last_gyro_error) /*+  GyroI /100* Gyro_Error_Count*/+GyroI/100 * Gyro_Error;//Z增量式pi 
      //位置PID计算
		

//		
		
		last_gyro_error=Gyro_Error;
	if(Realize>35000)
		Realize=35000;
		if(Realize<-35000)
		Realize=-35000;


      return Realize;
}


float Angle_PID(float Angle_Data,float Angle_m,float balance_angle)
{
    static float Angle_Error_Least=0;
    static  float Angle_Error=0,Realize=0;
      
      //偏差计算
      Angle_Error = Angle_m - Angle_Data - balance_angle;
    //      Angle_Error = -3 - Angle_Data - balance_angle;
      Realize = AngleP * Angle_Error + AngleD * (Angle_Error - Angle_Error_Least);
      
      //更新上一次的偏差
      Angle_Error_Least = Angle_Error;

      if(Realize>20000)
				Realize=20000;
			if(Realize<-20000)
				Realize=-20000;
      return Realize;
}

float Speed_PID(float Speed_New,float Speed_m,int speeed_low)
{
    static float Speed_Error_Integral=0;
    static  float Speed_Error=0,Realize=0,last_error=0;
	  static float PreError[10]={0};
   static float max=0;
		
		
////	if(speeed_low==0)
//	{
//		Speed_m=Speed_m;
//		
//	}
//	
//		if(speeed_low==1)//近灯
//	{
//		Speed_m=Speed_m*0.8;
//		
//	}
//	
//			if(speeed_low==2)//
//	{
//		Speed_m=Speed_m*0.5;
//		
//	}
//	
	
//	
//	
//			if(speeed_low==2)
//	{
//		Speed_m=Speed_m*0.8;
//		
//	}
	
	
		
		Fhan_ADRC(&ADRC_SPEED_MIN_Controller,(float)Speed_New); //td微分器


      Speed_Error = Speed_m - Speed_New;
      		
if(Speed_Error>1400)
	
			{	Realize = SpeedP * Speed_Error/5000;
Speed_Error_Integral=0;}

			
			else

			{				

		Speed_Error_Integral+= Speed_Error*0.8+0.2*last_error;	 //不完全微分

					 
	if(Speed_Error_Integral>=8000) Speed_Error_Integral=8000;
	if(Speed_Error_Integral<=-8000) Speed_Error_Integral=-8000;
		Realize = SpeedP * Speed_Error/5000 + Speed_Error_Integral/5000* SpeedI/200  ;//位置式
				
				
			}
			
	
    // Realize += SpeedP * (Speed_Error-last_error)/5000 + Speed_Error/5000* SpeedI ;//增量式
						last_error=Speed_Error;
     // ips114_showint16(65,2,Realize);//85
      if(Realize>46) Realize=46;
      if(Realize<-46) Realize=-46;
      last_error=Speed_Error;	//ips114_showint16(65,2,Realize);
      return Realize;
}


float In_Turn(int gyro_Z,int gyro_z)
{
	
  static float PWM_out=0;
	static float error=0,last_error=0;
  //static float last=0;
//		data_conversion(gyro_Z,gyro_z,0,0, virtual_scope_data);//使用虚拟示波器数据转换函数转换数据，至多同时转换四个数据
//     uart_putbuff(UART_1,virtual_scope_data,10);  //数据转换完成后，使用串口发送将数组的内容发送出去
	error=gyro_Z-gyro_z;
  PWM_out = (turn_kp)*error +turn_kd*(error-last_error)*15; 
  last_error=error;
	if(PWM_out>=12000)
		PWM_out=12000;
	if(PWM_out<=-12000)
		PWM_out=-12000;
	
	
	

  return PWM_out;
}

float out_Turn(int gyro_z)
{
	
	
	
 static float PWM_out=0,last_gyro_z=0;
	
	
	PWM_out = (turn_kp2)*gyro_z +turn_kd2*(gyro_z-last_gyro_z);  
//	PWM_out = (turnkp2)*gyro_z +turn_kd2*(gyro_z-last_gyro_z);  
	last_gyro_z=gyro_z;
	
		if(PWM_out>20000)
		PWM_out=20000;
	if(PWM_out<-20000)
		PWM_out=-20000;

  return PWM_out;
}
float Speed_Measure()
{
		static float 		Speed_New=0,left=0,right=0,Last_Speed_New=0;
		right=tim_counter_get_count(TIM_3);
		tim_encoder_rst(TIM_3); 


		left=-tim_counter_get_count(TIM_4);
		tim_encoder_rst(TIM_4);
		

	 // left=right;
      Speed_New = (left + right)/2;//10000
	//	show1=Speed_New;

	    Speed_New=0.8*Speed_New+0.2*Last_Speed_New;
    	Last_Speed_New=Speed_New;

	Fhan_ADRC(&ADRC_SPEED_MIN_Controller,(float)Speed_New);  //对当前速度进行TD过渡
	
	
	//turn_kp2=-(1.87e-7*Speed_New*Speed_New*Speed_New - 4.11e-4*Speed_New*Speed_New + 0.353*Speed_New + 78.1);
	//turn_kp2=-(1.98e-7*Speed_New*Speed_New*Speed_New- 4.16e-4*Speed_New*Speed_New + 0.349*Speed_New + 67.0);
if(Speed_New<=1600)
turnkp2=turn_kp2;//170

	if(Speed_New>1600)
turnkp2=turn_kp2+(Speed_New-1600)/9;
	
return Speed_New;
}

