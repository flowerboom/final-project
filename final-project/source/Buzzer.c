#include "Buzzer.h"
#include "display.h"

void Buzzer_Init()
{
	LPC_SYSCON -> SYSAHBCLKCTRL |= (1 << 16);																					
	LPC_IOCON -> PIO0_1 = 0x00;																//把p0.1引脚设置为GPIO时钟
	LPC_SYSCON -> SYSAHBCLKCTRL &= ~(1 << 16);								//静能IOCON时钟（使能->静能）
	LPC_GPIO0 -> DIR |= (1 << 1);
	LPC_GPIO0 -> DATA |= (1 << 1);
}


void Delay_inBuzzer()
{
	uint16_t i, j;
	for(i = 0; i < 3000; i++)
		for(j = 0; j < 200; j++);
}


void Judge_TempC(uint32_t temp)
{
	int t;
	if(temp >= 27)
	{
		
		for(t = 0;t < 50;t++)
		{
			Delay_inBuzzer();
			LPC_GPIO0 -> DATA &= ~(1 << 1);
			display_C(temp);
			Delay_inBuzzer();
			LPC_GPIO0 -> DATA |= (1 << 1);
		}
	}
}


void Judge_TempF(uint32_t temp)
{
	int t;
	if(temp >= 80)
	{
		for(t = 0;t < 50;t++)
		{
			Delay_inBuzzer();
			LPC_GPIO0 -> DATA &= ~(1 << 1);
			display_F(temp);
			Delay_inBuzzer();
			LPC_GPIO0 -> DATA |= (1 << 1);
		}
	}
}

