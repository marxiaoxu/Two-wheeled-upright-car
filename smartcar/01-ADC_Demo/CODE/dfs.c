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
		if(y==0)//第0行
		{
			 if(x==0)//第0列第0行
			 {
				 if(imagedata[offset]==255)//如果第0点有值则将其分配到区域一
				 {
					 buff[offset]=i;
					 domain_num++;//联通域数量增一
				 }
			 }else//如果是第0行的其它点
			 {
				 if(imagedata[offset]==255)//如果有值
				 {

					 if(imagedata[offset-1]==255)//如果它的前一点有值，则将它归属到它的前一点的联通域
					 {
						 i=buff[offset-1];//获取前一点的联通域序号，传给i
						 buff[offset]=i;//将该点赋给i指定的联通域
					 }else//如果它的前一点没有值，则将它归到另一个联通域
					 {
					    domain_num++;//联通域数量增一
					    i=domain_num;
					    buff[offset]=i;//将它标记为i联通域
	                 }
				 }
			 }
		}else if(x==0&&y>0)//如果是第一行下的行和第0列，则只检测其上方及其右上方的点
		{
			if(imagedata[offset]==255)//如果有值
			{
				if(imagedata[x+(y-1)*WIDTH]==255)//如果其上方的点有值则将它归属到上方点所属的连通域里
				{
					i=buff[x+(y-1)*WIDTH];//上方点的连同域的序号
					buff[offset]=i;//将此点归属到上方点的连同域
				}else if(imagedata[x+1+(y-1)*WIDTH]==255)//则检测其右上方的点，如果右上方的点有值
				{
					i=buff[x+1+(y-1)*WIDTH];//右上方点的连同域的序号
					buff[offset]=i;//将此点归属到右上方点的连同域			
				}else //如果在上方的点和右上方的点都没有值，则另设一个连同域
				{
				    domain_num++;//联通域数量增一
				    i=domain_num;
				    buff[offset]=i;//将它标记为i联通域
				}
			}
		}else if(x==(WIDTH-1)&&y>0)//如果是靠最右则第0行以下的点
		{
			if(imagedata[offset]==255)//如果此点有值
			{
				if(imagedata[offset-1]==255)//如果它的前一点有值，则将它规属到前一点的连同域里
				{
					i=buff[offset-1];//获取前一点的联通域序号，传给i
					buff[offset]=i;//将该点赋给i指定的联通域
				}else if(imagedata[x-1+(y-1)*WIDTH]==255)//否则如果其左上方有值，则将它归属到左上方的连同域里
				{
					i=buff[x-1+(y-1)*WIDTH];//获取左上方点的联通域序号，传给i
					buff[offset]=i;//将该点赋给i指定的联通域
				}else if(imagedata[x+(y-1)*WIDTH]==255)//否则如果其上方的点有值，则归属到其上方的点的连同域里
				{
					i=buff[x+(y-1)*WIDTH];//上方点的连同域的序号
					buff[offset]=i;//将此点归属到上方点的连同域
				}else//它的前方，左上方，上方的点都没有值，则另设连同域
				{
					domain_num++;//联通域数量增一
					i=domain_num;
				   buff[offset]=i;//将它标记为i联通域
				}
			}
		}else //如果是其它正常的点
		{
			if(imagedata[offset]==255)//如果此点有值
			{
				if(imagedata[offset-1]==255)//如果它的前一点有值，则将它规属到前一点的连同域里
				{
					i=buff[offset-1];//获取前一点的联通域序号，传给i
					buff[offset]=i;//将该点赋给i指定的联通域
					if(imagedata[x+(y-1)*WIDTH]==255)//继续检测其上方的点，如果上方点有值
					{
					   //if(buff[x+(y-1)*WIDTH]<buff[offset])//如果上方的点
					}else if(imagedata[x+1+(y-1)*WIDTH]==255)//否则如果其右上方才有值
					{
						if(buff[x+1+(y-1)*WIDTH]<buff[offset])//如果右上方的点的域序号小
						{
							for(i=0;i<WIDTH*HEIGHT;i++)//则将其所有的属于本点连通域的点都归到右上方的点的连通域
							{
								if(buff[i]==buff[offset])
								{
									buff[i]=buff[x+1+(y-1)*WIDTH];
								}else if(buff[i]>buff[offset])//所有大于本点的连通域序号的连通域序号自减1
								{
									buff[i]--;
								}
							}
							domain_num--;//连通域序号减1
					    }else if(buff[x+1+(y-1)*WIDTH]>buff[offset])//否则则反之
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
							domain_num--;//连通域序号减1
						}
					}
				 }else if(imagedata[x-1+(y-1)*WIDTH]==255)//否则如果其左上方有值，则将它归属到左上方的连同域里
				 {
					i=buff[x-1+(y-1)*WIDTH];//获取左上方点的联通域序号，传给i
					buff[offset]=i;//将该点赋给i指定的联通域
					if(imagedata[x+1+(y-1)*WIDTH]==255)//继续检测其右上方的点
					{
						if(buff[x+1+(y-1)*WIDTH]<buff[offset])//如果右上方的点的域序号小
						{
							for(i=0;i<WIDTH*HEIGHT;i++)//则将其所有的属于本点连同域的点都归到右上方的点的连同域
							{
								if(buff[i]==buff[offset])
								{
									buff[i]=buff[x+1+(y-1)*WIDTH];
								}else if(buff[i]>buff[offset])//所有大于本点连通域序号的连通域序号自减1
								{
									buff[i]--;
								}
							}
							domain_num--;//连通域序号减1
						}else if(buff[x+1+(y-1)*WIDTH]>buff[offset])//否则则反之
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
							domain_num--;//连通域序号减1
						}
				     }
				}else if(imagedata[x+(y-1)*WIDTH]==255)//否则如果其上方的点有值，则归属到其上方的点的连同域里
				{
						i=buff[x+(y-1)*WIDTH];//上方点的连同域的序号
						buff[offset]=i;//将此点归属到上方点的连同域
				}else if(imagedata[x+1+(y-1)*WIDTH]==255)//否则如果其右上方的点有值，则将其归到其右上方点的连通域里
				{
					i=buff[x+1+(y-1)*WIDTH];//右上方点的连同域的序号
					buff[offset]=i;//将此点归属到右上方点的连同域
				}else //如果以上检测都没有值，则另建连同域
				{
					domain_num++;//联通域数量增一
					i=domain_num;
					buff[offset]=i;//将它标记为i联通域
				}
		    }
	     }
     }
	return domain_num;
}

