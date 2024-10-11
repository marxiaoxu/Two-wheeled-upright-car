#include "motor.h"

int gyro_Y;
 int Move_Distence=0;
int Map_Angle=0;
int Map_turn=0,y_aflag=0;
void motor_Init()
{
	
	pwm_init(TIM_2, left_f,10000,0);      //初始化 电机 PWM
	pwm_init(TIM_2, left_z,10000,0);      //初始化 电机 PWM
	pwm_init(TIM_2, right_z,10000,0);      //初始化 电机 PWM
	pwm_init(TIM_2, right_f,10000,0);      //初始化 电机 PWM
//tim_encoder_init(TIM_1, PULSEA_pin, PULSEB_pin);
	
  tim_encoder_init(TIM_4, TIM_4_ENC1_B06, TIM_4_ENC2_B07);							// left初始化正交编码器采集      
	tim_encoder_init(TIM_3, TIM_3_ENC1_B04, TIM_3_ENC2_B05);							// right初始化正交编码器采集
	
}
void My_Init()
{
	
		board_init(true);		
		gpio_init(C7,GPI,GPIO_HIGH,GPI_PULL_UP);			
		icm20602_init_spi();
		ips114_init();
		ips114_showint16(150,7,1111);
		mt9v03x_init();	
		motor_Init();		
		gpio_init(D8,GPO,GPIO_LOW,GPO_PUSH_PULL);//蜂咛器
		key_Init();	
		ADRC_Init(&ADRC_GYRO_Controller,&ADRC_SPEED_Controller,&ADRC_SPEED_MIN_Controller);
	
	//	uart_init(UART_1,115200,UART1_TX_A09,UART1_TX_B06);//数据集传输  用了之后就没有值了   Speed_R没值
	
	
		uart_init(UART_4,9600,UART4_TX_C10,UART4_RX_C11);		
	
		ips114_clear(BLUE);//ADC3_CH11_C01
	
	
	
		tim_interrupt_init_ms(TIM_1,2,0X00);

	
	
}



float Yaw_angle()
{
	static float yaw_angle=0;
	get_icm20602_accdata_spi();
	yaw_angle=atan(sqrt(icm_acc_x*icm_acc_x+icm_acc_y*icm_acc_y)/icm_acc_z)*180/3.141593*1000;
	//yaw_angle=acos(icm_acc_z /4096.0)*180/3.141593;
	//	yaw_angle=+icm_acc_z;
	//yaw_angle=icm_acc_z;
	return yaw_angle;

}
	
void get_encoder()
{
	
		static  int left;
		static  int right; 
		right=tim_counter_get_count(TIM_3);//right
		//tim_encoder_rst(TIM_3);

		left=tim_counter_get_count(TIM_4);//left
		//tim_encoder_rst(TIM_4);
//		ips114_showint16(150,7,right);
//		 ips114_showint16(150,6,left);
}

int Get_Attitude()
{
	static int Angle=0;
	get_icm20602_accdata_spi();
	//θ = arctan(-Ax / sqrt(Ay^2 + Az^2)) 
	//Angle=atan(-icm_acc_x/sqrt((icm_acc_y*icm_acc_y+icm_acc_z*icm_acc_z)))**1.0 / 4096.0) * 180.0 / 3.141593) - 90-0.5)*1000
	Angle = ((acos((double)icm_acc_x * 1.0 / 4096.0) * 180.0 / 3.141593) - 90-0.5);//-3.5;//+10;
//		Angle = ((atan(-icm_acc_x/sqrt((icm_acc_y*icm_acc_y+icm_acc_z*icm_acc_z)) * 1.0 / 4096.0) * 180.0 / 3.141593) - 90-0.5)*1000;//-3.5;//+10;
//	ips114_showint16(2,4,Angle);
//	ips114_showint16(2,0,icm_acc_x);
	
	return Angle;
}


