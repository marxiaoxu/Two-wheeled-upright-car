#include "pengzhang.h"
void pengzhang(unsigned char *Image)
{
	
	int j,i;
	for(int i=188-2;i>=1;i--)
	for(int j=120-2;j>=1;j--)
	{
		
		
		if(Image[i * 120 + j]!=255)
		{
			
		if(Image[i * 120 + j+1]==255||Image[i * 120 + j-1]==255||Image[(i+1) * 120 + j]==255||Image[(i-1) * 120 + j]==255)
		Image[i * 120 + j]=255;
		}
		
	}
	
	


}

uint8 conv_bin_special(const uint8 img[120][188], uint8 out[120][188])
{
    for (uint8 i = ((uint8)x1_0); i < ((uint8)x2_120); ++i)

        for (uint8 j = ((uint8)y1_0); j < ((uint8)y2_188); ++j)
            out[i][j] = 0XC0;     //c0=192
	
    for (uint8 i = ((uint8)x1_0); i < ((uint8)x2_120); ++i)
        out[i][0] &= 0XBF, out[i][187] &= 0XBF;

        for (uint8 j = ((uint8)y1_0); j < ((uint8)y2_188); ++j)
        out[0][j] &= 0XBF, out[119][j] &= 0XBF;

	
	

    for (uint8 i = ((uint8)x1_0); i < ((uint8)x2_120); ++i)

        for (uint8 j = ((uint8)y1_0); j < ((uint8)y2_188); ++j)
        {
            if (img[i][j] <= 50)//30
                out[i][j] &= 0X7F;  //7f=127          //=64
            //xÖá±ßÔµ¼ì²â
            int32 cx = img[i - 1][j - 1] - img[i - 1][j + 1]
                + (img[i][j - 1] << 1) - (img[i][j + 1] << 1)
                + img[i + 1][j - 1] - img[i + 1][j + 1];
            //yÖá±ßÔµ¼ì²â
            int32 cy = img[i - 1][j - 1] + (img[i - 1][j] << 1) + img[i - 1][j + 1]
                - img[i + 1][j - 1] - (img[i + 1][j] << 1) - img[i + 1][j + 1];
            //Ö÷¶Ô½ÇÏß±ßÔµ¼ì²â
            int32 cz = (img[i - 1][j - 1] << 1) + img[i - 1][j]
                + img[i][j - 1] - img[i][j + 1]
                - img[i + 1][j] - (img[i + 1][j + 1] << 1);
            //¸±¶Ô½ÇÏß±ßÔµ¼ì²â
            int32 cf = img[i - 1][j] + (img[i - 1][j + 1] << 1)
                - img[i][j - 1] + img[i][j + 1]
                - (img[i + 1][j - 1] << 1) - img[i + 1][j];   //64&b0XBF=0

           //if (abs(cx) >= 25)out[i][j + (cx > 0 ? 1 : -1)] &= 0XBF;//=128     63
           //if (abs(cy) >= 25)out[i + (cy > 0 ? 1 : -1)][j] &= 0XBF;//bf=191
           //if (abs(cz) >= 15)out[i + (cz > 0 ? 1 : -1)][j + (cz > 0 ? 1 : -1)] &= 0XBF;
           //if (abs(cf) >= 15)out[i + (cf > 0 ? 1 : -1)][j + (cf > 0 ? -1 : 1)] &= 0XBF;
           //if ((cx * cx + cy * cy) > (85 * 85 + 55 * 55))out[i][j] |= 0X20;//=224  127

           if (abs(cx) >= 65)out[i][j + (cx > 0 ? 1 : -1)] &= 0XBF;//=128     63
           if (abs(cy) >= 75)out[i + (cy > 0 ? 1 : -1)][j] &= 0XBF;//bf=191
           if (abs(cz) >= 55)out[i + (cz > 0 ? 1 : -1)][j + (cz > 0 ? 1 : -1)] &= 0XBF;
           if (abs(cf) >= 55)out[i + (cf > 0 ? 1 : -1)][j + (cf > 0 ? -1 : 1)] &= 0XBF;  //    20=32                                                                                                          
           if ((cx * cx + cy * cy) > (80 * 80 + 85 * 85))out[i][j] |= 0X20;//=224  127    //20=32


          //if (abs(cx) >= 55)out[i][j + (cx > 0 ? 1 : -1)] &= 0XBF;//=128     63
          //if (abs(cy) >= 65)out[i + (cy > 0 ? 1 : -1)][j] &= 0XBF;//bf=191
          //if (abs(cz) >= 45)out[i + (cz > 0 ? 1 : -1)][j + (cz > 0 ? 1 : -1)] &= 0XBF;
          //if (abs(cf) >= 45)out[i + (cf > 0 ? 1 : -1)][j + (cf > 0 ? -1 : 1)] &= 0XBF;  //    20=32                                                                                                          
          //if ((cx * cx + cy * cy) > (55 * 55 + 65 * 65))out[i][j] |= 0X20;//=224  12



        }
    return 1;
}

