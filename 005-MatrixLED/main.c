#include "delay.h"
#include "stm32f10x_conf.h"
#include "stm32f10x_gpio.h"
#include <stdint.h>

const uint16_t DI_PIN = GPIO_Pin_1;
const uint16_t CLK_PIN = GPIO_Pin_2;
const uint16_t LE_PIN = GPIO_Pin_3;

// 心形图案的字节数据，每个元素表示一列
uint8_t HEART_PATTERN[8] = {0xF6, 0xA9, 0xA9, 0x00, 0xEF, 0x14, 0x1A, 0xE1};

void MatrixLED_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = DI_PIN | CLK_PIN | LE_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_ResetBits(GPIOA, CLK_PIN);
    GPIO_ResetBits(GPIOA, LE_PIN);
}

void MatrixLED_WriteWord(uint16_t data) {
    for (int i = 0; i < 16; i += 1) {
        GPIO_WriteBit(GPIOA, DI_PIN, (data & 0x01));
        data >>= 1;
        GPIO_SetBits(GPIOA, CLK_PIN);
        GPIO_ResetBits(GPIOA, CLK_PIN);
    }
    GPIO_SetBits(GPIOA, LE_PIN);
    GPIO_ResetBits(GPIOA, LE_PIN);
}

int main(void) {
    delay_init();

    MatrixLED_Init();

    while (1) {
        uint8_t col = 0b11111110;
        for (uint8_t i = 0; i < 8; i += 1) {
            uint8_t row = HEART_PATTERN[i];
            MatrixLED_WriteWord(((uint16_t)row) << 8 | ((uint16_t)col));
            col = (col << 1) | ((col & 0x80) >> 7);
        }
    }
}
