#include "LPC11xx.h"
#include "uart.h"
#define UART_BPS  9600

void UART_Init(void)
{
	uint16_t usFdiv;
	LPC_SYSCON ->SYSAHBCLKCTRL |=(1<<16);
	LPC_IOCON ->PIO1_6 &=~0x07;
	LPC_IOCON ->PIO1_6 |=0x01;
	LPC_IOCON ->PIO1_7 &=~0x07;
	LPC_IOCON ->PIO1_7 |=0x01;
	
	LPC_SYSCON ->SYSAHBCLKCTRL |=(1<<12);
	LPC_SYSCON ->UARTCLKDIV =0x01;
	LPC_UART ->LCR =0x83;
	usFdiv = (SystemCoreClock /LPC_SYSCON ->UARTCLKDIV /16)/UART_BPS ;
	LPC_UART ->DLM =usFdiv /256;
	LPC_UART ->DLL =usFdiv %256;
	LPC_UART ->LCR =0x03;
	LPC_UART ->FCR =0x07;
}
//********************串口发送字节数据***************************//
void UART_SendByte(uint8_t ucDat)
{
	LPC_UART -> THR = ucDat;
	while((LPC_UART -> LSR & 0x40)==0);
}
//********************向串口发送字符数据*************************//
void UART_SendStr(char *pucStr)
{
	while(1)
	{
		if(*pucStr == '\0')
			break;
		UART_SendByte (*pucStr ++);	
	}
}
/************************************************/
/* 函数功能：串口发送数组数据                   */
/************************************************/
void UART_send(uint8_t *Buffer, uint32_t Length)
{
	while(Length != 0)
	{
		LPC_UART->THR = *Buffer;
		Buffer++;
		Length--;
		while ( !(LPC_UART->LSR & (1<<5)) );//等待发送完
	}
}
