#include "LPC11XX.H"
#include "stdio.h"
#include "string.h"
#include "ADC.h"

//#define UART_BPS	9600
//char GcRcvBuf[20];
/*******************************************************************
*�������ƣ���ʱ����   						  															 *
*��������:Delay()																	  							 *		
*��    ����void																										 *
*����ֵ��void																											 *
********************************************************************/
void Delay(uint32_t ulTime){
	uint32_t i;
	i=0;
	while(ulTime--){
		for(i=0;i<5000;i++);
	}
}
/*******************************************************************
*�������ƣ�ADC_Init()   					  															 *
*��������:AD��ʼ��																  							 *		
*��    ����void																										 *
*����ֵ��void																											 *
********************************************************************/
void ADC_Init(void){
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
	LPC_IOCON->PIO1_11 &=~ 0xBF;
	LPC_IOCON->PIO1_11 |= 0x01;
	LPC_SYSCON->PDRUNCFG &=~ (0x01<<4);
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);
	LPC_ADC->CR=(0x01<<7)|														//ѡ��ͨ��AD1
							((SystemCoreClock/1000000-1)<<8)|			//ʱ������
							(0<<16)|															//�������ģʽ
							(0<<17)|															//ÿ��ת��ռ�õ�ʱ������������000 - 11��
							(0<<24)|															//�Ȳ�����
							(0<<27);															//����������ת��
}
/*******************************************************************
*�������ƣ�ADC_Read()					  															     * 
*��������:��ȡadc��ֵ															  							 *		
*��    ����void																										 *
*����ֵ��uint32_t																									 *
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
			while((LPC_ADC->DR[7]&0x80000000)==0);				//DR32��1��ת�����
			LPC_ADC->CR |= (1<<24);
			while((LPC_ADC->DR[7]&0x80000000)==0);
			ulADCBuf = LPC_ADC->DR[7];
			ulADCBuf = (ulADCBuf>>6)&0x3ff;								//11��1
			ulADCData += ulADCBuf;
		}
		ulADCData = ulADCData/10;
		ulADCData = (ulADCData*3300)/1024;
		return ulADCData;
}
