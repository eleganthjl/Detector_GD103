#ifndef _AD_H
#define _AD_H

#define ADC_Channel_Number 3//10+2         //ADC1ͨ������ һ·�ڲ��¶� һ·�ڲ��ο���ѹ
#define NUM_SAMTIMES 10 //ÿ��ͨ���ɼ�����
//#define ADC1_DR		0x4001244C

//extern uint32_t ADC_data[ADC_Channel_Number];

extern void ADC1Init(void);
extern int ADC_Read(unsigned char ch);

#endif

