#include "delay.h"
#include "ds18b20.h"
#include "lcd.h"
#include "lcd_init.h"
#include "stm32f10x_conf.h"
#include <stdint.h>

int main(void) {
    // LCD初始化
    delay_init();

    LCD_Init();
    LCD_Fill(0, 0, LCD_W, LCD_H, BRRED);

    LCD_ShowString(10, 0, "Temperature:", BLACK, BRRED, 24, 0);

    DS18B20_Init();

    DS18B20_ConvertT();
    delay_ms(50);

    while (1) {
        DS18B20_ConvertT();
        float temperature = DS18B20_ReadT();

        // 这个显示函数有缺陷，显示不了负数
        LCD_ShowFloatNum1(10, 30, temperature, 5, GREEN, BRRED, 24);
        delay_ms(1);
    }
}