int Get_Roi(unsigned char image[][188],int temp)//得到roi
{
	static int max_count=0; 
static  int max_Count=0,flag=0; 
    for (uint8 i = ((uint8)x1_0); i < ((uint8)x2_120); ++i)

        for (uint8 j = ((uint8)y1_0); j < ((uint8)y2_188); ++j)
	{
	for(int x=temp;x>0;x--) 
		{
			/**********************提取左上和右下坐标************************/
			if(image[i][j]==x) 
		{
				
//if(bianyan_tx[i][j]==0/*224*/) //binarization3(96, 192, 224,copy_tuxiang);//160
// 
//	{boundary_number[x]++;}//边界个数
//	
	

		
			if(copy_tuxiang2[i][j]>max_light[x]) 
			{
				max_light[x]=copy_tuxiang2[i][j]; //最大亮度			  
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
			center_gravityx[x]+=j; //重心坐标
			center_gravityy[x]+=i; 
				count[x]++;	//真实面积,每个连通域的像素个数
			}
	   }
		/**********************提取左上和右下坐标************************/		 
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
	
	
	

	
for(int y=1;y>0;y--)//提取特征时使用
	{
	int x=temp;//提取特征时使用

	 static double out[1];	
   average[x]=average[x]/count[x];
	 center_gravityx[x]=center_gravityx[x]/count[x];
	 center_gravityy[x]=center_gravityy[x]/count[x];

	

		date[0]=right_downx[x];//左

		date[1]=left_upx[x]; //上	

		date[2]=right_downy[x];//右

		date[3]=left_upy[x];//下

		date[4]=center_gravityx[x];		//偏差	

		date[5]=center_gravityy[x];//距离

		date[6]=max_light[x];

		date[7]=average[x];

		date[8]=/*(date[3]-date[1])+(date[2]-date[0]);*/boundary_number[x];//边界个数

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
