#include "ADC.h"


void ADC_Init(void)
{
	LPC_SYSCON -> SYSAHBCLKCTRL |= (1 << 16);
	LPC_IOCON -> PIO1_11 &= ~0xBF;																														//配置模拟输入
	LPC_IOCON -> PIO1_11 |= 0x01;																															//模拟通道输入0
	LPC_SYSCON -> PDRUNCFG &= ~(0x01 << 4);
	LPC_SYSCON -> SYSAHBCLKCTRL |= (1 << 13);																									//使能ADC模块
	LPC_ADC->CR = (0x01 << 7)|																																//选用通道ADC7
							((SystemCoreClock / 1000000 - 1) << 8)|																				//时钟设置，转换时钟1MHZ
							(0 << 16)|																																		//软件控制转换操作模式
							(0 << 17)|																																		//每次转换占用的时钟数，这里是11个。使用11 clocks转换
							(0 << 24)|																																		//先不启动，即ADC转换停止
							(0 << 27);																																		//上升沿启动转换，即直接启动ADC转换，此位无效
}


uint32_t temProcess(void)																																		//处理温度函数
{
			
		//算法所需变量
		float R;   					 	          																												//热敏电阻R
		float Re[18]={0.3952,0.5046,0.6510,0.8502,1.124,1.506,2.047,2.823,3.958,5.648,8.221,12.124,18.68,29.37,47.73,80.36,140.0,249.6};
		int temperature[18]={130,120,110,100,90,80,70,60,50,40,30,20,10,0,-10,-20,-30,-40};
		float unit;
		float Temperature;
		uint8_t n;
		
		//采集数据所需变量
		uint32_t i;
		uint32_t ulADCData;
		uint32_t ulADCBuf;
		ulADCData = 0;


		for(i = 0; i < 10; i++)
	  {
			LPC_ADC -> CR |= (1 << 24);																														//立即转换
			while((LPC_ADC -> DR[7] & 0x80000000) == 0);																					//读取DR置7位，转换完成，
			LPC_ADC -> CR |= (1 << 24);
			while((LPC_ADC -> DR[7] & 0x80000000) == 0);																					//丢弃以前的第一次
			ulADCBuf = LPC_ADC -> DR[7];																													//读取结果寄存器
			ulADCBuf = (ulADCBuf >> 6) & 0x3ff;																										//11个1，数据从第六位开始存储，占据十位
			ulADCData += ulADCBuf;
		}
		ulADCData = ulADCData / 10;
		ulADCData = (ulADCData * 3300) / 1024;																									//数字量转换成模拟量
		
		
		//由此开始进行采集数据的算法处理，经过算法变成温度		

		//R = (ulADCData/1000)/ ((3.3 - (ulADCData / 1000)) / 10000);      											//如果不先化简，就会把小数点后的位数删掉，所以分母变大有误差					
		
		R = (ulADCData*10*1.0)/(3.3-(ulADCData/ 1000));																					//热敏电阻的电阻求解公式，单位欧姆
		
		R = R / 1000;																																						//转换为千欧姆
		if((R < 0.3952) || (R >249.6))                     																			//判断是否在所测电阻范围之内，否则溢出防止出错设置为0
		Temperature = 0;
		else
		{
			for(n = 0; n < 18; n++)
			{
				if((R > Re[n]) && (R < Re[n + 1]))
				{
					unit = (Re[n + 1] - Re[n]) / 10;                   																//计算单位刻度温度所对应的电阻阻值
					Temperature = temperature[n+1] - (R - Re[n]) / unit;															//由Tn加上所需多少的温度刻度，到达应运算正确温度值
				}
			}
		}
		return Temperature;                          
}

