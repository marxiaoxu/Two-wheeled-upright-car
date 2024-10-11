#include "headfile.h"
#include "dfs.h"
int link_domain_label(unsigned char imagedata[],unsigned char buff[])
{
	#define HEIGHT 120
	#define WIDTH 188
	int x,y,i,domain_num=0;
	unsigned long offset;
	for(i=0;i<WIDTH*HEIGHT;i++)  
	buff[i]=0;
	i=1;
	for(offset=0;offset<HEIGHT*WIDTH;offset++)
	{
		x=offset%WIDTH;
		y=offset/WIDTH;
		if(y==0)//��0��
		{
			 if(x==0)//��0�е�0��
			 {
				 if(imagedata[offset]==255)//�����0����ֵ������䵽����һ
				 {
					 buff[offset]=i;
					 domain_num++;//��ͨ��������һ
				 }
			 }else//����ǵ�0�е�������
			 {
				 if(imagedata[offset]==255)//�����ֵ
				 {

					 if(imagedata[offset-1]==255)//�������ǰһ����ֵ����������������ǰһ�����ͨ��
					 {
						 i=buff[offset-1];//��ȡǰһ�����ͨ����ţ�����i
						 buff[offset]=i;//���õ㸳��iָ������ͨ��
					 }else//�������ǰһ��û��ֵ�������鵽��һ����ͨ��
					 {
					    domain_num++;//��ͨ��������һ
					    i=domain_num;
					    buff[offset]=i;//�������Ϊi��ͨ��
	                 }
				 }
			 }
		}else if(x==0&&y>0)//����ǵ�һ���µ��к͵�0�У���ֻ������Ϸ��������Ϸ��ĵ�
		{
			if(imagedata[offset]==255)//�����ֵ
			{
				if(imagedata[x+(y-1)*WIDTH]==255)//������Ϸ��ĵ���ֵ�����������Ϸ�����������ͨ����
				{
					i=buff[x+(y-1)*WIDTH];//�Ϸ������ͬ������
					buff[offset]=i;//���˵�������Ϸ������ͬ��
				}else if(imagedata[x+1+(y-1)*WIDTH]==255)//���������Ϸ��ĵ㣬������Ϸ��ĵ���ֵ
				{
					i=buff[x+1+(y-1)*WIDTH];//���Ϸ������ͬ������
					buff[offset]=i;//���˵���������Ϸ������ͬ��			
				}else //������Ϸ��ĵ�����Ϸ��ĵ㶼û��ֵ��������һ����ͬ��
				{
				    domain_num++;//��ͨ��������һ
				    i=domain_num;
				    buff[offset]=i;//�������Ϊi��ͨ��
				}
			}
		}else if(x==(WIDTH-1)&&y>0)//����ǿ��������0�����µĵ�
		{
			if(imagedata[offset]==255)//����˵���ֵ
			{
				if(imagedata[offset-1]==255)//�������ǰһ����ֵ������������ǰһ�����ͬ����
				{
					i=buff[offset-1];//��ȡǰһ�����ͨ����ţ�����i
					buff[offset]=i;//���õ㸳��iָ������ͨ��
				}else if(imagedata[x-1+(y-1)*WIDTH]==255)//������������Ϸ���ֵ���������������Ϸ�����ͬ����
				{
					i=buff[x-1+(y-1)*WIDTH];//��ȡ���Ϸ������ͨ����ţ�����i
					buff[offset]=i;//���õ㸳��iָ������ͨ��
				}else if(imagedata[x+(y-1)*WIDTH]==255)//����������Ϸ��ĵ���ֵ������������Ϸ��ĵ����ͬ����
				{
					i=buff[x+(y-1)*WIDTH];//�Ϸ������ͬ������
					buff[offset]=i;//���˵�������Ϸ������ͬ��
				}else//����ǰ�������Ϸ����Ϸ��ĵ㶼û��ֵ����������ͬ��
				{
					domain_num++;//��ͨ��������һ
					i=domain_num;
				   buff[offset]=i;//�������Ϊi��ͨ��
				}
			}
		}else //��������������ĵ�
		{
			if(imagedata[offset]==255)//����˵���ֵ
			{
				if(imagedata[offset-1]==255)//�������ǰһ����ֵ������������ǰһ�����ͬ����
				{
					i=buff[offset-1];//��ȡǰһ�����ͨ����ţ�����i
					buff[offset]=i;//���õ㸳��iָ������ͨ��
					if(imagedata[x+(y-1)*WIDTH]==255)//����������Ϸ��ĵ㣬����Ϸ�����ֵ
					{
					   //if(buff[x+(y-1)*WIDTH]<buff[offset])//����Ϸ��ĵ�
					}else if(imagedata[x+1+(y-1)*WIDTH]==255)//������������Ϸ�����ֵ
					{
						if(buff[x+1+(y-1)*WIDTH]<buff[offset])//������Ϸ��ĵ�������С
						{
							for(i=0;i<WIDTH*HEIGHT;i++)//�������е����ڱ�����ͨ��ĵ㶼�鵽���Ϸ��ĵ����ͨ��
							{
								if(buff[i]==buff[offset])
								{
									buff[i]=buff[x+1+(y-1)*WIDTH];
								}else if(buff[i]>buff[offset])//���д��ڱ������ͨ����ŵ���ͨ������Լ�1
								{
									buff[i]--;
								}
							}
							domain_num--;//��ͨ����ż�1
					    }else if(buff[x+1+(y-1)*WIDTH]>buff[offset])//������֮
						{
							for(i=0;i<WIDTH*HEIGHT;i++)
							{
								if(buff[i]==buff[x+1+(y-1)*WIDTH])
								{
									buff[i]=buff[offset];
								}else if(buff[i]>buff[x+1+(y-1)*WIDTH])
								{
									buff[i]--;
								}
							}
							domain_num--;//��ͨ����ż�1
						}
					}
				 }else if(imagedata[x-1+(y-1)*WIDTH]==255)//������������Ϸ���ֵ���������������Ϸ�����ͬ����
				 {
					i=buff[x-1+(y-1)*WIDTH];//��ȡ���Ϸ������ͨ����ţ�����i
					buff[offset]=i;//���õ㸳��iָ������ͨ��
					if(imagedata[x+1+(y-1)*WIDTH]==255)//������������Ϸ��ĵ�
					{
						if(buff[x+1+(y-1)*WIDTH]<buff[offset])//������Ϸ��ĵ�������С
						{
							for(i=0;i<WIDTH*HEIGHT;i++)//�������е����ڱ�����ͬ��ĵ㶼�鵽���Ϸ��ĵ����ͬ��
							{
								if(buff[i]==buff[offset])
								{
									buff[i]=buff[x+1+(y-1)*WIDTH];
								}else if(buff[i]>buff[offset])//���д��ڱ�����ͨ����ŵ���ͨ������Լ�1
								{
									buff[i]--;
								}
							}
							domain_num--;//��ͨ����ż�1
						}else if(buff[x+1+(y-1)*WIDTH]>buff[offset])//������֮
						{
							for(i=0;i<WIDTH*HEIGHT;i++)
							{
								if(buff[i]==buff[x+1+(y-1)*WIDTH])
								{
									buff[i]=buff[offset];
								}else if(buff[i]>buff[x+1+(y-1)*WIDTH])
								{
									buff[i]--;
								}
							}
							domain_num--;//��ͨ����ż�1
						}
				     }
				}else if(imagedata[x+(y-1)*WIDTH]==255)//����������Ϸ��ĵ���ֵ������������Ϸ��ĵ����ͬ����
				{
						i=buff[x+(y-1)*WIDTH];//�Ϸ������ͬ������
						buff[offset]=i;//���˵�������Ϸ������ͬ��
				}else if(imagedata[x+1+(y-1)*WIDTH]==255)//������������Ϸ��ĵ���ֵ������鵽�����Ϸ������ͨ����
				{
					i=buff[x+1+(y-1)*WIDTH];//���Ϸ������ͬ������
					buff[offset]=i;//���˵���������Ϸ������ͬ��
				}else //������ϼ�ⶼû��ֵ��������ͬ��
				{
					domain_num++;//��ͨ��������һ
					i=domain_num;
					buff[offset]=i;//�������Ϊi��ͨ��
				}
		    }
	     }
     }
	return domain_num;
}

