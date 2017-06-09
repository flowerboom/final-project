#include "lpc11xx.h"
#include "stdio.h"
#include "math.h"

#define ARGUNUM 18

/*******************************************************************
*�������ƣ�Rd2_temp     											                     *
*��������: �ѵ�ѹת��Ϊ�¶�      														  		 *		
*��    ����uint32_t																								 *
*����ֵ��int 																											 *
********************************************************************/

uint32_t Rd2_temp(int ulADCData)
{
	float Rege;               //�˴������ø�����
  float Re[ARGUNUM]={0.3952,0.5046,0.6510,0.8502,1.124,1.506,2.047,2.823,3.958,5.648,8.221,12.124,18.68,29.37,47.73,80.36,140.0,249.6};
	int Tem[ARGUNUM]={130,120,110,100,90,80,70,60,50,40,30,20,10,0,-10,-20,-30,-40};
	//int Tem[ARGUNUM]={-40,-30,-20,-10,0,10,20,30,40,50,60,70,80,90,100,110,120,130};
	float scale;
	float Temperature;
	uint8_t n;
	
	Rege = (ulADCData*10*1.0)/(3.3-(ulADCData/1000));      // ���裬���������ѹ����
	Rege = Rege/1000;																				//ת����λΪ Kŷķ
	if((Rege<0.3956)||(Rege>249.6))                       //�ж��Ƿ���������跶Χ֮��
		Temperature = 0;
	else
	{
		for(n=0;n<18;n++)
		{
			if((Rege>Re[n])&&(Rege<Re[n+1]))
			{
				scale = (Re[n+1]-Re[n])/10;                     //����ÿ���̶�����Ӧ����ֵ
				Temperature = Tem[n+1] - (Rege-Re[n])/scale;
			}
		}
	}

	return Temperature*100/10;                            //����һλС��
//	return int(Temperature);
}

