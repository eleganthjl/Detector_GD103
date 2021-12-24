#ifndef _tim_H
#define _tim_H

//定义变量
//PWM结构变量
typedef struct	
{
	unsigned int FreReg;	//
	unsigned int Prescaler;//分频   
  unsigned int Current;	//当前
	unsigned int Setting;	//设置值
  int SpeedSet;	//转速设定
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

