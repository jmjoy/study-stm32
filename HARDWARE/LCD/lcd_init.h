#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "sys.h"

#define USE_HARDWARE_SPI 0

#define USE_HORIZONTAL 2

#if USE_HORIZONTAL == 0 || USE_HORIZONTAL == 1
#define LCD_W 80
#define LCD_H 160
#else
#define LCD_W 160
#define LCD_H 80
#endif

#define LCD_SCLK_Clr() GPIO_ResetBits(GPIOB, GPIO_Pin_3) // SCL=SCLK
#define LCD_SCLK_Set() GPIO_SetBits(GPIOB, GPIO_Pin_3)

#define LCD_MOSI_Clr() GPIO_ResetBits(GPIOB, GPIO_Pin_5) // SDA=MOSI
#define LCD_MOSI_Set() GPIO_SetBits(GPIOB, GPIO_Pin_5)

#define LCD_RES_Clr() GPIO_ResetBits(GPIOB, GPIO_Pin_6) // RES
#define LCD_RES_Set() GPIO_SetBits(GPIOB, GPIO_Pin_6)

#define LCD_DC_Clr() GPIO_ResetBits(GPIOB, GPIO_Pin_4) // DC
#define LCD_DC_Set() GPIO_SetBits(GPIOB, GPIO_Pin_4)

#define LCD_CS_Clr() GPIO_ResetBits(GPIOB, GPIO_Pin_7) // CS
#define LCD_CS_Set() GPIO_SetBits(GPIOB, GPIO_Pin_7)

#define LCD_BLK_Clr() GPIO_ResetBits(GPIOB, GPIO_Pin_8) // BLK
#define LCD_BLK_Set() GPIO_SetBits(GPIOB, GPIO_Pin_8)

void LCD_GPIO_Init(void);
void LCD_Writ_Bus(uint8_t dat);
void LCD_WR_DATA8(uint8_t dat);
void LCD_WR_DATA(uint16_t dat);
void LCD_WR_REG(uint8_t dat);
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_Init(void);
#endif
