


#ifndef _can_H
#define _can_H

typedef enum CANBaudRate
{
	CANBaudRate_1M,
	CANBaudRate_500K,
	CANBaudRate_250K,
	CANBaudRate_125K,
	CANBaudRate_100K,
	CANBaudRate_50K,
	CANBaudRate_20K,
	CANBaudRate_10K
}CANBaudRate_Type;

typedef struct
{
	CanRxMsg RxMessage;
	CanTxMsg TxMessage;
	CANBaudRate_Type BaudRate;
}User_CAN;

extern User_CAN UserCan1;


extern void CAN_Int(void);
extern void Send_CAN_Data(CAN_TypeDef* CANx);  


#define SEND_CAN_ID1 ((unsigned long)0x18F5F953)


#endif

