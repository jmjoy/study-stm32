#ifndef __KEY_H
#define __KEY_H

#include <stdbool.h>
#include "stm32f10x_conf.h"

#define KEY_COUNT 4

void Key_Init(void);
bool Is_Key_Down(int key);

#endif
