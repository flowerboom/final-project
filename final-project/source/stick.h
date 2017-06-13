#ifndef STICK_H
#define STICK_H

#include "LPC11xx.h"                    // Device header

void Delay(uint32_t ulTime);
void PIOINT3_IRQHandler(void);
void stick(void);

#endif
