#include "stick.h"

int flag = 0;


void Delay(uint32_t ulTime)
{
	uint32_t i;
	i = 0;
	while(ulTime--){
		for(i = 0; i < 5000; i++);
	}
}


void PIOINT3_IRQHandler(void)
{
	if((LPC_GPIO3 -> MIS & (1 << 1)) == (1 << 1))					//显示摄氏度
	{
		Delay(200);
		flag++;
		if(flag > 2) 
			flag = 0;
		LPC_GPIO3 -> IC |= (1 << 1);												//清除第三引脚上的边沿检测逻辑			
	}
}


void stick(void)
{
	LPC_GPIO3->IE |= (1<<1); 														
	LPC_GPIO3->IS |= (1<<1);
	LPC_GPIO3->IEV &=~ (1<<1);
	NVIC_EnableIRQ(EINT3_IRQn);
}
