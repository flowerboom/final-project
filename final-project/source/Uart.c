#include "Uart.h"
char GcRcvBuf[20];
int a = 1;
void UartInit(void)
{
	uint16_t usFdiv;
	LPC_SYSCON -> SYSAHBCLKCTRL |= (1 << 16);
	LPC_IOCON -> PIO1_6 &= ~0x07;																															//配置p1.6为RXD，RXD是接收数据的引脚
	LPC_IOCON -> PIO1_6 |= 0x01;																															//配置p1.7为TXD，TXD是发送数据的引脚
	LPC_IOCON -> PIO1_7 &= ~0x07;
	LPC_IOCON -> PIO1_7 |= 0x01;
	LPC_SYSCON -> SYSAHBCLKCTRL &= ~(1 << 16);
	LPC_SYSCON -> SYSAHBCLKCTRL |= (1 << 12);																									//打开UART功能部件时钟
	LPC_SYSCON -> UARTCLKDIV = 0x01;																													//UART时钟分频
	LPC_UART -> LCR = 0x83;																																		//允许设置波特率
	usFdiv = (SystemCoreClock / LPC_SYSCON -> UARTCLKDIV / 16) / UART_BPS;										//设置波特率
	LPC_UART -> DLM = usFdiv / 256;
	LPC_UART -> DLL = usFdiv % 256;
	LPC_UART -> LCR = 0x03;																																		//lock波特率
	LPC_UART -> FCR = 0x07;																																	
	/*
	NVIC_EnableIRQ(UART_IRQn);
	LPC_UART->IER = 0x01;
	*/
}


void UART_SendByte(uint8_t ucDat)																														//查询法发送数据																						
{
	LPC_UART -> THR = ucDat;																																	//写入数据
	while((LPC_UART -> LSR & 0x040) == 0);																										//等待发送
}


void UART_SendStr(char * pucStr)
{
	while(1)
	{
		if( *pucStr == '\0')
			break;
		UART_SendByte( *pucStr++);
	}
}

/*
void UART_IRQHandler(void)
{
//	int t;
	uint32_t IRQ_ID;
	
	IRQ_ID = LPC_UART->IIR;
	IRQ_ID = ((IRQ_ID>>1)&0x7);
	if(IRQ_ID == 0x02){					
		sprintf(GcRcvBuf,"V:=%4d mV\r\n",a);
		UART_SendStr(GcRcvBuf);
	}
	LPC_UART->FCR = 0x07;		
}
*/

