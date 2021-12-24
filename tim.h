#ifndef _tim_H
#define _tim_H

//�������
//PWM�ṹ����
typedef struct	
{
	unsigned int FreReg;	//
	unsigned int Prescaler;//��Ƶ   
  unsigned int Current;	//��ǰ
	unsigned int Setting;	//����ֵ
  int SpeedSet;	//ת���趨
}STRU_PWM;

extern STRU_PWM StruPWM1,StruPWM2,StruPWM3,StruPWM4;

#define Vale_APB1CLK    56000000//
#define Vale_APB2CLK    56000000//
#define Value_FrequencyInit  250//
#define Value_BaudRateUart1  9600//

void TIM2Init(void);

void TIM4Init(void);
void PWM_SetRate1(unsigned int rate);
void PWM_SetRate2(unsigned int rate);
void PWM_SetRate3(unsigned int rate);
void PWM_SetRate4(unsigned int rate);



#endif

