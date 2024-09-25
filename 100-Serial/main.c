#include "delay.h"
#include "lcd.h"
#include "lcd_init.h"
#include "serial.h"
#include "stm32f10x_gpio.h"
#include <stdio.h>

int main(void) {
    delay_init();

    LCD_Init();
    LCD_Fill(0, 0, LCD_W, LCD_H, BRRED);

    Serial_Init();

    while (1) {
    }
}
