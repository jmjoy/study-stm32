#ifndef __IC_H
#define __IC_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

void IC_init(void);

uint32_t IC_GetFreq(void);

uint16_t IC_GetDuty(void);

#endif
