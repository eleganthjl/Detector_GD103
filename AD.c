
#include "main.h"

uint32_t ADC_data[ADC_Channel_Number*NUM_SAMTIMES];//ADC-DMA 原始数据
/***************************************************************************************
**Function : ADC1初始化
**Parameter: None
**Return   : None
**Author   : 
**Time     : 
**--------------------------------------------------------------------------------------
**Modifier : 
**Time     : 
***************************************************************************************/
void ADC1Init(void)
{
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	/*Set ADCCLK as 28/4=7M, open ADCCLK*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;	
	/*PA0 PA1 PA2 PA3 PA4: GPIO_Mode_AIN*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 ;//| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7; 
	GPIO_Init(GPIOA,&GPIO_InitStruct);
//	/*PB0 PB1: GPIO_Mode_AIN*/
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
//	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1; 
//	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	
	/*Set DMA to tranmit and save the ADC data in the array ADC1_Control.ADC_Data[ADC_Data_Number];*/
	DMA_DeInit(DMA1_Channel1);
	DMA_InitTypeDef DMA_InitStruct;
	DMA_InitStruct.DMA_BufferSize 				= ADC_Channel_Number*NUM_SAMTIMES;
	DMA_InitStruct.DMA_DIR        				= DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_M2M 								= DMA_M2M_Disable;
	DMA_InitStruct.DMA_MemoryBaseAddr 		= (uint32_t)&ADC_data;
	DMA_InitStruct.DMA_MemoryDataSize 		= DMA_MemoryDataSize_Word;
	DMA_InitStruct.DMA_MemoryInc 					= DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_Mode 							= DMA_Mode_Circular;
	DMA_InitStruct.DMA_PeripheralBaseAddr = (u32)(&ADC1->DR);
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStruct.DMA_PeripheralInc 			= DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Priority					  = DMA_Priority_VeryHigh;
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);

	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruct.ADC_DataAlign          = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_Mode               = ADC_Mode_Independent;
	ADC_InitStruct.ADC_NbrOfChannel       = ADC_Channel_Number;
	ADC_InitStruct.ADC_ScanConvMode       = ENABLE;
	ADC_Init(ADC1,&ADC_InitStruct);
	
	ADC_TempSensorVrefintCmd(ENABLE);
	
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1,ENABLE);
	
	/*Calibrate ADC*/
	ADC_ResetCalibration(ADC1);	
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_239Cycles5);//
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_239Cycles5);//
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_239Cycles5);//
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_41Cycles5);//
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_4,5,ADC_SampleTime_41Cycles5);//
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_5,6,ADC_SampleTime_41Cycles5);//
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_6,7,ADC_SampleTime_41Cycles5);//
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_7,8,ADC_SampleTime_41Cycles5);//
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_8,9,ADC_SampleTime_41Cycles5);//
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_9,10,ADC_SampleTime_41Cycles5);//
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_TempSensor,11,ADC_SampleTime_239Cycles5);//(1.43-V)/0.0043+25
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_Vrefint,12,ADC_SampleTime_239Cycles5);//


	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	
	
//	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
//		 ADC_data[3]=ADC_GetConversionValue(ADC1);
	
}


int ADC_Read(unsigned char ch)
{
  int i;
  unsigned char num_ad=NUM_SAMTIMES;
  unsigned int get_val[NUM_SAMTIMES];
  unsigned int get_ad,val_min,val_max,val_sum,val_avg;
  int val;

  //取平均值
  for(i=0;i<num_ad;i++)
  {
	  get_ad=ADC_data[i*ADC_Channel_Number+ch];//读AD值
		get_val[i]=get_ad;	
  }
  val_max=get_val[0];
  val_min=get_val[0];
  val_sum=0;
  for(i=0;i<num_ad;i++)
  {
		  if(get_val[i]>val_max)
		    val_max=get_val[i];
		  if(get_val[i]<val_min)
		    val_min=get_val[i];
		  val_sum+=get_val[i];
  }
  val_avg=(val_sum-val_max-val_min)/(num_ad-2);
	//调试
	//{
	//  char strdebug[100];
	//  UART_Send(1,"laozj",5);
		//sprintf(strdebug,"\r\val_min=0x%4x,val_max=0x%4x,val_avg=0x%4x\r\n",val_min,val_max,val_avg);
	//	sprintf(strdebug,"0=0x%2x,1=0x%2x,2=0x%2x,3=0x%2x,4=0x%2x,5=0x%2x,6=0x%2x,7=0x%2x",ADCConvertedValue[0],ADCConvertedValue[1],ADCConvertedValue[2],ADCConvertedValue[3],ADCConvertedValue[4],ADCConvertedValue[5],ADCConvertedValue[6],ADCConvertedValue[7]);
	//  Debug_Message(strdebug);
	//}
	
  if(val_max-val_min>200)//读取的偏差大于0.5V时报错
    val=-1000;//报错,即温度-100度
  else
  {
        get_ad=val_avg;
      
        double v,v_div,r1,r2;
        v=3300;//mV
		    v_div=get_ad*v/4095;
//        r1=10000;//欧
//        r2=20000;//欧
//        v_div=get_ad*v*((r1+r2)/r2)/4096;//V,分压,5V最大输入，经过20/(10+20)分压，12位传感器
//        //v_div=get_ad*v/1024;//V,由于运放放大倍数不定，所以直接返回原始数据
        val=(int)v_div;//返回mv
      
  }
  //val=get_ad;
  return val;
}

////



