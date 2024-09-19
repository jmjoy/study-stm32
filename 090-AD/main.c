#include "delay.h"
#include "lcd.h"
#include "lcd_init.h"
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "ad.h"
#include <stdint.h>

int main(void) {
    delay_init();

    LCD_Init();
    LCD_Fill(0, 0, LCD_W, LCD_H, BRRED);

    LCD_ShowString(10, 0, "ADC:", BLACK, BRRED, 24, 0);
    LCD_ShowString(10, 30, "Vt:", BLACK, BRRED, 24, 0);

    AD_Init();

    while (1) {
        uint16_t value = AD_GetValue();
        float voltage = (float) value / 4096 * 3.3;

        LCD_ShowIntNum(80, 0, value, 4, YELLOW, BRRED, 24);
        LCD_ShowFloatNum1(80, 30, voltage, 3, RED, BRRED, 24);

        delay_ms(100);
    }
}