void pengzhang2(unsigned char Image[][188])
{
	static int fuck_x,fuck_y1,fuck_y2;

    	 

	for (uint8 i = ((uint8)0); i <= ((uint8)119); ++i)
        Image[i][0] = 0,  Image[i][1] = 0, Image[i][187] = 0,Image[i][186] = 0;
	
	

    for (uint8 j = ((uint8)0); j <= ((uint8)187); ++j)
          Image[0][j] = 0,Image[1][j] = 0, Image[119][j] = 0,Image[118][j] = 0;
	
	
	//****************************************************//
	
	
	
	       for (uint8 i = ((uint8)0); i < ((uint8)fuck); ++i)  //È¥³ýÉÏ²ãÎÞÐ§ÇøÓò

        for (uint8 j = ((uint8)0); j < ((uint8)188); ++j)
	
	Image[i][j]=200;
	
	
	
	
//		       for (uint8 i = ((uint8)100); i < ((uint8)120); ++i)

//        for (uint8 j = ((uint8)148); j < ((uint8)188); ++j)
//	
//	Image[i][j]=200;


//		       for (uint8 i = ((uint8)90); i < ((uint8)120); ++i)

//        for (uint8 j = ((uint8)0); j < ((uint8)188); ++j)
//	
//	Image[i][j]=200;




//**********************************************************//  ¶¯Ì¬È¥³ýÉÏ²ãÎÞÐ§ÇøÓò

//	fuck_x=50;
//	fuck_y1=0;
//	fuck_y2=188;
//	
//	
//if(fuck_x>x1_0)
//	fuck_x=x1_0;


//if(fuck_y1>y1_0)
//	fuck_y1=y1_0;

//if(fuck_y2<y2_188)
//	fuck_y1=y2_188;

//if(miss>=1)  //×Ô¶¯ÊÊÓ¦
//	{

//	fuck_x=50;
//	fuck_y1=188;
//	fuck_y2=188;

//}
//		       for (uint8 i = ((uint8)0); i < ((uint8)fuck_x); ++i)

//        for (uint8 j = ((uint8)0); j < ((uint8)fuck_y1); ++j)
//	
//	Image[i][j]=200;


//		       for (uint8 i = ((uint8)0); i < ((uint8)fuck_x); ++i)

//        for (uint8 j = ((uint8)fuck_y2); j < ((uint8)188); ++j)
//	
//	Image[i][j]=200;







	//****************************************//  

//		       for (uint8 i = ((uint8)100); i < ((uint8)120); ++i)  //µ×ÏÂ

//        for (uint8 j = ((uint8)0); j < ((uint8)188); ++j)
//	
//	Image[i][j]=200;
	//****************************************//  É¨Ãè·¶Î§×Ô¶¯ÊÊÓ¦
	//
	
	
       for (uint8 i = ((uint8)0); i < ((uint8)120); ++i)

        for (uint8 j = ((uint8)0); j < ((uint8)y1_0); ++j)
	
	Image[i][j]=200;
	
	     for (uint8 i = ((uint8)0); i < ((uint8)120); ++i)

        for (uint8 j = ((uint8)y2_188)-1; j < ((uint8)188); ++j)
	
	Image[i][j]=200;
	
	
	
	      for (uint8 i = ((uint8)0); i < ((uint8)x1_0); ++i)
       for (uint8 j = ((uint8)y1_0); j < ((uint8)y2_188); ++j)  

	
	Image[i][j]=200;
	
	     for (uint8 i = ((uint8)x2_120)-1; i < ((uint8)120); ++i)
      for (uint8 j = ((uint8)y1_0); j < ((uint8)y2_188); ++j) 
	
	Image[i][j]=200;
	
	
	
	
	
	


}

 uint8 conv_bin_special2(const uint8 img[120][188],uint8 out[120][188])
{
    for(uint8 i=(0);i<=(119);++i)
        for(uint8 j=(0);j<=(187);++j)
            out[i][j]=0XC0;
	
    for(uint8 i=(0);i<=(119);++i)
	{out[i][0]&=0XBF;out[i][187]&=0XBF;
	}
	
    for(uint8 j=(0);j<=(187);++j)
	{out[0][j]&=0XBF;out[119][j]&=0XBF;
	
	
	}

	
	
	
	
    for(uint8 i=(0);i<=(119);++i)
        for(uint8 j=(0);j<=(187);++j)
        {
            if(img[i][j]<=15)
                out[i][j]&=0X7F;
            //xÖá±ßÔµ¼ì²â
            int32 cx= img[i-1][j-1]    - img[i-1][j+1]
                    +(img[i  ][j-1]<<1)-(img[i  ][j+1]<<1)
                    + img[i+1][j-1]    - img[i+1][j+1];
            //yÖá±ßÔµ¼ì²â
            int32 cy=img[i-1][j-1]+(img[i-1][j]<<1)+img[i-1][j+1]
                    -img[i+1][j-1]-(img[i+1][j]<<1)-img[i+1][j+1];
            //Ö÷¶Ô½ÇÏß±ßÔµ¼ì²â
            int32 cz=(img[i-1][j-1]<<1)+img[i-1][j]
                    + img[i  ][j-1]                - img[i  ][j+1]
                                       -img[i+1][j]-(img[i+1][j+1]<<1);
            //¸±¶Ô½ÇÏß±ßÔµ¼ì²â
            int32 cf=                   img[i-1][j]+(img[i-1][j+1]<<1)
                    - img[i  ][j-1]                + img[i  ][j+1]
                    -(img[i+1][j-1]<<1)-img[i+1][j];
//            if(abs(cx)>=50)out[i][j+(cx>0?1:-1)]&=0XBF;
//            if(abs(cy)>=60)out[i+(cy>0?1:-1)][j]&=0XBF;
//            if(abs(cz)>=35)out[i+(cz>0?1:-1)][j+(cz>0?1:-1)]&=0XBF;
//            if(abs(cf)>=35)out[i+(cf>0?1:-1)][j+(cf>0?-1:1)]&=0XBF;
//							if((cx*cx+cy*cy)>(35*35+45*45))out[i][j]|=0Xbf;
//							
            if(abs(cx)>=15)out[i][j+(cx>0?1:-1)]&=0XBF;
            if(abs(cy)>=20)out[i+(cy>0?1:-1)][j]&=0XBF;
            if(abs(cz)>=10)out[i+(cz>0?1:-1)][j+(cz>0?1:-1)]&=0XBF;
            if(abs(cf)>=10)out[i+(cf>0?1:-1)][j+(cf>0?-1:1)]&=0XBF;
						
				if((cx*cx+cy*cy)>(35*35+45*45))out[i][j]|=0X00;
					

    }
    return 1;
}
//********************************liantongy//
 uint8 conv_bin_special3(const uint8 img[120][188],uint8 out[120][188])
{
    for(uint8 i=((uint8)0);i<=((uint8)119);++i)
	
        for(uint8 j=((uint8)0);j<=((uint8)187);++j)
            out[i][j]=0XC0;     //c0=192
    for(uint8 i=((uint8)0);i<=((uint8)119);++i)	
	out[i][0]&=0XBF,out[i][187]&=0XBF;//bf=191
	
    for(uint8 j=((uint8)0);j<=((uint8)187);++j)
	out[0][j]&=0XBF,out[187][j]&=0XBF;
	
	
    for(uint8 i=((uint8)0);i<=((uint8)119);++i)
        for(uint8 j=((uint8)0);j<=((uint8)187);++j)
        {
            if(img[i][j]<=15)
                out[i][j]&=0X7F;  //7f=127          //=64
						//          
						//  0XC0&0X7F=64
						//  7f=127  
						//  c0=192
						
            //xÖá±ßÔµ¼ì²â
            int32 cx= img[i-1][j-1]    - img[i-1][j+1]
                    +(img[i  ][j-1]<<1)-(img[i  ][j+1]<<1)
                    + img[i+1][j-1]    - img[i+1][j+1];
            //yÖá±ßÔµ¼ì²â
            int32 cy=img[i-1][j-1]+(img[i-1][j]<<1)+img[i-1][j+1]
                    -img[i+1][j-1]-(img[i+1][j]<<1)-img[i+1][j+1];
            //Ö÷¶Ô½ÇÏß±ßÔµ¼ì²â
            int32 cz=(img[i-1][j-1]<<1)+img[i-1][j]
                    + img[i  ][j-1]                - img[i  ][j+1]
                                       -img[i+1][j]-(img[i+1][j+1]<<1);
            //¸±¶Ô½ÇÏß±ßÔµ¼ì²â
            int32 cf=                   img[i-1][j]+(img[i-1][j+1]<<1)
                    - img[i  ][j-1]                + img[i  ][j+1]
                    -(img[i+1][j-1]<<1)-img[i+1][j];
						
//						
//							if (abs(cx) >= 35)out[i][j + (cx > 0 ? 1 : -1)] &= 0XBF;//=128     63
//							if (abs(cy) >= 35)out[i + (cy > 0 ? 1 : -1)][j] &= 0XBF;//bf=191
//							if (abs(cz) >= 25)out[i + (cz > 0 ? 1 : -1)][j + (cz > 0 ? 1 : -1)] &= 0XBF;
//							if (abs(cf) >= 25)out[i + (cf > 0 ? 1 : -1)][j + (cf > 0 ? -1 : 1)] &= 0XBF;
//							if ((cx * cx + cy * cy) > (135 * 135 + 135 * 135))out[i][j] |= 0X20;//=224  127
//						
//						
						
						
           if(abs(cx)>=50)out[i][j+(cx>0?1:-1)]&=0XBF;//=128     63
           if(abs(cy)>=60)out[i+(cy>0?1:-1)][j]&=0XBF;//bf=191
				if(abs(cz)>=35)out[i+(cz>0?1:-1)][j+(cz>0?1:-1)]&=0XBF;
           if(abs(cf)>=35)out[i+(cf>0?1:-1)][j+(cf>0?-1:1)]&=0XBF;
						
						
						//  0XC0&0X7F=64     64&0XBF=0
						//  7f=127           127&0XBF=63
						//  c0=192					 192&0XBF=128
						//									 0XBF=191
						//									 64
						//									 127
						//									 192
						
						
						
           if((cx*cx+cy*cy)>(65*65+75*75))out[i][j]|=0X20;//=224  127
						
						//  0XC0&0X7F=64     64&0XBF=0          0|0X20=  32
						//  7f=127           127&0XBF=63        63 |0X20=  63
						//  c0=192					 192&0XBF=128       128|0X20=  160
						//									 0XBF=191           191|0X20=  191
						//									 64                 64|0X20=   96
						//									 127                127|0X20=  127
						//									 192			          192|0X20=  224

						
						//  0XC0&0X7F=64     64&0XBF=0           0
						//  7f=127           127&0XBF=63         63
						//  c0=192					 192&0XBF=128        128
						//									 0XBF=191            191
						//									 64                  64
						//									 127                 127
						//									 192		             192
						
//				 if (abs(cx) >= 55)out[i][j + (cx > 0 ? 1 : -1)] &= 0XBF;//=128     63
//           if (abs(cy) >= 65)out[i + (cy > 0 ? 1 : -1)][j] &= 0XBF;//bf=191
//           if (abs(cz) >= 45)out[i + (cz > 0 ? 1 : -1)][j + (cz > 0 ? 1 : -1)] &= 0XBF;
//           if (abs(cf) >= 45)out[i + (cf > 0 ? 1 : -1)][j + (cf > 0 ? -1 : 1)] &= 0XBF;  //    20=32                                                                                                          
//          if ((cx * cx + cy * cy) > (65 * 65 + 75 * 75))out[i][j] |= 0X20;//=224  127    //20=32		
//						
//						
						
																													//20=32
    }
    return 1;
}



