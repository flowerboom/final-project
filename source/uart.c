#include "lpc11xx.h"
#include "stdio.h"
#include "string.h"
#include "uart.h"

#define UART_BPS 9600
volatile uint8_t GucRcvNew;
uint8_t GucRcvBuf[10];
uint32_t GulNum;
char GcRcvBuf[20];

/*******************************************************************
*�������ƣ�UART_Init()      											                 *
*��������: ���ڳ�ʼ��             														  	 *		
*��    ����void																										 *
*����ֵ��void																											 *
********************************************************************/
void UART_Init(void){
	uint16_t usFdiv;
	
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
	LPC_IOCON->PIO1_6 |= 0x01;
	LPC_IOCON->PIO1_7 |= 0x01;
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);
	LPC_SYSCON->UARTCLKDIV = 0x01;
	
	LPC_UART->LCR = 0x83;
	usFdiv = (SystemCoreClock/LPC_SYSCON->UARTCLKDIV/16)/UART_BPS;
	LPC_UART->DLM = usFdiv/256;
	LPC_UART->DLL = usFdiv%256;
	LPC_UART->LCR = 0x03;
	LPC_UART->FCR = 0x07;
	
	NVIC_EnableIRQ(UART_IRQn);
//	NVIC_SetPriority(UART_IRQn,1);
	LPC_UART->IER = 0x01;
}

/*******************************************************************
*�������ƣ�UART_SendByte()    											               *
*��������: ��ѯ����������        														  		 *		
*��    ����uint8_t			����������																 *
*����ֵ��void																											 *
********************************************************************/
void UART_SendByte(uint8_t ucDat){
	LPC_UART->THR = ucDat;
	while((LPC_UART->LSR&0x40)==0);
}

/*******************************************************************
*�������ƣ�UART_SendStr()  											                   *
*��������: �ַ�������            														  		 *		
*��    ����char																										 *
*����ֵ��void																											 *
********************************************************************/
void UART_SendStr(char *pucStr){
	while(1){
		if(*pucStr=='\0') 
			break;
		else
			UART_SendByte(*pucStr++);
	}
}

/*******************************************************************
*�������ƣ�UART_IRQHandler()      											           *
*��������: �����жϷ�����      														  		 *		
*��    ����void																										 *
*����ֵ��void																											 *
********************************************************************/
void UART_IRQHandler(void)
{
//	int t;
	uint32_t IRQ_ID;
	
	IRQ_ID = LPC_UART->IIR;
	IRQ_ID = ((IRQ_ID>>1)&0x7);
	if(IRQ_ID == 0x02){					
		sprintf(GcRcvBuf,"V:=%4d mV\r\n", ADC_Read());
		UART_SendStr(GcRcvBuf);
	}
	LPC_UART->FCR = 0x07;		
}
