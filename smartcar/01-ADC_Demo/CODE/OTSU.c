#include "OTSU.h"
#include "math.h"



/*******************ȫ�ֶ�̬��ֵ�������*************************************************/
#define GrayScale 256   //frame�Ҷȼ�

typedef unsigned char uchar;
int pixel[256]={0};  //�����־λ���ܶ����ں����ڲ�����Ϊ��һ�������飬�ٶ� �����飬�ֲ����������bug�� ��ע���£��ҵ�ʱ����������������졣
 
/*********�����ֵ�ָ���Ż���********************/
//�������ͣ��� �� ͼ��ָ�� ��ʼ��  ��ʼ�� �����д�С  �����д�С
int MyOSTU(int width,int height,uint8 *Image)
{
	int threshold1=0;
	int32_t sum_gray=0;
	int32_t sum_pix_num=0;
	int32_t pl_pix_num=0;
	int32_t p2_pix_mum=0;
	int32_t p1_sum_gray=0;
	float m1=0;
	float m2=0;
	float V=0;
	float variance=0;
	int i,j,k=0;
	
	for(i = 0;i<256;i++)
		pixel[i] = 0;
	
	//ͳ��ÿ���Ҷȼ������صĸ���   
    for(i = 0; i < height; i++)  
    {  
        for(j = 0;j < width;j++)  
        {  
            pixel[(int)Image[i * width + j]]++;  
        }  
    } 

		for(k=0;k<GrayScale;k++)
		{
			sum_gray+=k*pixel[k];//�Ҷ�ֱ��ͼ������
			sum_pix_num+=pixel[k];//�����ظ���
		}	
		
		for(k=0;k<GrayScale-1;k++)
		{
			pl_pix_num+=pixel[k];//��һ�������ظ���
			p2_pix_mum=sum_pix_num-pl_pix_num;//�ڶ��������ظ���
			p1_sum_gray+=k*pixel[k];   //��һ����������
			m1=(float)p1_sum_gray/pl_pix_num;//��һ���ֻҶȾ�ֵ
			m2=(float)(sum_gray-p1_sum_gray)/p2_pix_mum;//�ڶ����ֻҶȾ�ֵ
			
			V=pl_pix_num*p2_pix_mum*(m1-m2)*(m1-m2);
			
			if(V>variance)//����䷽��ϴ�ʱ�ĻҶ�ֵ��Ϊ��ֵ
			{
				variance=V;
				threshold1=k;
			}
		}
		return threshold1;
}

/************************��˸ʶ��***************************/
float process_curvity(int x1, int y1, int x2, int y2, int x3, int y3)
{
    float K;
    int S_of_ABC = ((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)) / 2;
    //����ķ��ű�ʾ����
    int q1 = (int)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    int AB = sqrt(q1);
    q1 = (int)((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
    int BC = sqrt(q1);
    q1 = (int)((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1));
    int AC = sqrt(q1);
    if (AB * BC * AC == 0)
    {
        K = 0;
    }
    else
        K = (float)4 * S_of_ABC / (AB * BC * AC);
    return K;
}

