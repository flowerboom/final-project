#include "lpc11xx.h"
#include "ADC.h"
#include "display.h"

/*******************************************************************
*函数名称：GPIOInit()      											                   *
*函数描述: 控制终端的按键GPIO初始化  												  		 *		
*参    数：void																										 *
*返回值：void																											 *
********************************************************************/
void GPIOInit(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);	
	LPC_IOCON->PIO3_0 &=~ 0x07;    
	LPC_IOCON->PIO3_0 = 0x00; 			
	LPC_SYSCON->SYSAHBCLKCTRL &=~ (1<<16);
	LPC_GPIO3->DIR &=~ (1<<1);
	LPC_GPIO3->DATA |= (1<<1);
}

/*******************************************************************
*函数名称：interupt()      											                   *
*函数描述: 按键中断初始化设置    														  		 *		
*参    数：void																										 *
*返回值：void																											 *
********************************************************************/
void interupt(void)
{
	LPC_GPIO3->IE |= (1<<1); 
	LPC_GPIO3->IS |= (1<<1);
	LPC_GPIO3->IEV &=~ (1<<1);
	NVIC_EnableIRQ(EINT3_IRQn);
}
