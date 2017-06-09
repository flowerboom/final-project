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
*函数名称：PIOINT3_IRQHandler()    											           *
*函数描述: 按键中断服务函数      														  		 *		
*参    数：void																										 *
*返回值：void																											 *
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
*函数名称：main()                 											           *
*函数描述: 主函数               														  		 *		
*参    数：void																										 *
*返回值：int																											 *
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
			//for(t=0;t<2000;t++)                   //更改温度更新频率，效果是数码管闪烁，经常需要调节的参数
				SHUMAGUAN_Display(Temprature/10);       //*10原因是需要向高位移动一位
		if(flag==1){
			temprature = 32+Temprature/10 * 1.8;			//这里温度不可以用同一个变量,不然在判断温度时会一直报警//		Temprature = Temprature*34;
			//for(t=0;t<700;t++) 		//更改更新频率，经常需要调节的参数
				Fahrenheit_Display(temprature);
		}
		if(flag==2){
		sprintf(GcRcvBuf,"Temp=%4d C\r\n",Temprature);
		UART_SendStr(GcRcvBuf);
		Delay_ms(200);
	}
		//Judge_Temp(Temprature/10);            //除以10的原因是在转换函数里*100/10  所以还需要/10	
	}
}
