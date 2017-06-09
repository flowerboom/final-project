#include "lpc11xx.h"

uint32_t table1[10]={0xec0,0xef9,0xea4,0xeb0,0xe99,0xe92,0xe82,0xef8,0xe80,0xe90};	
uint32_t table2[10]={0xdc0,0xdf9,0xda4,0xdb0,0xd99,0xd92,0xd82,0xdf8,0xd80,0xd90};	
uint32_t table3[10]={0xbc0,0xbf9,0xba4,0xbb0,0xb99,0xb92,0xb82,0xbf8,0xb80,0xb90};	
uint32_t table4[10]={0x7c0,0x7f9,0x7a4,0x7b0,0x799,0x792,0x782,0x7f8,0x780,0x790};
//delay

/*******************************************************************
*�������ƣ�Delay1()       											                   *
*��������: ��ʱ����             														  		 *		
*��    ����uint32_t																								 *
*����ֵ��void																											 *
********************************************************************/
void delay(uint32_t i)
{
//	uint32_t i=4000;
	while(i--);
}

/*******************************************************************
*�������ƣ�SHUMAGUAN_GPIOInit()   									                   *
*��������: ����ܳ�ʼ��          														  		 *		
*��    ����void																										 *
*����ֵ��void																											 *
********************************************************************/
//GPIOinit
void SHUMAGUAN_GPIOInit(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);
	LPC_SYSCON->SYSAHBCLKCTRL &=~ (1<<16);
	LPC_GPIO2->DIR |= 0xFFF;		
}

/*******************************************************************
*�������ƣ�SHUMAGUAN_Display()  										                   *
*��������: ���϶���ʾ����        														  		 *		
*��    ����uint32_t 																							 *
*����ֵ��void																											 *
********************************************************************/
//Dispaly
//void SHUMAGUAN_Display(uint32_t value)
void SHUMAGUAN_Display(uint32_t value)              //���϶�
{
	//value = value * 10;
	LPC_GPIO2->DATA	= table1[value/1000];	
	delay(40);

	LPC_GPIO2->DATA = 0xFFF;
	
	
	LPC_GPIO2->DATA	= table2[value%1000/100];	
	delay(40);

	LPC_GPIO2->DATA = 0xFFF;
	
	
	LPC_GPIO2->DATA = table3[value%1000%100/10];	
	delay(40);
	
	LPC_GPIO2->DATA = 0xFFF;
	
	
	LPC_GPIO2->DATA = table4[value%1000%1000%10];	
	delay(40);
	
	LPC_GPIO2->DATA = 0xFFF;
}

/*******************************************************************
*�������ƣ�Fahrenheit_Display()      						                   *
*��������: ���϶���ʾ����        														  		 *		
*��    ����uint32_t 																							 *
*����ֵ��void																											 *
********************************************************************/
void Fahrenheit_Display(uint32_t value)              //���϶�
{
	LPC_GPIO2->DATA	= table1[value/1000];	
	delay(40);

	LPC_GPIO2->DATA = 0xFFF;
	
	
	LPC_GPIO2->DATA	= table2[value%1000/100];	
	delay(40);

	LPC_GPIO2->DATA = 0xFFF;
	
	
	LPC_GPIO2->DATA = table3[value%1000%100/10];	
	delay(40);
	
	LPC_GPIO2->DATA = 0xFFF;
	
	
	LPC_GPIO2->DATA = table4[value%1000%1000%10];	
	delay(40);
	
	LPC_GPIO2->DATA = 0xFFF;
}
