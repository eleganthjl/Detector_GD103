#ifndef _AD_H
#define _AD_H

#define ADC_Channel_Number 3//10+2         //ADC1通道数量 一路内部温度 一路内部参考电压
#define NUM_SAMTIMES 10 //每个通道采集数量
//#define ADC1_DR		0x4001244C

//extern uint32_t ADC_data[ADC_Channel_Number];

extern void ADC1Init(void);
extern int ADC_Read(unsigned char ch);

#endif

