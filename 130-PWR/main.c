#include "delay.h"
#include "lcd.h"
#include "lcd_init.h"
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include <time.h>

int main(void) {
    delay_init();

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    PWR_WakeUpPinCmd(ENABLE);

    LCD_Init();
    LCD_Fill(0, 0, LCD_W, LCD_H, BRRED);

    LCD_ShowString(10, 0, "Timeout:", BLACK, BRRED, 24, 0);

    while (1) {
        for (int8_t i = 10; i > 0; i -= 1) {
            LCD_ShowIntNum(120, 0, i, 2, RED, BRRED, 24);
            delay_ms(1000);
        }

        // 模拟关闭耗电器件
        LCD_Fill(0, 0, LCD_W, LCD_H, BLACK);

        PWR_EnterSTANDBYMode();
    }
}
