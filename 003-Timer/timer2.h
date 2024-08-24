#ifndef __TIME_H__
#define __TIME_H__

#include <stdbool.h>
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

typedef void (*TimHandler)(void);

void TIM2_Init(bool is_external);
void Set_TIM2_Handler(TimHandler);
uint16_t Get_Timer_Count(void);

#endif
