#include "at24c02.h"
#include "delay.h"
#include "key.h"
#include "lcd.h"
#include "lcd_init.h"
#include "stm32f10x_conf.h"
#include <stdint.h>

int main(void) {
    const uint8_t ADDR = 0x10;

    uint8_t num = 0;

    // LCD初始化
    delay_init();

    LCD_Init();
    LCD_Fill(0, 0, LCD_W, LCD_H, BRRED);
    LCD_ShowString(10, 0, "NUM:", BLACK, BRRED, 24, 0);

    AT24C02_Init();

    Key_Init();

    while (1) {
        LCD_ShowIntNum(60, 0, (uint16_t)num, 5, RED, BRRED, 24);

        if (Is_Key_Down(0)) {
            num += 1;
        }
        if (Is_Key_Down(1)) {
            num -= 1;
        }
        if (Is_Key_Down(2)) {
            num = AT24C02_Read(ADDR);
        }
        if (Is_Key_Down(3)) {
            AT24C02_Write(ADDR, num);
        }
    }
}
