#include "delay.h"
#include "exti1.h"
#include "lcd.h"
#include "lcd_init.h"

static uint16_t FALLING_COUNT = 0;
static uint16_t RISING_COUNT = 0;

void handler(Exti1Trigger trigger) {
    if (trigger == Falling) {
        FALLING_COUNT++;
    } else {
        RISING_COUNT++;
    }
}

/**
 * @brief 外部中断，按钮作为中断源
 *
 * @return int
 */
int main(void) {
    delay_init();

    LCD_Init(); // LCD初始化
    LCD_Fill(0, 0, LCD_W, LCD_H, BRRED);

    Set_Exti1_Handler(handler);

    EXTI1_Init();

    // 屏幕内容显示
    LCD_ShowString(10, 0, "F cnt:", BLACK, BRRED, 24, 0);
    LCD_ShowString(10, 30, "R cnt:", BLACK, BRRED, 24, 0);

    while (1) {
        LCD_ShowIntNum(80, 0, FALLING_COUNT, 5, GREEN, BRRED, 24);
        LCD_ShowIntNum(80, 30, RISING_COUNT, 5, BLUE, BRRED, 24);
    }
}
