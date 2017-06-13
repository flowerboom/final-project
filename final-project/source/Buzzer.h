#ifndef BUZZER_H
#define BUZZER_H

#include "lpc11xx.h"

void Buzzer_Init(void);
void Delay_inBuzzer(void);
void Judge_TempC(uint32_t temp);
void Judge_TempF(uint32_t temp);
#endif
