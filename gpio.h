

#ifndef _GPIO_H
#define _GPIO_H

//LED
#define LED_YELLOW_ON  GPIO_SetBits(GPIOC,GPIO_Pin_13);
#define LED_YELLOW_OFF GPIO_ResetBits(GPIOC,GPIO_Pin_13);

#define LED_WHITE_ON  GPIO_SetBits(GPIOC,GPIO_Pin_14);
#define LED_WHITE_OFF GPIO_ResetBits(GPIOC,GPIO_Pin_14);

#define LED_RED_ON  GPIO_SetBits(GPIOC,GPIO_Pin_15);
#define LED_RED_OFF GPIO_ResetBits(GPIOC,GPIO_Pin_15);

//OUT_SW
#define OUT_SW_ON  GPIO_SetBits(GPIOB,GPIO_Pin_15);
#define OUT_SW_OFF GPIO_ResetBits(GPIOB,GPIO_Pin_15);

#define LED_IN_Sta GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)


extern void GPIOInit(void);
extern void LED_OUT_Sta(char sta);

#endif

