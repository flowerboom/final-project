#include "lpc11xx.h"

#ifndef _SHUMAGUAN_H_
#define _SHUMAGUAN_H_

extern void delay(void);
extern void SHUMAGUAN_GPIOInit(void);
extern void SHUMAGUAN_Display(uint32_t value);
extern void Fahrenheit_Display(uint32_t value);

#endif
