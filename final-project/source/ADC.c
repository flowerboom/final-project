#include "ADC.h"


void ADC_Init(void)
{
	LPC_SYSCON -> SYSAHBCLKCTRL |= (1 << 16);
	LPC_IOCON -> PIO1_11 &= ~0xBF;																														//����ģ������
	LPC_IOCON -> PIO1_11 |= 0x01;																															//ģ��ͨ������0
	LPC_SYSCON -> PDRUNCFG &= ~(0x01 << 4);
	LPC_SYSCON -> SYSAHBCLKCTRL |= (1 << 13);																									//ʹ��ADCģ��
	LPC_ADC->CR = (0x01 << 7)|																																//ѡ��ͨ��ADC7
							((SystemCoreClock / 1000000 - 1) << 8)|																				//ʱ�����ã�ת��ʱ��1MHZ
							(0 << 16)|																																		//�������ת������ģʽ
							(0 << 17)|																																		//ÿ��ת��ռ�õ�ʱ������������11����ʹ��11 clocksת��
							(0 << 24)|																																		//�Ȳ���������ADCת��ֹͣ
							(0 << 27);																																		//����������ת������ֱ������ADCת������λ��Ч
}


uint32_t temProcess(void)																																		//�����¶Ⱥ���
{
			
		//�㷨�������
		float R;   					 	          																												//��������R
		float Re[18]={0.3952,0.5046,0.6510,0.8502,1.124,1.506,2.047,2.823,3.958,5.648,8.221,12.124,18.68,29.37,47.73,80.36,140.0,249.6};
		int temperature[18]={130,120,110,100,90,80,70,60,50,40,30,20,10,0,-10,-20,-30,-40};
		float unit;
		float Temperature;
		uint8_t n;
		
		//�ɼ������������
		uint32_t i;
		uint32_t ulADCData;
		uint32_t ulADCBuf;
		ulADCData = 0;


		for(i = 0; i < 10; i++)
	  {
			LPC_ADC -> CR |= (1 << 24);																														//����ת��
			while((LPC_ADC -> DR[7] & 0x80000000) == 0);																					//��ȡDR��7λ��ת����ɣ�
			LPC_ADC -> CR |= (1 << 24);
			while((LPC_ADC -> DR[7] & 0x80000000) == 0);																					//������ǰ�ĵ�һ��
			ulADCBuf = LPC_ADC -> DR[7];																													//��ȡ����Ĵ���
			ulADCBuf = (ulADCBuf >> 6) & 0x3ff;																										//11��1�����ݴӵ���λ��ʼ�洢��ռ��ʮλ
			ulADCData += ulADCBuf;
		}
		ulADCData = ulADCData / 10;
		ulADCData = (ulADCData * 3300) / 1024;																									//������ת����ģ����
		
		
		//�ɴ˿�ʼ���вɼ����ݵ��㷨���������㷨����¶�		

		//R = (ulADCData/1000)/ ((3.3 - (ulADCData / 1000)) / 10000);      											//������Ȼ��򣬾ͻ��С������λ��ɾ�������Է�ĸ��������					
		
		R = (ulADCData*10*1.0)/(3.3-(ulADCData/ 1000));																					//��������ĵ�����⹫ʽ����λŷķ
		
		R = R / 1000;																																						//ת��Ϊǧŷķ
		if((R < 0.3952) || (R >249.6))                     																			//�ж��Ƿ���������跶Χ֮�ڣ����������ֹ��������Ϊ0
		Temperature = 0;
		else
		{
			for(n = 0; n < 18; n++)
			{
				if((R > Re[n]) && (R < Re[n + 1]))
				{
					unit = (Re[n + 1] - Re[n]) / 10;                   																//���㵥λ�̶��¶�����Ӧ�ĵ�����ֵ
					Temperature = temperature[n+1] - (R - Re[n]) / unit;															//��Tn����������ٵ��¶ȿ̶ȣ�����Ӧ������ȷ�¶�ֵ
				}
			}
		}
		return Temperature;                          
}

