#include "image_handle.h"
void fuck_image(int hang_s,int hang_e,uint8 image[][188])
{int i, j;
 for(i=hang_s;i>=hang_e;i--)
				{  //16

								for (j = 0; j < 188; j++)
								{
									image[i][j]=0;

								}
				}



}
	
void get_linex(int x,int s,int e,uint8 image[][188])
{
//	if(x!=0&&x!=187)
    for (int j = s; j >= e ; j--)
    {
        image[j][x] = 255;

    }

}
void get_liney(int y,int s,int e, uint8 image[][188])
{
//	if(y!=0&&y!=187)
    for (int j = s; j >= e; j--)
    {
        image[y][j] = 255;

    }

}




void copy(uint8  SrcImg[][188], uint8  CannyImg[][188])
{
	
	
	
  for (uint8 i = ((uint8)x1_0); i < ((uint8)x2_120); ++i)

        for (uint8 j = ((uint8)y1_0); j < ((uint8)y2_188); ++j)
									SrcImg[i][j]=CannyImg[i][j];

												
	}

	
	
	
void two_piecture(uint8 SrcImg[][188], uint8 CannyImg[][188])
{
	
				int i, j;
				for (i = 0; i < 120; i++)
				{

								for (j = 0; j < 188; j++)
								{
									CannyImg[i][j]|=SrcImg[i][j];

								}
								
				}
		}

void picture_255(uint8 SrcImg[][188])
{
	
				int i, j;
				for (i = 0; i < 120; i++)
				{

								for (j = 0; j < 188; j++)
								{
									SrcImg[i][j]=	SrcImg[i][j]*255;

								}
								
				}
		}
void picture_x(uint8 SrcImg[][188],int k)
{
	
				int i, j;
				for (i = 0; i < 120; i++)
				{

								for (j = 0; j < 188; j++)
								{
									if(SrcImg[i][j]==k)
									SrcImg[i][j]=	SrcImg[i][j]*255;

								}
								
				}
		}	
void binarization(int k,uint8 image[][188])
{

  for (uint8 i = ((uint8)x1_0); i < ((uint8)x2_120); ++i)

        for (uint8 j = ((uint8)y1_0); j < ((uint8)y2_188); ++j)
       {
			
           if (image[i][j] >= k||image[i][j]==0 )
               image[i][j] = 255;//bai
          else image[i][j] = 0;//hei
       }


}
void binarization2(int k,uint8 image[][188])
{
    for (uint8 i = ((uint8)x1_0); i < ((uint8)x2_120); ++i)

        for (uint8 j = ((uint8)y1_0); j < ((uint8)y2_188); ++j)
       {
				
           if (image[i][j] >= k)
               image[i][j] = 255;//bai
          else image[i][j] = 0;//hei
       }


}


void binarization3(int k, int k2,int k3,unsigned char image[120][188])
{

    for (int i = 0; i <= 119; i++)
        for (int j = 0; j <= 187; j++)
        {

            if (image[i][j] == k || image[i][j] == k2 || image[i][j] == k3|| image[i][j] == 128)
                image[i][j] = 255;//bai
            else image[i][j] = 0;//hei
        }


}


void sobel(unsigned char imag[120][188], unsigned char charimag1[120][188])
{
    int tempx = 0, tempy = 0, temp = 0, i = 0, j = 0;
    for (i = 1; i < 120 - 1; i++)
    {
        for (j = 1; j < 188 - 1; j++)
        {

            tempx = (-imag[i - 1][j - 1])
                + (-2 * imag[i][j - 1])
                + (-imag[i + 1][j - 1])
                + (imag[i - 1][j + 1])
                + (2 * imag[i][j + 1])
                + (imag[i + 1][j + 1]);
            if (tempx < 0)
                tempx = -tempx;

            tempy = (imag[i + 1][j - 1])
                + (2 * imag[i + 1][j])
                + (imag[i + 1][j + 1])
                + (-imag[i - 1][j - 1])
                + (-2 * imag[i - 1][j])
                + (-imag[i - 1][j + 1]);
            if (tempy < 0)
                tempy = -tempy;
            temp = tempx + tempy;
						//temp = sqrt(tempx * tempx + tempy * tempy);
            if (temp > 255)
                temp = 255;
//             if(temp>254)//二值化
//							 temp=255;
						 else temp=0;
            charimag1[i][j] = temp;

        }
    }
}

void Reduction(uint8 image[][188],uint8 image2[][188],uint8 image3[][188])
{
int i,j,temp;
		for (i = 0; i < 120; i++)
		{
					for (j = 0; j < 188; j++)
					{
						temp=image[i][j]-image2[i][j];	
						if(temp<0)
							temp=-temp;
						image3[i][j]=temp;
					}
		}
	
}

