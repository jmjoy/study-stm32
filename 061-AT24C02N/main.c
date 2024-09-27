#include "at24c02.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_init.h"
#include "stm32f10x_conf.h"
#include <stdint.h>

/**
 * @brief 硬件I2C，每次Reset之后，NUM + 1
 *
 * @return int
 */
int main(void) {
    const uint8_t ADDR = 0x10;

    // LCD初始化
    delay_init();

    LCD_Init();
    LCD_Fill(0, 0, LCD_W, LCD_H, BRRED);
    LCD_ShowString(10, 0, "NUM:", BLACK, BRRED, 24, 0);

    AT24C02_Init();

    uint8_t num = AT24C02_Read(ADDR);

    num += 1;

    AT24C02_Write(ADDR, num);

    LCD_ShowIntNum(60, 0, (uint16_t)num, 5, RED, BRRED, 24);

    while (1) {
    }
}
