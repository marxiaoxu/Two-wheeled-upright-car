#include "fuzzy.h"

#define RANK 7

float fuzzy_kp = 0.0;   //模糊算得的kp值
float fuzzy_kd = 0.0;   //模糊算得的kd值

/*
 *  @brief      舵机模糊控制
 *  @since      v1.0
 *  P
 *  D
*/
void KP_Fuzzy(int8 position , int16 position_error)
{
    int16 fe = 0,fec = 0;//输入到模糊里的偏差
    int16 pe = 0,pec = 0;//输入到模糊里的偏差变化量
    uint8 num=0;
    float eRule[7]={0,1500,2800,4100,5400,6700,8000};                    //偏差的分段点 0---- 94    0,8 ,15,25,30 ,35 ,38
    float ecRule[7]={0,500,1000,1500,2000,2500,3000};                //偏差变化量的分段点


    //偏差变化隶属度
    /*速度模糊调节*/

//    float Rule_kp[7]={-64,-66,-68,-70,-72,-74,-76};          //kp隶属函数中心值
//    float Rule_kd[7]={-64,-66,-68,-70,-72,-74,-76};               //kd隶属函数中心值

//		float Rule_kp[7]={121,123,125,127,129,131,132};          //kp隶属函数中心值
//    float Rule_kd[7]={113,115,117,119,121,123,125};                    //kd隶属函数中心值
		
		
		  float Rule_kp[7]={145,165,185,205,225,245,265};          //kp隶属函数中心值
      float Rule_kd[7]={14,16,18,20,22,24,26};    
		
		
		

    float eFuzzy[2]={0.0,0.0};                              //偏差隶属度
    float ecFuzzy[2]={0.0,0.0};                                //偏差变化隶属度
    float U1Fuzzy_kp[7]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    float U1Fuzzy_kd[7]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    uint8 rule_kp[7][7]=
    {//负大 负中 负小 零 正小  正中 正大
  //ec 0 1 2 3 4 5 6  //e
      {2,2,1,1,1,0,0},//0    3,2,2,1,1,1,0
      {3,3,2,1,1,1,0},//1    2,2,1,1,1,0,0
      {4,3,3,2,2,1,1},//2    2,2,1,1,1,0,0
      {4,4,3,3,2,1,1},//3    4,3,2,1,1,1,0
      {4,4,4,3,2,2,1},//4
      {5,5,5,4,4,3,2},//5
      {6,6,5,5,4,3,3} //6
    };

    uint8 rule_kd[7][7]=
    {
  //ec 0 1 2 3 4 5 6  //e
      {3,3,4,5,5,6,6},//0
      {3,3,4,4,5,5,5},//1
      {2,3,3,4,5,5,5},//2
      {1,2,2,3,3,4,5},//3
      {1,1,2,2,3,3,3},//4
      {0,1,1,1,2,2,3},//5
      {0,0,1,1,1,2,2} //6
    };


    /*-------------------------------------------*/
    /*----------------确定输入量-----------------*/
    /*-------------------------------------------*/

    fe = (abs(position));          //偏差和偏差的变化量均取绝对值做计算
    fec =(abs(position_error));
    fuzzy_kp = 0.0;
    fuzzy_kd = 0.0;
    /*-------------------------------------------*/
    /*---------------确定kp隶属度----------------*/
    /*-------------------------------------------*/
    if(fe < eRule[0])
    {
        eFuzzy[0] =1.0;
        pe= 0;
    }
    else if(fe < eRule[1])
    {
        eFuzzy[0] = (eRule[1]-fe)/(eRule[1]-eRule[0]);
        pe = 0;
    }
    else if(fe < eRule[2])
    {
        eFuzzy[0] = (eRule[2] -fe)/(eRule[2]-eRule[1]);
        pe =1;
    }
    else if(fe < eRule[3])
    {
        eFuzzy[0] = (eRule[3] -fe)/(eRule[3]-eRule[2]);
        pe =2;
    }
    else if(fe < eRule[4])
    {
        eFuzzy[0] = (eRule[4]-fe)/(eRule[4]-eRule[3]);
        pe=3;
    }
    else if(fe < eRule[5])
    {
        eFuzzy[0] = (eRule[5]-fe)/(eRule[5]-eRule[4]);
        pe=4;
    }
    else if(fe < eRule[6])
    {
        eFuzzy[0] = (eRule[6]-fe)/(eRule[6]-eRule[5]);
        pe=5;
    }
    else
    {
        eFuzzy[0] =1.0;
        pe=6;
    }//隶属度为1-%a
    eFuzzy[1] = 1.0 - eFuzzy[0];                    //eFuzzy[0]+eFuzzy[1]=1;


    /*-------------------------------------------*/
    /*---------------确定kd隶属度----------------*/
    /*-------------------------------------------*/
    if(fec <= ecRule[0])
    {
        ecFuzzy[0] =1.0;
        pec = 0;
    }
    else if(fec < ecRule[1])
    {
        ecFuzzy[0] = (ecRule[1] - fec)/(ecRule[1]-ecRule[0]);
        pec = 0 ;
    }
    else if(fec < ecRule[2])
    {
        ecFuzzy[0] = (ecRule[2] - fec)/(ecRule[2]-ecRule[1]);
        pec = 1;
    }
    else if(fec < ecRule[3])
    {
        ecFuzzy[0] = (ecRule[3] - fec)/(ecRule[3]-ecRule[2]);
        pec = 2 ;
    }
    else if(fec < ecRule[4])
    {
        ecFuzzy[0] = (ecRule[4] - fec)/(ecRule[4]-ecRule[3]);
        pec=3;
    }
    else if(fec < ecRule[5])
    {
        ecFuzzy[0] = (ecRule[5]-fec)/(ecRule[5]-ecRule[4]);
        pec=4;
    }
    else if(fec<ecRule[6])
    {
        ecFuzzy[0] = (ecRule[6]-fec)/(ecRule[6]-ecRule[5]);
        pec=5;
    }
    else
    {
        ecFuzzy[0] =1.0;
        pec=6;
    }
    ecFuzzy[1] = 1.0 - ecFuzzy[0];
    /*-------------------------------------------*/
    /*---------------查询kp规则表----------------*/
    /*-------------------------------------------*/
    if(pe<(RANK-1) && pec<(RANK-1))        // e和e'都没有达到边缘
    {   //上下左右四个规则表的周围值
        num = rule_kp[pec][pe];//0-6范围
        U1Fuzzy_kp[num] += eFuzzy[0]*ecFuzzy[0];//误差隶属百分比*变化率隶属相乘  a*b

        num = rule_kp[pec][pe+1];
        U1Fuzzy_kp[num] += eFuzzy[1]*ecFuzzy[0];//(1-a)*(b)

        num = rule_kp[pec+1][pe];
        U1Fuzzy_kp[num] += eFuzzy[0]*ecFuzzy[1];//a*(1-b)

        num = rule_kp[pec+1][pe+1];
        U1Fuzzy_kp[num] += eFuzzy[1]*ecFuzzy[1];//(1-a)*(1-b)
    }
    else if(pe==(RANK-1) && pec<(RANK-1))  // e达到边缘
    {
        num = rule_kp[pec][pe];
        U1Fuzzy_kp[num] += eFuzzy[0]*ecFuzzy[0];
        num = rule_kp[pec+1][pe];
        U1Fuzzy_kp[num] += eFuzzy[0]*ecFuzzy[1];
    }
    else if(pe<(RANK-1) && pec==(RANK-1))  // e'达到边缘
    {
        num = rule_kp[pec][pe];
        U1Fuzzy_kp[num] += eFuzzy[0]*ecFuzzy[0];
        num = rule_kp[pec][pe+1];
        U1Fuzzy_kp[num] += eFuzzy[1]*ecFuzzy[0];
    }
    else                       // e和e'同时达到边缘
    {
        num = rule_kp[pec][pe];
        U1Fuzzy_kp[num] += eFuzzy[0]*ecFuzzy[0];
    }



    /*-------------------------------------------*/
    /*---------------查询kd规则表----------------*/
    /*-------------------------------------------*/
    if(pe<(RANK-1) && pec<(RANK-1))        // e和e'都没有达到边缘
    {
        num = rule_kd[pec][pe];
        U1Fuzzy_kd[num] += eFuzzy[0]*ecFuzzy[0];

        num = rule_kd[pec][pe+1];
        U1Fuzzy_kd[num] += eFuzzy[1]*ecFuzzy[0];

        num = rule_kd[pec+1][pe];
        U1Fuzzy_kd[num] += eFuzzy[0]*ecFuzzy[1];

        num = rule_kd[pec+1][pe+1];
        U1Fuzzy_kd[num] += eFuzzy[1]*ecFuzzy[1];
    }
    else if(pe==(RANK-1) && pec<(RANK-1))  // e达到边缘9
    {
        num = rule_kd[pec][pe];
        U1Fuzzy_kd[num] += eFuzzy[0]*ecFuzzy[0];
        num = rule_kd[pec+1][pe];
        U1Fuzzy_kd[num] += eFuzzy[0]*ecFuzzy[1];
    }
    else if(pe<(RANK-1) && pec==(RANK-1))  // e'达到边缘
    {
        num = rule_kd[pec][pe];
        U1Fuzzy_kd[num] += eFuzzy[0]*ecFuzzy[0];
        num = rule_kd[pec][pe+1];
        U1Fuzzy_kd[num] += eFuzzy[1]*ecFuzzy[0];
    }
    else                       // e和e'同时达到边缘
    {
        num = rule_kd[pec][pe];
        U1Fuzzy_kd[num] += eFuzzy[0]*ecFuzzy[0];
    }


    /*-------------------------------------------*/
    /*-----------------解模糊--------------------*/
    /*-------------------------------------------*/
    for(int l=0;l<RANK;l++)
    {
        fuzzy_kp += U1Fuzzy_kp[l] * Rule_kp[l];
        fuzzy_kd += U1Fuzzy_kd[l] * Rule_kd[l];
    }
}