//int gyro_Y
float Get_Gyro()
{
	
static float Angle=0;

get_icm20602_gyro_spi();
	
//static float tempx=0,tempy=0,tempz=9.8;
//Angle=atan(-(icm_gyro_x-tempx)/sqrt(((icm_gyro_y-tempy)*(icm_gyro_y-tempy)+(icm_gyro_z-tempz)*(icm_gyro_z-tempz))));
//tempx=icm_gyro_x;
//tempy=icm_gyro_y;
//tempz=icm_gyro_z;
//Angle=IMUupdate(icm_gyro_x,icm_gyro_y,icm_gyro_z, icm_acc_x, icm_acc_y, icm_acc_z);
//Angle=cos(icm_gyro_x*0.048)+sin(icm_gyro_z*0.048);
gyro_Y=icm_gyro_y;
Angle=(icm_gyro_y);//*0.048;//*0.048;
//ips114_showint16(80,4,Angle*1000);
//ips114_showint16(80,0,icm_gyro_x);
//ips114_showint16(80,1,icm_gyro_y);	
//ips114_showint16(80,2,icm_gyro_z);	
return Angle;//*1000;	

}

void pwn_out(int speed,int final_speed,int turn)
{
	static int j=0;
	j++;
	
//			pwm_duty_updata(TIM_2,right_f,0);//you  1880
//			pwm_duty_updata(TIM_2,left_f,0);//zuo 2250
//			pwm_duty_updata(TIM_2,right_z,2000 );
//			pwm_duty_updata(TIM_2,left_z,2250);
//		if(turn>=10000)
//	turn=10000;
//	if(turn<=-10000)
//	turn=-10000;
//	
//			if(speed+turn>=5*10000)
//			{
//			turn=10000;
//			}

//			if(speed-turn<=-5*10000)
//			{
//			turn=-10000;
//			}
	
	
	
//		if((speed+turn)>=5*10000||(speed-turn)<=-5*10000)
//		turn=turn-5000;


	if(stop_flag==0)
	{		pwm_duty_updata(TIM_2,right_f,0);
			pwm_duty_updata(TIM_2,left_f,0);
			pwm_duty_updata(TIM_2,right_z,0 );
			pwm_duty_updata(TIM_2,left_z,0);
	}
	else
	
	{
		

		{
			
//			pwm_duty_updata(TIM_2,left_f,0);  //you z  no
//			pwm_duty_updata(TIM_2,right_z,0);//zuo z ok			
//			pwm_duty_updata(TIM_2,right_f,0);//zheng fan   no
//			pwm_duty_updata(TIM_2,left_z,0);//zuo f no
			
			
			if(speed<0)
	   
		{
			
			pwm_duty_updata(TIM_2,left_f,-final_speed+3500);	//you
			pwm_duty_updata(TIM_2,right_z,-final_speed+2900);			
			pwm_duty_updata(TIM_2,right_f,0);
			pwm_duty_updata(TIM_2,left_z,0);
		
			
			
		}
		if(speed>=0)
			{		
		

				
			pwm_duty_updata(TIM_2,right_f,final_speed-turn+3500);//you
			pwm_duty_updata(TIM_2,left_z,final_speed+turn+2300);			
			pwm_duty_updata(TIM_2,right_z,0);
			pwm_duty_updata(TIM_2,left_f,0);
		}
		


			

	}
	}
	
}

void map(int lef,int rig)
{
	Move_Distence+=-(lef+rig)/100;
if(Move_Distence>6000)
	Move_Distence=0;
if(Move_Distence<-6000)
	Move_Distence=0;
	//	ips114_showint16(90,4,Move_Distence);//3m=2570   
	
}
void get_map_angle()
{
	get_icm20602_gyro_spi();
	Map_Angle+=(icm_gyro_z)/100;
		//ips114_showint16(90,4,Move_Distence);//3m=2570  
	//ips114_showint16(90,5,Map_Angle);//90=220   
	
	
}




