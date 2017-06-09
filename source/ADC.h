#include "lpc11xx.h"
#ifndef _ADC_H_
#define _ADC_H_

extern void Delay(uint32_t ulTime);
extern void ADC_Init(void);	//ADC初始化
extern uint32_t ADC_Read(void);	//读取AD值
//extern void UART_Init(void);
//extern void UART_SendByte(uint8_t ucDat);
//extern void UART_SendStr(char *pucStr);

#endif