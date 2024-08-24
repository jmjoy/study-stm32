#ifndef __BREATH_H
#define __BREATH_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

void Breathing_Init(uint16_t PSC, uint16_t ARR);

void Breathing_SetCCR1(uint16_t Compare1);

void Breathing_SetARR(uint16_t ARR);

#endif
