



#include "main.h"

/***************************************************************************************
**Function : IO口初始化
**Parameter: 
**Return   : None
**Author   : 
**Time     : 
**--------------------------------------------------------------------------------------
**Modifier :
**Time     :
***************************************************************************************/
void GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//13 14 15 LED
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init(GPIOC,&GPIO_InitStruct);

	//LED_IN
	  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_12;
	  GPIO_Init(GPIOB,&GPIO_InitStruct);	
	
	//15 OUT_SW
	  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_15;
	  GPIO_Init(GPIOB,&GPIO_InitStruct);	
	
	
}


/***************************************************************************************
**Function : 状态输出
**Parameter: 
**Return   : 0 地 ,1 3.3V ,2 高阻
**Author   : 
**Time     : 
**--------------------------------------------------------------------------------------
**Modifier :
**Time     :
***************************************************************************************/
void LED_OUT_Sta(char sta)
{
	if(2==sta)
	{
		GPIO_InitTypeDef GPIO_InitStruct;
	
	  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_13;
	  GPIO_Init(GPIOB,&GPIO_InitStruct);
	}
	else
	{
		GPIO_InitTypeDef GPIO_InitStruct;
	
	  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_13;
	  GPIO_Init(GPIOB,&GPIO_InitStruct);
		
		if(1==sta)GPIO_SetBits(GPIOB,GPIO_Pin_13);
		else if(0==sta)GPIO_ResetBits(GPIOB,GPIO_Pin_13);	
	}
}


