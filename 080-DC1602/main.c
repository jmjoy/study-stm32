#include "dc1602.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_init.h"
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include <stdint.h>

int main(void) {
    delay_init();

    LCD_Init();
    LCD_Fill(0, 0, LCD_W, LCD_H, BRRED);

    DC1602_Init();

    DC1602_WriteString(0, 0, "Hello World! Where are you from?");
    DC1602_WriteString(1, 3, "TEST!");

    while (1) {
        DC1602_MoveScreen(MoveLeft);
        delay_ms(500);
    }
}
