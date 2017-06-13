#include "display.h"

uint32_t table[10]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};


void delay(void)
{
	uint16_t i = 4000;
	while(i--)
		;
}


void display_C(uint32_t value)
{	
		LPC_GPIO2->DIR |= 0xFFF;	
		LPC_GPIO2 -> DATA &= ~(0xFF);
		LPC_GPIO2 -> DATA |= 0xC6;
		LPC_GPIO2 -> DATA &= ~(1 << 11);
		delay();
		LPC_GPIO2 -> DATA = 0xFFF;		
		LPC_GPIO2 -> DATA &= ~(0xFF);
		LPC_GPIO2 -> DATA |= 0x9C;
		LPC_GPIO2 -> DATA &= ~(1 << 10);
		delay();
		LPC_GPIO2 -> DATA = 0xFFF;
		LPC_GPIO2 -> DATA &= ~(0xFF);
		LPC_GPIO2 -> DATA |= table[value % 10];
		LPC_GPIO2 -> DATA &= ~(1 << 9);
		delay();
		LPC_GPIO2 -> DATA = 0xFFF;
		LPC_GPIO2 -> DATA &= ~(0xFF);
		LPC_GPIO2 -> DATA |= table[value / 10];	
		LPC_GPIO2 -> DATA &= ~(1 << 8);
		delay();
		LPC_GPIO2->DATA = 0xFFF;	
}


void display_F(uint32_t value)
{
		LPC_GPIO2->DIR |= 0xFFF;	
		LPC_GPIO2 -> DATA &= ~(0xFF);
		LPC_GPIO2 -> DATA |= 0x8E;
		LPC_GPIO2 -> DATA &= ~(1 << 11);
		delay();
		LPC_GPIO2 -> DATA = 0xFFF;		
		LPC_GPIO2 -> DATA &= ~(0xFF);
		LPC_GPIO2 -> DATA |= 0x9C;
		LPC_GPIO2 -> DATA &= ~(1 << 10);
		delay();
		LPC_GPIO2 -> DATA = 0xFFF;
		LPC_GPIO2 -> DATA &= ~(0xFF);
		LPC_GPIO2 -> DATA |= table[value % 10];
		LPC_GPIO2 -> DATA &= ~(1 << 9);
		delay();
		LPC_GPIO2 -> DATA = 0xFFF;
		LPC_GPIO2 -> DATA &= ~(0xFF);
		LPC_GPIO2 -> DATA |= table[value / 10];	
		LPC_GPIO2 -> DATA &= ~(1 << 8);
		delay();
		LPC_GPIO2->DATA = 0xFFF;	
}
