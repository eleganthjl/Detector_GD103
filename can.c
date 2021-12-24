/**************************************************************************************
* Includes
**************************************************************************************/ 
#include "main.h"


User_CAN UserCan1;


//CAN发送使能标志
u8 CAN1_SEND_ENABLE=0;

/**
  * @brief  Configures CAN.
  * @param  None
  * @retval None
  */
void CAN_Int(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	
	CAN_DeInit(CAN1);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/*CAN1 IO Init*/
	/*PA11:GPIO_Mode_IPU
	  PA12:GPIO_Mode_AF_PP
	  PA15:GPIO_Mode_Out_PP*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_11;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_15;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_15);//使能1040
	
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);
	
//	NVIC_InitStruct.NVIC_IRQChannel = CAN1_SCE_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
//	NVIC_Init(&NVIC_InitStruct);
	
	
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
	
//	CAN_ITConfig(CAN1,CAN_IT_EWG|CAN_IT_BOF|CAN_IT_EPV|CAN_IT_ERR,ENABLE);// 不开CAN_IT_ERR不进中断，标志位不置位
//只开busoff错误中断
//	CAN_ITConfig(CAN1,CAN_IT_BOF|CAN_IT_ERR,ENABLE);// 不开CAN_IT_ERR不进中断，标志位不置位

	
  //CAN2SB=0x0E，即过滤器0-13：CAN1	 14-27：CAN2
//	u32 EXT_CAN_ID=0x12345678;
//	u32 STD_CAN_ID=0x0123;
	
	/*CAN1 filter initialization*/
	CAN_FilterInitTypeDef CAN_FilterInitStruct; 
	CAN_FilterInitStruct.CAN_FilterActivation     = ENABLE;
	CAN_FilterInitStruct.CAN_FilterFIFOAssignment = CAN_FilterFIFO0;
	CAN_FilterInitStruct.CAN_FilterIdHigh         = 0x0000;
	CAN_FilterInitStruct.CAN_FilterIdLow          = 0x0000;
	CAN_FilterInitStruct.CAN_FilterMaskIdHigh     = 0x0000;
	CAN_FilterInitStruct.CAN_FilterMaskIdLow      = 0x0000;
	CAN_FilterInitStruct.CAN_FilterMode           = CAN_FilterMode_IdMask;
	CAN_FilterInitStruct.CAN_FilterNumber         = 0;
	CAN_FilterInitStruct.CAN_FilterScale          = CAN_FilterScale_32bit;
	CAN_FilterInit(&CAN_FilterInitStruct);
	
	
	UserCan1.BaudRate=CANBaudRate_250K;
	
	/*CAN1 initialization*/
	CAN_InitTypeDef CAN_InitStruct;
	CAN_InitStruct.CAN_ABOM = ENABLE;//使能busoff自动重连
	CAN_InitStruct.CAN_AWUM = DISABLE;
	CAN_InitStruct.CAN_Mode = CAN_Mode_Normal;
	CAN_InitStruct.CAN_NART = DISABLE;//使能重复发送直到发送成功
	CAN_InitStruct.CAN_BS1  = CAN_BS1_4tq;//CAN_BS1_3tq;
	CAN_InitStruct.CAN_BS2  = CAN_BS2_3tq;//CAN_BS2_2tq;
	switch(UserCan1.BaudRate)
	{
//		case CANBaudRate_1M: 
//			CAN_InitStruct.CAN_Prescaler = 6;   // 36M/6/(1+3+2)=1M
//			break;               
		case CANBaudRate_500K: 
			CAN_InitStruct.CAN_Prescaler = 7;  // 28M/7/(1+4+3)=500K
			break;               
		case CANBaudRate_250K: 
			CAN_InitStruct.CAN_Prescaler = 14;  // 28M/14/(1+4+3)=250K
			break;     
		case CANBaudRate_125K: 
			CAN_InitStruct.CAN_Prescaler = 28;  // 28M/7/(1+4+3)=125K
			break;
//		case CANBaudRate_100K:
//			CAN_InitStruct.CAN_Prescaler = 60;  // 36M/60/(1+3+2)=100K
//			break;  
//		case CANBaudRate_50K:
//			CAN_InitStruct.CAN_Prescaler = 120; // 36M/120/(1+3+2)=50K
//			break;
//		case CANBaudRate_20K:
//			CAN_InitStruct.CAN_Prescaler = 300; // 36M/300/(1+3+2)=20K
//			break;
//		case CANBaudRate_10K:
//			CAN_InitStruct.CAN_Prescaler = 600; // 36M/600/(1+3+2)=10K
//			break;
		default: break;
	}
	CAN_InitStruct.CAN_RFLM = DISABLE;
	CAN_InitStruct.CAN_SJW  = CAN_SJW_1tq;
	CAN_InitStruct.CAN_TTCM = DISABLE;
	CAN_InitStruct.CAN_TXFP = ENABLE;
	CAN_Init(CAN1,&CAN_InitStruct);

}