void picutre_with(unsigned char image1[][188],unsigned char image2[][188])
{
int i,j,temp;
    for (i = 2; i < 119; i++)
	 {
			for (j = 1; j < 187; j++)
			{
				if(image2[i][j]==0)
				image1[i][j]=255;
				
				
			}
		}



}

void Canny(uint8 SrcImg[][188],uint8 CAnny[][188],int sobel_threshold)
{

	int Gx = 0, Gy = 0;
	int i, j;
	static int temp;

	for (i = 0; i < 120; i++)
	{
			if (i > 3 && i < 120 - 3)
			{
					for (j = 2; j < 188 - 2; j++)
					{
							Gy = SrcImg[i - 1][ j - 1] - SrcImg[i + 1][ j + 1] - (SrcImg[i + 1][ j]<<1) +  (SrcImg[i - 1][ j]<<1) - SrcImg[i + 1][ j + 1] + SrcImg[i - 1][j + 1];
							Gx = SrcImg[i - 1][j + 1] - SrcImg[i - 1][ j - 1] -  (SrcImg[i][ j - 1]<<1) +  (SrcImg[i][ j + 1]<<1) - SrcImg[i + 1][j - 1] + SrcImg[i + 1][ j + 1];
						 temp=(abs(Gx)+abs(Gy));					
							if (temp > sobel_threshold/*&&CannyImg[i][j]!=bai*/)
							{ 
								
							CAnny[i][j]=255;

							}
							else CAnny[i][j]=0;
							
					}
			}
	}
}

void yasuo(uint8 SrcImg[][188],uint8 wif[][125])
{
	for(int i=80;i>=0;i--)
	 for(int j=125;j>=0;j--)
	{
		
		wif[j][i]=SrcImg[40+j][63+i];
		
		
	}
	
}

void key_Init()
{
	//C9 A8 A15 C7 
//G15 G13 G11 G14 B3
//gpio_dir(C9,GPI,GPI_FLOATING_IN);

	gpio_init(C9,GPI,GPIO_HIGH,GPI_PULL_UP);  //拨码按键初始化
	gpio_init(A8,GPI,GPIO_HIGH,GPI_PULL_UP);
	gpio_init(A15,GPI,GPIO_HIGH,GPI_PULL_UP);
	gpio_init(G15,GPI,GPIO_HIGH,GPI_PULL_UP);
	gpio_init(G13,GPI,GPIO_HIGH,GPI_PULL_UP);
	gpio_init(G11,GPI,GPIO_HIGH,GPI_PULL_UP);
	gpio_init(G14,GPI,GPIO_HIGH,GPI_PULL_UP); //五相开关初始化
	gpio_init(B3,GPI,GPIO_HIGH,GPI_PULL_UP);	
	
	
}


int aver_x,aver_y;


void find_light(unsigned char img[120][188])
{
	int num = 0;
	int total_x = 0, total_y = 0;
	int high_Height = 160;         //定义图像的三个部分高度 便于分块求其灰度阈值
	int mid_Height = 120;
	int low_Height = 80;

	int i=0;
	int j=0;
	int Height=120;
	int Length=188;
 //  滤波处理 （预防数组越界）

   for (i = 0; i<Height; i++)
      {
          for (j = 1; j<Length-1; j++)
            {
                if(i == 0 )
                    img[i][j] = (img[i+1][j]+img[i][j+1]+img[i+1][j+1]+img[i][j-1]+img[i+1][j-1])/5;
                if(i == 119)
                    img[i][j] = (img[i][j+1]+img[i-1][j]+img[i][j-1]+img[i-1][j-1]+img[i-1][j+1])/5;
                if(i != 0 && i != 199)
                    img[i][j] = (img[i+1][j]+img[i][j+1]+img[i+1][j+1]+img[i-1][j]+img[i][j-1]+img[i-1][j-1]+img[i-1][j+1]+img[i+1][j-1])/8;
            }
          j = 0;
          if(i == 0)
            img[i][j] = (img[i+1][j]+img[i][j+1]+img[i+1][j+1])/3;
          if(i == 119)
            img[i][j] = (img[i-1][j]+img[i-1][j+1]+img[i][j+1])/3;
          if(i != 0 && i != 119)
            img[i][j] = (img[i-1][j]+img[i-1][j+1]+img[i][j+1]+img[i+1][j+1]+img[i+1][j])/5;
          j = 187;
          if(i == 0)
            img[i][j] = (img[i][j-1]+img[i+1][j-1]+img[i+1][j])/3;
          if(i == 119)
            img[i][j] = (img[i][j-1]+img[i-1][j-1]+img[i-1][j])/3;
          if(i != 0 && i != 119)
            img[i][j] = (img[i-1][j]+img[i-1][j-1]+img[i][j-1]+img[i+1][j-1]+img[i+1][j])/5;
      }

		}
