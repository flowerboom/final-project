#ifndef __UART_H
#define __UART_H	
#include "LPC11xx.h"

extern void UART_Init(void);
extern void UART_SendByte(uint8_t ucDat);
extern void UART_SendStr(char *pucStr);
extern void UART_send(uint8_t *Buffer, uint32_t Length);

#endif
