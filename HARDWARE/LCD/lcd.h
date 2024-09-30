#ifndef __LCD_H
#define __LCD_H

#include "sys.h"
#include <stdlib.h>
#include <string.h>

typedef enum {
    Acsii_1206 = 0,
    Acsii_1608 = 0x0474,
    Acsii_2412 = 0x0A64,
    Acsii_3212 = 0x01C34,
    GB2312_12X12 = 0x33F4,
    GB2312_16X16 = 0x332A6,
    GB2312_24X24 = 0x730E8,
    GB2312_32X32 = 0x102CFA,
} FontAddr;

void LCD_Fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend,
              uint16_t color);
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                  uint16_t color);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                       uint16_t color);
void Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);

void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint16_t fc, uint16_t bc,
                  uint8_t sizey, uint8_t mode);
void LCD_ShowString(uint16_t x, uint16_t y, const char *p, uint16_t fc,
                    uint16_t bc, uint8_t sizey, uint8_t mode);
u32 mypow(uint8_t m, uint8_t n);
void LCD_ShowIntNum(uint16_t x, uint16_t y, uint16_t num, uint8_t len,
                    uint16_t fc, uint16_t bc, uint8_t sizey);
void LCD_ShowFloatNum1(uint16_t x, uint16_t y, float num, uint8_t len,
                       uint16_t fc, uint16_t bc, uint8_t sizey);

void LCD_ShowPicture(uint16_t x, uint16_t y, uint16_t length, uint16_t width,
                     const uint8_t pic[]);

#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40
#define BRRED 0XFC07
#define GRAY 0X8430
#define DARKBLUE 0X01CF
#define LIGHTBLUE 0X7D7C
#define GRAYBLUE 0X5458
#define LIGHTGREEN 0X841F
#define LGRAY 0XC618
#define LGRAYBLUE 0XA651
#define LBBLUE 0X2B12
#define PINK 0xFD18

#endif
