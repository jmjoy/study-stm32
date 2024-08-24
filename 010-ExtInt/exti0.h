#ifndef __EXTI0_H
#define __EXTI0_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

typedef void (*Exti0Handler)(void);

void EXTI0_Init(void);

void Set_Exti0_Handler(Exti0Handler handler);

#endif
