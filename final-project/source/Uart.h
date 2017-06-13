#ifndef UART_H
#define UART_H

#include "LPC11xx.h"  
#include <stdio.h>

#define UART_BPS 115200


void UartInit(void);
void UART_SendByte(uint8_t ucDat);
void UART_SendStr(char * pucStr);
void UART_IRQHandler(void);

#endif
