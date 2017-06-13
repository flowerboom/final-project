#include "LPC11xx.h"                    // Device header
#include "display.h"
#include "ADC.h"
#include "Uart.h"
#include "stick.h"
#include "Buzzer.h"
#include <stdio.h>

extern int flag;
extern char GcRcvBuf[20];


int main()
{
	uint32_t final_TemC, final_TemF;
	ADC_Init();
	UartInit();
	stick();
	Buzzer_Init();
	while(1)
	{
		final_TemC = temProcess();
		if(0 == flag)
		{
			display_C(final_TemC);
			Judge_TempC(final_TemC);
		}
		else if(1 == flag)
		{
			final_TemF = 32 + final_TemC * 1.8;
			display_F(final_TemF);
			Judge_TempF(final_TemF);
		}
		else if(2 == flag)
		{
			sprintf(GcRcvBuf, "Temp = %4d ¡æ\r \n", final_TemC);
			UART_SendStr(GcRcvBuf);
			Delay(1000);
			sprintf(GcRcvBuf, "Temp = %4d ¨H\r \n", final_TemF);
			UART_SendStr(GcRcvBuf);
			Delay(1000);
		}
	}
}
