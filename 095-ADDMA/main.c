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

    LCD_ShowString(10, 0, "AD0:", BLACK, BRRED, 24, 0);
    LCD_ShowString(10, 20, "AD1:", BLACK, BRRED, 24, 0);
    LCD_ShowString(10, 40, "AD2:", BLACK, BRRED, 24, 0);
    LCD_ShowString(10, 60, "AD3:", BLACK, BRRED, 24, 0);

    AD_Init();

    while (1) {
        LCD_ShowIntNum(60, 0, AD_VALUE[0], 4, BLUE, BRRED, 24);
        LCD_ShowIntNum(60, 20, AD_VALUE[1], 4, BLUE, BRRED, 24);
        LCD_ShowIntNum(60, 40, AD_VALUE[2], 4, BLUE, BRRED, 24);
        LCD_ShowIntNum(60, 60, AD_VALUE[3], 4, BLUE, BRRED, 24);

        delay_ms(100);
    }
}
