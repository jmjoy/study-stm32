#ifndef __BTN_H
#define __BTN_H

#include <stdbool.h>
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "delay.h"

void btn_init(void);

bool is_btn_down(void);

#endif
