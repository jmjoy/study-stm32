#include "delay.h"
#include "lcd.h"
#include "lcd_init.h"
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "stm32f10x_gpio.h"
#include <time.h>
#include <stdio.h>

#define LAST_FLASH_ADDRESS 0x0800FC00

static void show_uint32_t(uint16_t x, uint16_t y, uint32_t num) {
    char str[16];
    sprintf(str, "0x%x", num);
    LCD_ShowString(x, y, str, GREEN, BRRED, 12, 0);
}

int main(void) {
    delay_init();

    LCD_Init();
    LCD_Fill(0, 0, LCD_W, LCD_H, BRRED);

    LCD_ShowString(10, 0, "ID0:", BLACK, BRRED, 12, 0);
    show_uint32_t(50, 0, *(__IO uint32_t *)0x1FFFF7EC);

    LCD_ShowString(10, 15, "ID1:", BLACK, BRRED, 12, 0);
    show_uint32_t(50, 15, *(__IO uint32_t *)0x1FFFF7EC);

    LCD_ShowString(10, 30, "ID2:", BLACK, BRRED, 12, 0);
    show_uint32_t(50, 30, *(__IO uint32_t *)0x1FFFF7F0);

    LCD_ShowString(10,45, "SIZE:", BLACK, BRRED, 12, 0);
    show_uint32_t(50, 45, *(__IO uint16_t *)0x1FFFF7E0);

    FLASH_Unlock();
    FLASH_ErasePage(LAST_FLASH_ADDRESS);
    FLASH_ProgramHalfWord(LAST_FLASH_ADDRESS, 0xA5A5);
    FLASH_Lock();

    LCD_ShowString(10, 60, "DATA:", BLACK, BRRED, 12, 0);
    show_uint32_t(50, 60, *(__IO uint16_t *)LAST_FLASH_ADDRESS);

    while (1) {
    }
}
