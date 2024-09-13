#ifndef _DS18B20_H_
#define _DS18B20_H_

#include "stm32f10x_conf.h"
#include "delay.h"
#include <stdbool.h>

void DS18B20_Init(void);
bool DS18B20_Reset(void);
void DS18B20_WriteByte(uint8_t data);
uint8_t DS18B20_ReadByte(void);
void DS18B20_ConvertT(void);
float DS18B20_ReadT(void);

#endif
