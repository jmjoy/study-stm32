#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x_conf.h"

#define USE_SORTWARE_SPI 0

#define MY_SPI_NSS GPIO_Pin_4
#define MY_SPI_SCK GPIO_Pin_5
#define MY_SPI_MISO GPIO_Pin_6
#define MY_SPI_MOSI GPIO_Pin_7

void MY_SPI_Init(void);
void MY_SPI_START(void);
void MY_SPI_STOP(void);
uint8_t MY_SPI_SWAP(uint8_t data);

#endif
