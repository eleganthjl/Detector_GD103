
/*

TIM4  PWM
*/



#include "main.h"

//PWM 输出
STRU_PWM StruPWM1,StruPWM2,StruPWM3,StruPWM4;

/***************************************************************************************
**Function : TIM2初始化 5ms定时
**Parameter: None
**Return   : None
**Author   : 丘嘉乐
**Time     : 2018.1.12
**--------------------------------------------------------------------------------------
**Modifier :
**Time     :
***************************************************************************************/
void TIM2Init(void)
{
	uint16_t Prescaler;
	Prescaler=(5*(Vale_APB1CLK/1000000))-1;//单位ms
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode   = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period        = 999;//
	TIM_TimeBaseInitStruct.TIM_Prescaler     = Prescaler;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel                   = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority        = 2;
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
}


void TIM4Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8| GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	
	StruPWM1.Prescaler=Vale_APB1CLK/(1000*Value_FrequencyInit);
	StruPWM2.Prescaler=StruPWM1.Prescaler;
	StruPWM3.Prescaler=StruPWM1.Prescaler;
	StruPWM4.Prescaler=StruPWM1.Prescaler;
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode   = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period        = 999;//1000
	TIM_TimeBaseInitStruct.TIM_Prescaler     = StruPWM1.Prescaler - 1;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCInitStruct.TIM_OCMode      = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity  = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_Pulse       = 0;
	TIM_OC1Init(TIM4,&TIM_OCInitStruct);
	TIM_OC2Init(TIM4,&TIM_OCInitStruct);
	TIM_OC3Init(TIM4,&TIM_OCInitStruct);
	TIM_OC4Init(TIM4,&TIM_OCInitStruct);
	
	TIM_CtrlPWMOutputs(TIM4,ENABLE);
	TIM_Cmd(TIM4,ENABLE);
}

void PWM_SetRate1(unsigned int rate)
{
	if(rate<=100)
	{
	   TIM_SetCompare1(TIM4,(uint16_t)rate*10);
		 StruPWM1.Current=rate;
	}
}

void PWM_SetRate2(unsigned int rate)
{
	if(rate<=100)
	{
	   TIM_SetCompare2(TIM4,(uint16_t)rate*10);
		 StruPWM2.Current=rate;
	}
}

void PWM_SetRate3(unsigned int rate)
{
	if(rate<=100)
	{
	   TIM_SetCompare3(TIM4,(uint16_t)rate*10);
		 StruPWM3.Current=rate;
	}
}

void PWM_SetRate4(unsigned int rate)
{
	if(rate<=100)
	{
	   TIM_SetCompare4(TIM4,(uint16_t)rate*10);
		 StruPWM4.Current=rate;
	}
}


/***************************************************************************************
**Function : TIM2溢出中断
**Parameter: None
**Return   : None
**Author   : 丘嘉乐
**Time     : 2018.1.12
**--------------------------------------------------------------------------------------
**Modifier :
**Time     : 
***************************************************************************************/
unsigned int CAN_TX_TIMER=0;
void TIM2_IRQHandler()//5ms
{	
	
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		
		CAN_TX_TIMER+=5;
		if(CAN_TX_TIMER>100000)CAN_TX_TIMER=0;

	}
}


