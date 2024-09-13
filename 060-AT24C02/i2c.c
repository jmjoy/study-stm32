#include "i2c.h"
#include "delay.h"
#include "stm32f10x_gpio.h"

static inline void I2C_SDA_EnableRead(void) {
    static GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Pin = I2C_SDA;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_GPIO, &GPIO_InitStruct);
}

static inline void I2C_SDA_EnableWrite(void) {
    static GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStruct.GPIO_Pin = I2C_SDA;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_GPIO, &GPIO_InitStruct);
}

void I2C_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStruct.GPIO_Pin = I2C_SCL | I2C_SDA;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_GPIO, &GPIO_InitStruct);

    GPIO_SetBits(I2C_GPIO, I2C_SCL | I2C_SDA);
}

void I2C_Start(void) {
    I2C_SDA_EnableWrite();

    GPIO_SetBits(I2C_GPIO, I2C_SCL);
    GPIO_SetBits(I2C_GPIO, I2C_SDA);
    delay_us(5);

    GPIO_ResetBits(I2C_GPIO, I2C_SDA);
    delay_us(5);

    GPIO_ResetBits(I2C_GPIO, I2C_SCL);
    delay_us(5);
}

void I2C_Stop(void) {
    I2C_SDA_EnableWrite();

    GPIO_ResetBits(I2C_GPIO, I2C_SDA);
    GPIO_SetBits(I2C_GPIO, I2C_SCL);
    delay_us(5);

    GPIO_SetBits(I2C_GPIO, I2C_SDA);
    delay_us(5);
}

bool I2C_ReadAck(void) {
    I2C_SDA_EnableRead();
    delay_us(5);

    GPIO_SetBits(I2C_GPIO, I2C_SCL);
    delay_us(5);

    bool ack = !((bool)GPIO_ReadInputDataBit(I2C_GPIO, I2C_SDA));

    GPIO_ResetBits(I2C_GPIO, I2C_SCL);
    delay_us(5);

    I2C_SDA_EnableWrite();

    return ack;
}

void I2C_WriteAck(bool ack) {
    I2C_SDA_EnableWrite();

    if (ack) {
        GPIO_ResetBits(I2C_GPIO, I2C_SDA);
    } else {
        GPIO_SetBits(I2C_GPIO, I2C_SDA);
    }
    delay_us(5);

    GPIO_SetBits(I2C_GPIO, I2C_SCL);
    delay_us(5);

    GPIO_ResetBits(I2C_GPIO, I2C_SCL);
    delay_us(5);

    GPIO_SetBits(I2C_GPIO, I2C_SDA);
    I2C_SDA_EnableWrite();
    delay_us(5);
}

void I2C_WriteByte(uint8_t data) {
    I2C_SDA_EnableWrite();

    for (uint8_t i = 0; i < 8; i += 1) {
        if (data & (0x80 >> i)) {
            GPIO_SetBits(I2C_GPIO, I2C_SDA);
        } else {
            GPIO_ResetBits(I2C_GPIO, I2C_SDA);
        }

        GPIO_SetBits(I2C_GPIO, I2C_SCL);
        delay_us(5);

        GPIO_ResetBits(I2C_GPIO, I2C_SCL);
        delay_us(5);
    }
}

uint8_t I2C_ReadByte(void) {
    GPIO_SetBits(I2C_GPIO, I2C_SDA);

    I2C_SDA_EnableRead();

    uint8_t data = 0;

    for (uint8_t i = 0; i < 8; i += 1) {
        GPIO_SetBits(I2C_GPIO, I2C_SCL);
        delay_us(5);

        if (GPIO_ReadInputDataBit(I2C_GPIO, I2C_SDA)) {
            data |= (0x80 >> i);
        }

        GPIO_ResetBits(I2C_GPIO, I2C_SCL);
        delay_us(5);
    }

    return data;
}
