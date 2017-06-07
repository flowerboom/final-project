#include "LPC11xx.h"
#include "uart.h"
#include "delay.h"
#include "ADC.h"
#include "KEY.h"
#include <stdio.h>
#include <string.h>

int main()
{ 
	key_init();
	UART_Init ();
	ADC_Init ();

	while(1)
	{    
	}

	}
