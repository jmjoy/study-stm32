#ifndef __EXTI0_H
#define __EXTI0_H

#include "stm32f10x_conf.h"

typedef enum {
    Falling = 0,
    Rising = 1,
} Exti1Trigger;

typedef void (*Exti1Handler)(Exti1Trigger);

void EXTI1_Init(void);

void Set_Exti1_Handler(Exti1Handler handler);

#endif
