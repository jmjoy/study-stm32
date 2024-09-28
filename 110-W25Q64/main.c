#include "W25Q64.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const uint32_t ADDR = 0x10000000;

static uint8_t DATA[8];

static void LCD_ShowDATA(char tag, uint16_t y) {
    char buf[100];
    sprintf(buf, "%02X %02X %02X %02X %02X %02X %02X %02X", DATA[0], DATA[1],
            DATA[2], DATA[3], DATA[4], DATA[5], DATA[6], DATA[7]);
    LCD_ShowChar(5, y, tag, BLACK, BRRED, 12, 0);
    LCD_ShowString(15, y, buf, BLUE, BRRED, 12, 0);
}

int main(void) {
    delay_init();

    LCD_Init();
    LCD_Fill(0, 0, LCD_W, LCD_H, BRRED);

    W25Q64_Init();

    JEDEC jedec;
    W25Q64_ReadJEDEC(&jedec);

    LCD_ShowString(10, 0, "V.ID:", BLACK, BRRED, 16, 0);
    LCD_ShowString(10, 18, "D.ID:", BLACK, BRRED, 16, 0);

    LCD_ShowIntNum(60, 0, jedec.vendor_id, 3, GREEN, BRRED, 16);
    LCD_ShowIntNum(60, 18, jedec.device_id, 5, GREEN, BRRED, 16);

    W25Q64_Read(ADDR, DATA, 8);
    LCD_ShowDATA('R', 40);

    for (int i = 0; i < 8; i += 1) {
        DATA[i] += 1;
    }

    LCD_ShowDATA('W', 60);

    W25Q64_EarseSector(ADDR);
    W25Q64_PageProgram(ADDR, DATA, 8);

    while (1) {
    }
}
