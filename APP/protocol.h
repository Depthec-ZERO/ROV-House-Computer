#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_
#include "stm32f10x.h"


extern uint16_t pitch,roll,yaw;
extern uint16_t depth;
extern uint8_t battery;






/******************************************************************************
							全局函数声明
*******************************************************************************/ 
void Status_Get(void);  
void Send_Command(void); 






#endif

