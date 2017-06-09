#include "LPC11XX.H"
#include "stdio.h"
#include "string.h"
#include "ADC.h"

//#define UART_BPS	9600
//char GcRcvBuf[20];
/*******************************************************************
*函数名称：延时函数   						  															 *
*函数描述:Delay()																	  							 *		
*参    数：void																										 *
*返回值：void																											 *
********************************************************************/
void Delay(uint32_t ulTime){
	uint32_t i;
	i=0;
	while(ulTime--){
		for(i=0;i<5000;i++);
	}
}
/*******************************************************************
*函数名称：ADC_Init()   					  															 *
*函数描述:AD初始化																  							 *		
*参    数：void																										 *
*返回值：void																											 *
********************************************************************/
void ADC_Init(void){
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
	LPC_IOCON->PIO1_11 &=~ 0xBF;
	LPC_IOCON->PIO1_11 |= 0x01;
	LPC_SYSCON->PDRUNCFG &=~ (0x01<<4);
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);
	LPC_ADC->CR=(0x01<<7)|														//选用通道AD1
							((SystemCoreClock/1000000-1)<<8)|			//时钟设置
							(0<<16)|															//软件控制模式
							(0<<17)|															//每次转换占用的时钟数，这里是000 - 11个
							(0<<24)|															//先不启动
							(0<<27);															//上升沿启动转换
}
/*******************************************************************
*函数名称：ADC_Read()					  															     * 
*函数描述:读取adc的值															  							 *		
*参    数：void																										 *
*返回值：uint32_t																									 *
********************************************************************/
uint32_t ADC_Read(void)
{
	uint32_t i;
	uint32_t ulADCData;
	uint32_t ulADCBuf;
	ulADCData = 0;
	
		for(i=0;i<10;i++)
	  {
			LPC_ADC->CR |= (1<<24);
			while((LPC_ADC->DR[7]&0x80000000)==0);				//DR32置1，转换完成
			LPC_ADC->CR |= (1<<24);
			while((LPC_ADC->DR[7]&0x80000000)==0);
			ulADCBuf = LPC_ADC->DR[7];
			ulADCBuf = (ulADCBuf>>6)&0x3ff;								//11个1
			ulADCData += ulADCBuf;
		}
		ulADCData = ulADCData/10;
		ulADCData = (ulADCData*3300)/1024;
		return ulADCData;
}
