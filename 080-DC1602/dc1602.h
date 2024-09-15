#ifndef __DC_1602__
#define __DC_1602__

#include "stm32f10x_conf.h"
#include "delay.h"

typedef enum {
    MoveLeft = 0,
    MoveRight = 1
} MoveDirection;

void DC1602_Init(void);
void DC1602_WriteString(uint8_t row, uint8_t col, char *str);
void DC1602_MoveScreen(MoveDirection direction);

#endif
