#include "karman.h"
float Kal_Gyro;
float gyro;
int mmax, mmaz;
float angle, angleSpeed;
float Angle_Kalman;
int Pre_Angle_Kalman;
float angleSpeedIntegral;
 
float Q_bias, Angle_err;
float PCt_0, PCt_1, E;
float K_0, K_1, t_0, t_1;
float Pdot[4] ={0,0,0,0};
float PP[2][2] = { { 1, 0 },{ 0, 1 } };



struct _filter groy_filter[1];

double iib[7]={4.863987500781e-08,2.918392500469e-07,7.295981251171e-07,9.727975001562e-07,
  7.295981251171e-07,2.918392500469e-07,4.863987500781e-08};
double iia[7]={1,   -5.514535121166,    12.68911305652,    -15.5936352107,
      10.79329667049,   -3.989359404231,   0.6151231220526};


#define dt 0.005
			
//#define R_angle     0.005 
//float C_0=1.0;
//#define Q_angle    0.025//0.025 //0.01  //�Ƕ����� Խ������Խ������� �� ����Ҳ��0.001   0.015
//#define Q_gyro      0.005//Ư������//ԽС���߸������Խ����
			
			
#define R_angle    0.5
float C_0=1.0;
#define Q_angle    0.2//0.025 //0.01  //�Ƕ����� Խ������Խ������� �� ����Ҳ��0.001   0.015
#define Q_gyro      0.1//Ư������//ԽС���߸������Խ����



//float  Q_angle=0.2;  //1--0.001 ����������Э����
//                        //��ֵԽС���仯Խ��
//float  Q_gyro =0.1;  //0.3--0.003 ����������Э���� ����������Э����Ϊһ��һ�����о���,
//                        //��ֵԽС���仯Խ��
//float  R_angle=0.5;    //0.01--0.5   ����������Э���� �Ȳ���ƫ��
//                        //��ֵԽС���仯Խ��

/**
 * @brief  �������˲�, ������������Ĳ�����, ���ؿɿ��Ĳ�����, �˴����ڻ�ñ仯���ȶ��ĽǶ�ֵ
 * @param[in]  Accel �ɼ��ٶȼƵõ��ĽǶȲ���
 * \param[in]  Gyro �������ǵõ��Ľ��ٶȲ���
 * @retval �ȶ��ɿ��ĽǶ�ֵ, ����ֱ������
 */
 
float KalmanFilter(float Accel,float Gyro)		
{
    static float Angle = 0, Gyro_y = 0;

	Angle+=(Gyro - Q_bias) * dt; //�������
 
	Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-����������Э�����΢��
 
	Pdot[1] = -PP[1][1];
	Pdot[2] = -PP[1][1];
	Pdot[3]= Q_gyro;
	
	PP[0][0] += Pdot[0] * dt;   // Pk-����������Э����΢�ֵĻ���
	PP[0][1] += Pdot[1] * dt;   // =����������Э����
	PP[1][0] += Pdot[2] * dt;
	PP[1][1] += Pdot[3] * dt;
		
	Angle_err = Accel - Angle;	//zk-�������
	
	PCt_0 = C_0*PP[0][0];
	PCt_1 = C_0*PP[1][0];
	
	E = R_angle + C_0*PCt_0;
	
	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;
	
	t_0 = PCt_0;
	t_1 = C_0*PP[0][1];
 
	PP[0][0] -= K_0 * t_0;		 //����������Э����
	PP[0][1] -= K_0 * t_1;
	PP[1][0] -= K_1 * t_0;
	PP[1][1] -= K_1 * t_1;
		
	Angle	+= K_0 * Angle_err;	 //�������
	Q_bias	+= K_1 * Angle_err;	 //�������
	Gyro_y   = Gyro - Q_bias;	 //���ֵ(�������)��΢��=���ٶ�
	return Angle;
}





double IIRLowPass(double x, struct _filter *Acc)
{
	int i;
	//����֮ǰBuf��ǰ�ƶ�һ��λ�ã��Ա���֮ǰBuf������;
	for(i=6; i>0; i--){
		Acc->outBuf[i] = Acc->outBuf[i-1];
		Acc->inBuf[i] = Acc->inBuf[i-1];
	}
	Acc->inBuf[0] = x;
	Acc->outBuf[0] = 0;
	for(i=1;i<7;i++)
	{
		Acc->outBuf[0] = Acc->outBuf[0] + iib[i] * Acc->inBuf[i];
		Acc->outBuf[0] = Acc->outBuf[0] - iia[i] * Acc->outBuf[i];
	}
	Acc->outBuf[0] = Acc->outBuf[0] + iib[0] * Acc->inBuf[0];
	return Acc->outBuf[0];
}




