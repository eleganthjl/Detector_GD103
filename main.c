/****************************Copyright (c)*********************************************                                     
**
**               (c) Copyright 2018, TongDa, CHINA 
**                            All Rights Reserved
**
**			           广州市白云区通达汽车电气股份有限公司
**                      http://www.bailitong.com                        
**
*--------------file imformation-------------------------------------------------------
** File name   : main.c
** Author      : 
** Time        : 
** Description : 主程序C语言入口
** Version     : 
*--------------------------------------------------------------------------------------
**************************************************************************************/


#include "main.h"
、、


unsigned int timer=0;
//u16 wdata[512]={11,22,33,44,55,66,77,88};
//u16 rdata[512]={11,22,33,44,55,66,77,88};
//u32 waddrtest=0x800fC00;
//u32 raddrtest=0x800fC00;
//u16 rNtest=10;
//u16 wNtest=10;

//	int i;
//	for(i=0;i<512;i++)wdata[i]=i;

//		 while(WriteParaToFlash(waddrtest, wdata , wNtest)){}
//		 while(ReadParaFromFlash(raddrtest, rdata, rNtest)){}
int ADC_V[12];
char LED_IN_S;

int main(void)
{
	
  RCC_Configuration();	//系统时钟初始化
	NVIC_Configuration();
	GPIOInit();	
	UART1_onfiguration ();
	CAN_Int();
	TIM4Init();
	TIM2Init();
	ADC1Init();
	//Watch_Dog();   
//	__enable_irq();

	char ii=0;
	
	
   while(1)
	 {	
		 
//		 PWM_SetRate1(10);
//		 PWM_SetRate2(20);
//		 PWM_SetRate3(30);
//		 PWM_SetRate4(40);
		 
		 for(ii=0;ii<3;ii++)
		 {
			 ADC_V[ii]=ADC_Read(ii);
		 }
		 Send_CAN_Data(CAN1);
//		 ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_41Cycles5);//
//		 ADC_SoftwareStartConvCmd(ADC1,ENABLE);
//		 while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
//		 ADC_data[0]=ADC_GetConversionValue(ADC1);
//		 
//		  ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_41Cycles5);//
//		 ADC_SoftwareStartConvCmd(ADC1,ENABLE);
//		 while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
//		 ADC_data[1]=ADC_GetConversionValue(ADC1);

//		 ADC_RegularChannelConfig(ADC1,ADC_Channel_16,1,ADC_SampleTime_239Cycles5);//
//		 ADC_SoftwareStartConvCmd(ADC1,ENABLE);
//		 while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
//		 ADC_data[2]=ADC_GetConversionValue(ADC1);
//		 
//		 ADC_RegularChannelConfig(ADC1,ADC_Channel_17,1,ADC_SampleTime_239Cycles5);//
//		 ADC_SoftwareStartConvCmd(ADC1,ENABLE);
//		 while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
//		 ADC_data[3]=ADC_GetConversionValue(ADC1);
		 
		 LED_YELLOW_ON;
		 LED_WHITE_ON;
		 LED_RED_ON;
		 OUT_SW_ON;
		 LED_OUT_Sta(0);
		 SysTick_Delay_ms(1000);
		 LED_IN_S=LED_IN_Sta;
		 IWDG_ReloadCounter();
		 
		 LED_YELLOW_OFF;
		 LED_WHITE_OFF;
		 LED_RED_OFF;
		 OUT_SW_OFF;
		 LED_OUT_Sta(1);
		 SysTick_Delay_ms(1000);
		 LED_IN_S=LED_IN_Sta;
		 IWDG_ReloadCounter();
		 
		 
		 LED_YELLOW_OFF;
		 LED_WHITE_OFF;
		 LED_RED_OFF;
		 OUT_SW_OFF
		 LED_OUT_Sta(2);
		 SysTick_Delay_ms(1000);
		 LED_IN_S=LED_IN_Sta;
		 IWDG_ReloadCounter();
		 
		 
		 //SysTick_Delay_ms(1);
		 SysTick_Delay_ms(1000);
		 //SysTick_Delay_ms(10);
//		 if(Rx_num>0)
//		 {
//			 for(timer=0;timer<Rx_num;timer++)USART1_SendChar(RX_data[timer]);	
//       Rx_num=0;		 
//		 }
		 
		 IWDG_ReloadCounter();
	 }
}


 

