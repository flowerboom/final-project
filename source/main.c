#include "lpc11xx.h"
#include "ADC.h"
#include "display.h"
#include "uart.h"
#include "algorithm.h"
#include "key.h"
#include <stdio.h>

static uint32_t Temprature;
int flag=0;
extern char GcRcvBuf[20];
//static float Temprature;
void Delay_ms(uint32_t ulTime){
	uint32_t i;
	i=0;
	while(ulTime--){
		for(i=0;i<5000;i++);
	}
}
/*******************************************************************
*�������ƣ�PIOINT3_IRQHandler()    											           *
*��������: �����жϷ�����      														  		 *		
*��    ����void																										 *
*����ֵ��void																											 *
********************************************************************/

void PIOINT3_IRQHandler()
{
	int i;
	if((LPC_GPIO3->MIS&(1<<1)) == (1<<1))   
	{
		Delay_ms(200);
		flag++;
		if(flag>2) flag=0;
		LPC_GPIO3->IC = 0xFFF;
	}
}

/*******************************************************************
*�������ƣ�main()                 											           *
*��������: ������               														  		 *		
*��    ����void																										 *
*����ֵ��int																											 *
********************************************************************/
int main()
{																			  	
	uint32_t t;
	uint32_t temprature;
	
	SHUMAGUAN_GPIOInit();
	ADC_Init();
	UART_Init();
	GPIOInit();									  		
	interupt();
while(1)
	{ 
		Temprature = Rd2_temp(ADC_Read());  	
		if(flag==0)
			//for(t=0;t<2000;t++)                   //�����¶ȸ���Ƶ�ʣ�Ч�����������˸��������Ҫ���ڵĲ���
				SHUMAGUAN_Display(Temprature/10);       //*10ԭ������Ҫ���λ�ƶ�һλ
		if(flag==1){
			temprature = 32+Temprature/10 * 1.8;			//�����¶Ȳ�������ͬһ������,��Ȼ���ж��¶�ʱ��һֱ����//		Temprature = Temprature*34;
			//for(t=0;t<700;t++) 		//���ĸ���Ƶ�ʣ�������Ҫ���ڵĲ���
				Fahrenheit_Display(temprature);
		}
		if(flag==2){
		sprintf(GcRcvBuf,"Temp=%4d C\r\n",Temprature);
		UART_SendStr(GcRcvBuf);
		Delay_ms(200);
	}
		//Judge_Temp(Temprature/10);            //����10��ԭ������ת��������*100/10  ���Ի���Ҫ/10	
	}
}
