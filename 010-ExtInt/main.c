#include "RTE_Components.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "sys.h"
#include <stdint.h>
#include CMSIS_device_header
#include "delay.h"
#include "lcd_init.h"
#include "lcd.h"
#include "exti0.h"

static uint16_t NUM = 0;

void handler(void) {
    NUM += 1;
}

/**
 * 我没有信号发射器，就用GPIO来模拟吧
 */
void mock_signal_init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void mock_signal_send(void) {
    GPIO_SetBits(GPIOA, GPIO_Pin_6);
    delay_ms(5);
    GPIO_ResetBits(GPIOA, GPIO_Pin_6);
    delay_ms(5);
}

/**
 * @brief 外部中断
 * 
 * @return int 
 */
int main(void) {
    delay_init();

    LCD_Init(); // LCD初始化
    LCD_Fill(0, 0, LCD_W, LCD_H, BRRED);

    mock_signal_init();

    Set_Exti0_Handler(handler);

    EXTI0_Init();

    // 屏幕内容显示
    LCD_ShowString(10, 0, "NUM:", BLACK, BRRED, 24, 0);

    while (1) {
        mock_signal_send();
        LCD_ShowIntNum(60, 0, NUM, 5, RED, BRRED, 24);
    }
}
