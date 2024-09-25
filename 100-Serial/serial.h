#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "stm32f10x_conf.h"

#define USART1_TX  GPIO_Pin_9
#define USART1_RX  GPIO_Pin_10

void Serial_Init(void);
void Serial_SendByte(uint8_t data);

#endif
