#ifndef _USART_H
#define _USART_H


#define DIR485_Usart1_Rx()     GPIO_ResetBits(GPIOA, GPIO_Pin_8)
#define DIR485_Usart1_Tx()     GPIO_SetBits(GPIOA, GPIO_Pin_8)

extern void UART1_onfiguration (void);
extern void USART1_SendChar(unsigned char Data);

extern char RX_data[1000];
extern int Rx_num;

#endif

