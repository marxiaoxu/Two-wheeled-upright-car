#include "filter.h"
void Bin_Image_Filter(uint8 Bin_Image[120][188])
{


    for (int nc = y1_0+1; nc < y2_188-1; nc++)
    {
        for (int nr = x1_0+1; nr < x2_120-1; nr++)
        {

            if ((Bin_Image[nr][nc] == 0)
                && (Bin_Image[nr - 1][nc] + Bin_Image[nr + 1][nc] + Bin_Image[nr][nc + 1] + Bin_Image[nr][nc - 1] +

                    Bin_Image[nr - 1][nc + 1] + Bin_Image[nr + 1][nc - 1] + Bin_Image[nr + 1][nc + 1] + Bin_Image[nr - 1][nc - 1]
                    >= 5 * 255))
            {
                Bin_Image[nr][nc] = 255;
            }
        }
    }

}

void Bin_Image_Filter2(uint8 Bin_Image[120][188],uint8 Bin_Image2[120][188])
{


    for (int nc = y1_0+1; nc < y2_188-1; nc++)
    {
        for (int nr = x1_0+1; nr < x2_120-1; nr++)
        {

            if ((Bin_Image[nr][nc] ==255)
                && (Bin_Image2[nr - 1][nc] + Bin_Image2[nr + 1][nc] + Bin_Image2[nr][nc + 1] + Bin_Image2[nr][nc - 1] +

                    Bin_Image2[nr - 1][nc + 1] + Bin_Image2[nr + 1][nc - 1] + Bin_Image2[nr + 1][nc + 1] + Bin_Image2[nr - 1][nc - 1]
                    <= 1 * 255))
            {
                Bin_Image2[nr][nc] = 0;
            }
        }
    }

}
 void fuck_zaodian(const uint8 img[120][188],uint8 out[120][188])
{
  for (uint8 i = ((uint8)x1_0+1); i < ((uint8)x2_120-1); ++i)

        for (uint8 j = ((uint8)y1_0+1); j < ((uint8)y2_188-1); ++j)
        {
            uint8 cnt=0;
            if(img[i][j]>=100)
            {
                cnt+=abs(img[i][j]-img[i-1][j-1])>10;
                cnt+=abs(img[i][j]-img[i-1][j+1])>10;
                cnt+=abs(img[i][j]-img[i+1][j-1])>10;
                cnt+=abs(img[i][j]-img[i+1][j+1])>10;
            }        	out[i][j]=(cnt>=4?((img[i-1][j-1]+img[i-1][j]+img[i-1][j+1]+img[i][j-1]+img[i][j]+img[i][j+1]+img[i+1][j-1]+img[i+1][j]+img[i+1][j+1])/9):img[i][j]);
        }
}


