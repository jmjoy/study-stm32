#include "RTE_Components.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "sys.h"
#include CMSIS_device_header
#include "delay.h"
#include "lcd_init.h"
#include "lcd.h"
#include "timer2.h"

static uint16_t NUM = 0;

void handler(void) {
    NUM += 1;
}

int main(void) {
    delay_init();

    LCD_Init(); // LCD初始化
    LCD_Fill(0, 0, LCD_W, LCD_H, BRRED);

    delay_ms(300);

    Set_TIM2_Handler(handler);
    TIM2_Init(false);

    // 屏幕内容显示
    LCD_ShowString(10, 0, "NUM:", BLACK, BRRED, 24, 0);
    LCD_ShowString(10, 30, "CNT:", BLACK, BRRED, 24, 0);

    while (1) {
        LCD_ShowIntNum(60, 0, NUM, 5, RED, BRRED, 24);
        LCD_ShowIntNum(60, 30, Get_Timer_Count(), 5, RED, BRRED, 24);
    }
}
