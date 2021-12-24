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







//PA8 en  usart1
/****************************************************************************************
** 功能描述: UART1配置
** 参    数: None
** 返 回 值: None       
** 作　  者: 
** 日  　期: 
**---------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void UART1_onfiguration (void)  
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  USART_ClockInitTypeDef  USART_ClockInitStructure;						
  
  /* Enable USART1 clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE);

  /* Configure USARTx_Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USARTx_Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure PA1 as Output,DIR */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;//设置为输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure the USART1 synchronous paramters */
  USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
  USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
  USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
  USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
  
  USART_ClockInit(USART1, &USART_ClockInitStructure);
  
  /* USARTx configuration ------------------------------------------------------*/
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  /* Configure the USARTx */ 
  USART_Init(USART1, &USART_InitStructure);

  /*Set receive interrupt of UART1*/
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);


  /* Enable the USART Receive interrupt: this interrupt is generated when the 
   USART1 receive data register is not empty */
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  /* Enable the USARTx */
  USART_Cmd(USART1, ENABLE);      

  DIR485_Usart1_Rx();//设置为接收状态      
}

/****************************************************************************************
** 功能描述: UART1 发送字符
** 参    数: Data: 待发送数据
** 返 回 值: None       
** 作　  者: 
** 日  　期:
**---------------------------------------------------------------------------------------
** 修 改 人: 
** 日　  期: 
**--------------------------------------------------------------------------------------
****************************************************************************************/
void USART1_SendChar(unsigned char Data)
{
	DIR485_Usart1_Tx();
	SysTick_Delay_us(50);
  /* Transmit Data */
  USART_SendData(USART1, Data);
	
	SysTick_Delay_us(1100);
	
  DIR485_Usart1_Rx();
}


/***************************************************************************************
**Function : USART1接收中断
**Parameter: None
**Return   : None
**Author   : 丘嘉乐
**Time     : 2018.1.12
**--------------------------------------------------------------------------------------
**Modifier :
**Time     :
***************************************************************************************/
char RX_data[1000];
int Rx_num;
void USART1_IRQHandler (void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{
		USART_ClearFlag(USART1,USART_FLAG_RXNE);
		RX_data[Rx_num] = USART_ReceiveData(USART1);
		Rx_num++;
		//USART2_SendChar(data);
	}
	;
}






