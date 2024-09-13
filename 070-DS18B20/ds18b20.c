/*

接线图：

VCC ---+--- 上拉电阻（4.7kΩ） --- 数据线（DQ）--- PA6
       |
      DS18B20
       |
      GND

*/

#include "ds18b20.h"
#include "delay.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include <stdint.h>

static GPIO_InitTypeDef GPIO_InitStructure;

static inline void DS18B20_InputMode(void) {
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static inline void DS18B20_OutputMode(void) {
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static inline void DS18B20_SetDQ(void) {
    GPIO_SetBits(GPIOA, GPIO_Pin_6);
}

static inline void DS18B20_ResetDQ(void) {
    GPIO_ResetBits(GPIOA, GPIO_Pin_6);
}

static inline uint8_t DS18B20_ReadDQ(void) {
    return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}

void DS18B20_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
}

bool DS18B20_Reset(void) {
    bool ack = false;

    DS18B20_OutputMode();

    // 拉低总线至少480ms
    DS18B20_SetDQ();
    DS18B20_ResetDQ();
    delay_us(500);

    // 释放总线
    DS18B20_SetDQ();
    delay_us(50);

    DS18B20_InputMode();

    // 读取响应
    delay_us(40);
    if (DS18B20_ReadDQ() == RESET) {
        ack = true;
    }

    // 之后DS18B20会释放总线
    delay_us(460);

    return ack;
}

void DS18B20_WriteByte(uint8_t data) {
    DS18B20_OutputMode();

    for (int i = 0; i < 8; i += 1) {
        DS18B20_ResetDQ();

        delay_us(2);

        if (data & (0x01 << i)) {
            DS18B20_SetDQ();
        } else {
            DS18B20_ResetDQ();
        }

        // 延迟60ms到120ms之间，等待DS18B20读取数据
        delay_us(76);

        // 释放总线
        DS18B20_SetDQ();
        delay_us(2);
    }
}

uint8_t DS18B20_ReadByte(void) {
    uint8_t data = 0;

    for (int i = 0; i < 8; i += 1) {
        DS18B20_OutputMode();

        DS18B20_ResetDQ();

        delay_us(2);

        // 释放总线
        DS18B20_SetDQ();
        delay_us(2);

        DS18B20_InputMode();

        data |= DS18B20_ReadDQ() << i;

        // 延迟60ms到120ms之间，等待DS18B20读取数据
        delay_us(76);

        // 读时序结束，DS18B20释放总线
    }

    return data;
}

void DS18B20_ConvertT(void) {
    DS18B20_Reset();
    DS18B20_WriteByte(0xcc);
    DS18B20_WriteByte(0x44);
}

float DS18B20_ReadT(void) {
    DS18B20_Reset();
    DS18B20_WriteByte(0xcc);
    DS18B20_WriteByte(0xbe);

    uint8_t lsb = DS18B20_ReadByte();
    uint8_t msb = DS18B20_ReadByte();

    int16_t tmp = (msb << 8) | lsb;
    float temp = tmp * 0.0625; // 相当于除以16（右移四位）

    return temp;
}
