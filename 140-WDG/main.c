#include "delay.h"
#include "lcd.h"
#include "lcd_init.h"
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "stm32f10x_gpio.h"
#include <time.h>

static void Key_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

int main(void) {
    delay_init();

    Key_Init();

    LCD_Init();
    LCD_Fill(0, 0, LCD_W, LCD_H, BRRED);

    if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET) {
        LCD_ShowString(10, 0, "IWDG RST", BLACK, BRRED, 24, 0);
    } else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) == SET) {
        LCD_ShowString(10, 0, "PIN RST", BLACK, BRRED, 24, 0);
    } else if (RCC_GetFlagStatus(RCC_FLAG_PORRST) == SET) {
        LCD_ShowString(10, 0, "POR/PDR RST", BLACK, BRRED, 24, 0);
    } else if (RCC_GetFlagStatus(RCC_FLAG_SFTRST) == SET) {
        LCD_ShowString(10, 0, "SW RST", BLACK, BRRED, 24, 0);
    } else if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET) {
        LCD_ShowString(10, 0, "WWDG RST", BLACK, BRRED, 24, 0);
    } else if (RCC_GetFlagStatus(RCC_FLAG_LPWRRST) == SET) {
        LCD_ShowString(10, 0, "LPWR RST", BLACK, BRRED, 24, 0);
    } else {
        LCD_ShowString(10, 0, "UNKNOWN RST", BLACK, BRRED, 24, 0);
    }
    RCC_ClearFlag();

    // 设置独立看门狗超时时间为5s
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(IWDG_Prescaler_64);
    IWDG_SetReload(2889);
    IWDG_ReloadCounter();
    IWDG_Enable();

    while (1) {
        while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == Bit_RESET) {
        }
        
        delay_ms(5000);
        IWDG_ReloadCounter();
    }
}