float Compute_Angle(void)//四元数
{
	
	float gx,gy, gz, ax, ay,az;
		gx=icm_gyro_x/131*2 ;
		gy=icm_gyro_y /131*2 ;
		gz=icm_gyro_z /131*2 ;

		ax=icm_acc_x /8192.0*2;
		ay=icm_acc_y /8192.0*2;
		az=icm_acc_z /8192.0*2;

 return  IMUupdate(gx/57.3,gy/57.3,gz/57.3,ax,ay,az);
 
}
//#define Pi 3.14159265f
//#define Kp 0.8f                       // 比例增益支配率收敛到加速度计/磁强计
//#define Ki 0.001f                // 积分增益支配率的陀螺仪偏见的衔接
//#define halfT 0.05f                // 采样周期的一半
#define Pi 3.14159265f
#define Kp 0.8f                       // 比例增益支配率收敛到加速度计/磁强计
#define Ki 0.001f                // 积分增益支配率的陀螺仪偏见的衔接
#define halfT 0.005f                // 采样周期的一半
float q0 = 1, q1 = 0, q2 = 0, q3 = 0;          // 四元数的元素，代表估计方向
float exInt = 0, eyInt = 0, ezInt = 0;        // 按比例缩小积分误差
 
float Yaw,Pitch,Roll;  //偏航角，俯仰角，翻滚角


 
float IMUupdate(float gx, float gy, float gz, float ax, float ay, float az)
{
    float norm;
	float vx, vy, vz;
	float ex, ey, ez;
//  static float static_error=0,flag=0;
//	if(flag<100)
//	{//static_error+=gz;
//	flag++;
//	}
//	if(flag==100)
//	{
//	gz=gz-static_error/100;

	

	norm = sqrt(ax*ax + ay*ay + az*az);	//把加速度计的三维向量转成单维向量   
	ax = ax / norm;
	ay = ay / norm;
	az = az / norm;

		//	下面是把四元数换算成《方向余弦矩阵》中的第三列的三个元素。 
		//	根据余弦矩阵和欧拉角的定义，地理坐标系的重力向量，转到机体坐标系，正好是这三个元素
		//	所以这里的vx vy vz，其实就是当前的欧拉角（即四元数）的机体坐标参照系上，换算出来的
		//	重力单位向量。
	vx = 2*(q1*q3 - q0*q2);
	vy = 2*(q0*q1 + q2*q3);
	vz = q0*q0 - q1*q1 - q2*q2 + q3*q3 ;

//if(y_aflag==1)
//{
//	exInt=0;
//	eyInt=0;
//	ezInt=0;
//	q0=0;
//	q1=0;
//	q2=0;
//	q3=0;
//}

	ex = (ay*vz - az*vy) ;
	ey = (az*vx - ax*vz) ;
	ez = (ax*vy - ay*vx) ;

	exInt = exInt + ex * Ki;
	eyInt = eyInt + ey * Ki;
	ezInt = ezInt + ez * Ki;

	gx = gx + Kp*ex + exInt;
	gy = gy + Kp*ey + eyInt;
	gz = gz + Kp*ez + ezInt;

	q0 = q0 + (-q1*gx - q2*gy - q3*gz) * halfT;
	q1 = q1 + ( q0*gx + q2*gz - q3*gy) * halfT;
	q2 = q2 + ( q0*gy - q1*gz + q3*gx) * halfT;
	q3 = q3 + ( q0*gz + q1*gy - q2*gx) * halfT;

	norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
	q0 = q0 / norm;
	q1 = q1 / norm;
	q2 = q2 / norm;
	q3 = q3 / norm;

//	return asin(2*(q0*q2 - q1*q3 )) * 57.2957795f; // 俯仰   换算成度
//	Roll = asin(2*(q0*q1 + q2*q3 )) * 57.2957795f; // 横滚

return atan2f(2*q1*q2+2*q0*q3,-2*q2*q2-2*q3*q3+1) * 57.2957795f;
	
//	}

//return 0;
}
