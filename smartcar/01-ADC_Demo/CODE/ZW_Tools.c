/*---------------------------------------------------------------------
                          ����ͼ�����ߺ���
													
��ƽ    ̨��RT1064
����    д�����Ļ�ϲ
����ϵ��ʽ��QQ��320388825 ΢�ţ�LHD0617_
�������¡�2021.11.30
������ƽ̨��MDK 5.28.0
����    �ܡ�����ͼ�����ߺ���
��ע�����������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
---------------------------------------------------------------------*/
/*����ͷ�ļ�*/
#include "ZW_Tools.h"

/************************************************************
												 ����ͼ��
								
���������ơ�ZW_Send_Image
����    �ܡ�ͼ���ͺ���
����    ����ZW_Image��ֵ��ͼ�����飨��0��1���Ķ�ֵ��ͼ��
���� �� ֵ����
��ʵ    ����ZW_Send_Image(mt9v03x_csi_image);
��ע�������ֻ�ܴ����ֵ��ͼ�񣨷�0��1��
						��.h�ļ��к궨��ߴ��������λ������д�ĳߴ��Ӧ�����޷�ʹ��
						�۸ú��������ͼ��������±���������λ������

************************************************************/

void ZW_Send_Image(ZW_uint8 ZW_Image[ZW_ImgSize_H][ZW_ImgSize_W])
{
	ZW_uint8 ZW_data = 0;
	ZW_uint8 ZW_i,ZW_j;
	for(ZW_i=0;ZW_i<ZW_ImgSize_H;ZW_i++)
	{
		for(ZW_j=0;ZW_j<ZW_ImgSize_W/8;ZW_j++)
		{
			ZW_data = 0;
			if(ZW_Image[ZW_i][ZW_j*8+0])	ZW_data |= 0x01<<7;
			if(ZW_Image[ZW_i][ZW_j*8+1])	ZW_data |= 0x01<<6;
			if(ZW_Image[ZW_i][ZW_j*8+2])	ZW_data |= 0x01<<5;
			if(ZW_Image[ZW_i][ZW_j*8+3])	ZW_data |= 0x01<<4;
			if(ZW_Image[ZW_i][ZW_j*8+4])	ZW_data |= 0x01<<3;
			if(ZW_Image[ZW_i][ZW_j*8+5])	ZW_data |= 0x01<<2;
			if(ZW_Image[ZW_i][ZW_j*8+6])	ZW_data |= 0x01<<1;
			if(ZW_Image[ZW_i][ZW_j*8+7])	ZW_data |= 0x01<<0;
			ZW_Putchar(ZW_data);
		}
		ZW_data = 0;
		for(ZW_j=0;ZW_j<ZW_ImgSize_W%8;ZW_j++)
		{
			if(ZW_Image[ZW_i][(ZW_ImgSize_W-ZW_ImgSize_W%8)+ZW_j])	ZW_data |= 0x01<<(7-ZW_j);
		}
		ZW_Putchar(ZW_data);
		ZW_data = 0;
	}
}

