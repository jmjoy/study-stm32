/*

接线图：

+---------------------+         +---------------------+
|     STM32F103       |         |      AT24C02        |
|                     |         |                     |
|        PB10 (SCL)   |-------->|        SCL          |
|        PB11 (SDA)   |-------->|        SDA          |
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
#include "lcd.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"
#include <stdint.h>

static void AT24C02_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT) {
    uint16_t timeout = 0;
    while (I2C_CheckEvent(I2Cx, I2C_EVENT) == ERROR) {
        timeout += 1;
        if (timeout >= 10000) {
            LCD_ShowString(10, 50, "I2C TIMEOUT!", RED, BRRED, 24, 0);
            break;
        }
    }
}

void AT24C02_Init(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    I2C_InitTypeDef I2C_InitStructure;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 100000;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;
    I2C_Init(I2C2, &I2C_InitStructure);
}

void AT24C02_Write(uint8_t addr, uint8_t data) {
    I2C_GenerateSTART(I2C2, ENABLE);
    AT24C02_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(I2C2, AT24C02_ADDR, I2C_Direction_Transmitter);
    AT24C02_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

    I2C_SendData(I2C2, addr);
    AT24C02_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING);

    I2C_SendData(I2C2, data);
    AT24C02_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);

    I2C_GenerateSTOP(I2C2, ENABLE);

    // 等待写完成，也可以用I2C检查AT24C02是否响应从机应答来判断
    delay_ms(5); // Wait for write cycle
}

uint8_t AT24C02_Read(uint8_t addr) {
    I2C_GenerateSTART(I2C2, ENABLE);
    AT24C02_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(I2C2, AT24C02_ADDR, I2C_Direction_Transmitter);
    AT24C02_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

    I2C_SendData(I2C2, addr);
    AT24C02_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);

    I2C_GenerateSTART(I2C2, ENABLE);
    AT24C02_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(I2C2, AT24C02_ADDR, I2C_Direction_Receiver);
    AT24C02_WaitEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);

    I2C_AcknowledgeConfig(I2C2, DISABLE);
    I2C_GenerateSTOP(I2C2, ENABLE);

    AT24C02_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED);
    uint8_t data = I2C_ReceiveData(I2C2);

    // 重新使能 ACK，为下一次接收做准备
    I2C_AcknowledgeConfig(I2C1, ENABLE);

    return data;
}
