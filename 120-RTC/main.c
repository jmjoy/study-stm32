#include "delay.h"
#include "lcd.h"
#include "lcd_init.h"
#include "stm32f10x_conf.h"
#include <time.h>

void MY_RTC_Init() {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);
    RCC_LSEConfig(RCC_LSE_ON);
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET) {
    }
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    RCC_RTCCLKCmd(ENABLE);
    RTC_WaitForSynchro();
    RTC_WaitForLastTask();

    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5) {
        RTC_SetPrescaler(32767);
        RTC_WaitForLastTask();
        RTC_SetCounter(0);
        RTC_WaitForLastTask();
        BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
    }
}

int main(void) {
    delay_init();

    MY_RTC_Init();

    LCD_UseHardwareSPI();
    LCD_Init();
    LCD_Fill(0, 0, LCD_W, LCD_H, BRRED);

    LCD_ShowString(10, 0, "TS:", BLACK, BRRED, 24, 0);

    while (1) {
        uint32_t timestamp = RTC_GetCounter();

        LCD_ShowIntNum(50, 0, timestamp, 5, RED, BRRED, 24);

        struct tm *local_time = localtime(&timestamp);
        char datetime_str[100];
        strftime(datetime_str, 100, "%Y-%m-%d %H:%M:%S", local_time);

        LCD_ShowString(10, 50, datetime_str, BLACK, BRRED, 12, 0);
    }
}
