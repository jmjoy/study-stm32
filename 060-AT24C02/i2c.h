#ifndef __I__2C_H
#define __I__2C_H

#include <stdbool.h>
#include "stm32f10x_conf.h"
#include "delay.h"

#define I2C_GPIO GPIOB
#define I2C_SCL GPIO_Pin_0
#define I2C_SDA GPIO_Pin_1

#define I2C_READ 1
#define I2C_WRITE 0

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
bool I2C_ReadAck(void);
void I2C_WriteAck(bool ack);
void I2C_WriteByte(uint8_t data);
uint8_t I2C_ReadByte(void);

#endif