int Get_Roi(unsigned char image[][188],int temp)//�õ�roi
{
	static int max_count=0; 
static  int max_Count=0,flag=0; 
    for (uint8 i = ((uint8)x1_0); i < ((uint8)x2_120); ++i)

        for (uint8 j = ((uint8)y1_0); j < ((uint8)y2_188); ++j)
	{
	for(int x=temp;x>0;x--) 
		{
			/**********************��ȡ���Ϻ���������************************/
			if(image[i][j]==x) 
		{
				
//if(bianyan_tx[i][j]==0/*224*/) //binarization3(96, 192, 224,copy_tuxiang);//160
// 
//	{boundary_number[x]++;}//�߽����
//	
	

		
			if(copy_tuxiang2[i][j]>max_light[x]) 
			{
				max_light[x]=copy_tuxiang2[i][j]; //�������			  
			}
			average[x]+=copy_tuxiang2[i][j]; 
			
			
			if(i<left_upx[x])
			{				
				left_upx[x]=i; 
			}
			if(i>left_upy[x])
			{			
			
				left_upy[x]=i; 
			
			}
			if(j>	right_downx[x])
			{
		
				right_downx[x]=j;	
			}	
				if(j<right_downy[x])
			{
				
				right_downy[x]=j;	
			}	
			//if(copy_tuxiang2[i][j]!=0)
			{
			center_gravityx[x]+=j; //��������
			center_gravityy[x]+=i; 
				count[x]++;	//��ʵ���,ÿ����ͨ������ظ���
			}
	   }
		/**********************��ȡ���Ϻ���������************************/		 
	 }
  }		

	 max_count=0;
	
		for(int x=temp;x>0;x--)
	{
	
		if(count[x]>max_count/*&&max_light[x]==255*/)
		{		max_count=count[x];
		max_Count=x;}
		
	}
	
	
			
	for(int x=temp;x>0;x--)
	{
	
		if(count[x]>max_count/*&&max_light[x]==255*/)
		{		max_count=count[x];
		max_Count=x;}
	}
	
	
	

	
for(int y=1;y>0;y--)//��ȡ����ʱʹ��
	{
	int x=temp;//��ȡ����ʱʹ��

	 static double out[1];	
   average[x]=average[x]/count[x];
	 center_gravityx[x]=center_gravityx[x]/count[x];
	 center_gravityy[x]=center_gravityy[x]/count[x];

	

		date[0]=right_downx[x];//��

		date[1]=left_upx[x]; //��	

		date[2]=right_downy[x];//��

		date[3]=left_upy[x];//��

		date[4]=center_gravityx[x];		//ƫ��	

		date[5]=center_gravityy[x];//����

		date[6]=max_light[x];

		date[7]=average[x];

		date[8]=/*(date[3]-date[1])+(date[2]-date[0]);*/boundary_number[x];//�߽����

		date[9]=count[x];

			


//			
//	if(temp3){
//						ips114_showfloat(180,0,show3,1,4);
//							}



							

			
		if(left_upy[max_Count]>70&&count[max_Count]>600&&max_light[max_Count]==255)
		{		
						if(x!=max_Count)
		
	{
	 center_gravityx[max_Count]=center_gravityx[max_Count]/count[max_Count];
	 center_gravityy[max_Count]=center_gravityy[max_Count]/count[max_Count];
	}		
					
			return max_Count;
				
		}

	return x;
		



			}
				max_Count=0;
	return 0;
}
