/*

接线图：

+---------------------+         +---------------------+
|     STM32F103       |         |      AT24C02        |
|                     |         |                     |
|        PB0 (SCL)    |-------->|        SCL          |
|        PB1 (SDA)    |-------->|        SDA          |
|        3.3V/5V      |-------->|        Vcc          |
|        GND          |-------->|        GND          |
|                     |         |        WP ---------> GND
|                     |         |        A0 ---------> GND
|                     |         |        A1 ---------> GND
+---------------------+         +---------------------+

上拉电阻：
+3.3V ---- [4.7kΩ] ---- SCL
+3.3V ---- [4.7kΩ] ---- SDA

*/
#include "at24c02.h"
#include "delay.h"
#include "i2c.h"
#include <stdint.h>
#include "lcd.h"

void AT24C02_Init(void)
{
    I2C_Init();
}

void AT24C02_Write(uint8_t addr, uint8_t data)
{
    I2C_Start();
    I2C_WriteByte(AT24C02_ADDR + I2C_WRITE);
    if (!I2C_ReadAck()) {
        LCD_ShowString(10, 30, "1", RED, BRRED, 24, 0);
    }
    I2C_WriteByte(addr);
    if (!I2C_ReadAck()) {
        LCD_ShowString(30, 30, "2", RED, BRRED, 24, 0);
    }
    I2C_WriteByte(data);
    if (!I2C_ReadAck()) {
        LCD_ShowString(50, 30, "3", RED, BRRED, 24, 0);
    }
    I2C_Stop();
    delay_ms(5); // Wait for write cycle
}

uint8_t AT24C02_Read(uint8_t addr)
{
    I2C_Start();
    I2C_WriteByte(AT24C02_ADDR + I2C_WRITE);
    if (!I2C_ReadAck()) {
        LCD_ShowString(70, 30, "4", RED, BRRED, 24, 0);
    }
    I2C_WriteByte(addr);
    if (!I2C_ReadAck()) {
        LCD_ShowString(90, 30, "5", RED, BRRED, 24, 0);
    }
    I2C_Start();
    I2C_WriteByte(AT24C02_ADDR + I2C_READ);
    if (!I2C_ReadAck()) {
        LCD_ShowString(110, 30, "6", RED, BRRED, 24, 0);
    }
    uint8_t data = I2C_ReadByte();
    I2C_WriteAck(false);
    I2C_Stop();
    return data;
}
