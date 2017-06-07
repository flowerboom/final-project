#include "LPC11xx.h"
#include "delay.h"
#include "KEY.h"

//#define KEY_U  LPC_GPIO3->DIR&=~(1<<0)  
//#define KEY_D  LPC_GPIO3->DIR&=~(1<<1)
//#define KEY_A  LPC_GPIO3->DIR&=~(1<<2)
//#define KEY_B  LPC_GPIO3->DIR&=~(1<<3)


void  key_init(void)
{
		LPC_GPIO3->DIR&=~(1<<0);
    LPC_GPIO3->DIR&=~(1<<1);
    LPC_GPIO3->DIR&=~(1<<2);
    LPC_GPIO3->DIR&=~(1<<3);
}


KEY_STATUS key_get(void )
{
  if((LPC_GPIO3->DATA&(1<<0))==0)  	//如果按键1被按下
		{
			delay();			  	//延时消抖
			if((LPC_GPIO3->DATA&(1<<0))==0)//如果还是按下状态
			{
				return KEY_DOWN;
			}
			//else return KEY_UP;
		}
  else return KEY_UP;		

		if((LPC_GPIO3->DATA&(1<<1))==0)	   	//如果按键2被按下
		{
			delay();
			if((LPC_GPIO3->DATA&(1<<1))==0)	//如果还是按下状态
			{
			  return KEY_DOWN;
			}
		}
			else return KEY_UP;
		

		if((LPC_GPIO3->DATA&(1<<2))==0)
		{
			delay();			  	//延时消抖
			if((LPC_GPIO3->DATA&(1<<2))==0)	//如果还是按下状态
				{
				return KEY_DOWN;
				}
		
      //else return KEY_UP;
	  }
		else return KEY_UP;
		
		if((LPC_GPIO3->DATA&(1<<3))==0)
		{
			delay();			  	//延时消抖
			if((LPC_GPIO3->DATA&(1<<3))==0)	//如果还是按下状态
				{
				return KEY_DOWN;
				}
		
      //else return KEY_UP;
	  }
		else return KEY_UP;
}