/***************************************************************************************
**Function : CAN发送
**Parameter: CANx:CAN通道
**Return   : 
**Author   : 
**Time     : 
**--------------------------------------------------------------------------------------
**Modifier :
**Time     :
***************************************************************************************/
void Send_CAN_Data(CAN_TypeDef* CANx)  
{
	u8 mbox;
	
	if(CANx==CAN1)//CAN1
	{
		if((SEND_CAN_ID1&0xFFFFF800)!=0)   //清空低11位，若不为0则判定为拓展帧，否则为标准帧
		{
			UserCan1.TxMessage.IDE   = CAN_ID_EXT;
			UserCan1.TxMessage.ExtId = SEND_CAN_ID1;
		}
		else
		{
			UserCan1.TxMessage.IDE   = CAN_ID_STD;
			UserCan1.TxMessage.ExtId = 0;
			UserCan1.TxMessage.StdId = SEND_CAN_ID1;
		}
		UserCan1.TxMessage.DLC   = 8;
		
		//发送协议
		UserCan1.TxMessage.Data[0]=0;
		UserCan1.TxMessage.Data[1]=0;
		UserCan1.TxMessage.Data[2]=0;
		UserCan1.TxMessage.Data[3]=0;
		UserCan1.TxMessage.Data[4]=0;
		UserCan1.TxMessage.Data[5]=0;
		UserCan1.TxMessage.Data[6]=0;
		UserCan1.TxMessage.Data[7]=0;
		//
		
		mbox = CAN_Transmit(CAN1,&UserCan1.TxMessage);
		while(CAN_TransmitStatus(CAN1, mbox) == CAN_TxStatus_Failed);
	}
	else//CAN2
	{
		
	}
}




/***************************************************************************************
**Function : CAN1错误中断
**Parameter: None
**Return   : None
**Author   : 胡锦炉
**Time     : 2018.6.4
**--------------------------------------------------------------------------------------
**Modifier :
**Time     :
***************************************************************************************/

void CAN1_SCE_IRQHandler(void)
{
//	if(CAN_GetITStatus(CAN1,CAN_IT_EWG)!=RESET)
//	{
//		CAN_ClearITPendingBit(CAN1,CAN_IT_EWG);
//		//CAN1_SEND_ENABLE=0;
//	}
//	if(CAN_GetITStatus(CAN1,CAN_IT_EPV)!=RESET)
//	{
//		CAN_ClearITPendingBit(CAN1,CAN_IT_EPV);
//		//CAN1_SEND_ENABLE=0;
//	}
	if(CAN_GetITStatus(CAN1,CAN_IT_BOF)!=RESET)
	{
		CAN_ClearITPendingBit(CAN1,CAN_IT_BOF);
		CAN1_SEND_ENABLE=0;
	}
}







void CAN_Analysis(void)//协议处理
{
	
	
}











//中断函数
void USB_LP_CAN1_RX0_IRQHandler(void)
{

	 UserCan1.RxMessage.StdId=0x00;
   UserCan1.RxMessage.ExtId=0x00;
   UserCan1.RxMessage.IDE=0;
   UserCan1.RxMessage.DLC=0;
   UserCan1.RxMessage.FMI=0;
	
  CAN_Receive(CAN1,CAN_FIFO0, &UserCan1.RxMessage);
  
	if(CAN_GetITStatus(CAN1,CAN_IT_FMP0)!=RESET)
	{
		CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);
		CAN_Receive(CAN1,CAN_FIFO0, &UserCan1.RxMessage);
		CAN_FIFORelease(CAN1,CAN_FIFO0);
	
    if(
		  ((UserCan1.RxMessage.ExtId!=0x00) && (UserCan1.RxMessage.IDE==CAN_ID_EXT)&&(UserCan1.RxMessage.DLC>0))//扩展帧
	  ||((UserCan1.RxMessage.StdId!=0x00) && (UserCan1.RxMessage.IDE==CAN_Id_Standard)&&(UserCan1.RxMessage.DLC>0))//标准帧	
	    )
    {
  	 CAN_Analysis();//协议处理
    }
		
	}
}















