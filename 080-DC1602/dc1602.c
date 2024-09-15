/*

接线图

STM32F103        LCD1602
----------       --------
GND              ->  VSS (1)
5V               ->  VCC (2)
GND              ->  V0 (通过电位器)
PB0              ->  RS (4)
PB1              ->  RW (5)
PB10             ->  E (6)
PA7~PA0          ->  D7~D0 (11)
5V 限流电阻(220Ω) -> A (15)
GND              ->  K (16)

为了省事，不判断忙信号，直接延时

*/
#include "dc1602.h"
#include "delay.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

/**
 * @brief 数据/命令选择端
 *
 * @param BitVal
 */
static inline void DC1602_WriteRS(BitAction BitVal) {
    GPIO_WriteBit(GPIOB, GPIO_Pin_0, BitVal);
}

/**
 * @brief 读/写选择端
 *
 * @param BitVal
 */
static inline void DC1602_WriteRW(BitAction BitVal) {
    GPIO_WriteBit(GPIOB, GPIO_Pin_1, BitVal);
}

/**
 * @brief 使能信号
 *
 * @param BitVal
 */
static inline void DC1602_WriteE(BitAction BitVal) {
    GPIO_WriteBit(GPIOB, GPIO_Pin_10, BitVal);
}

/**
 * @brief D0~D7
 *
 * @param d
 */
static inline void DC1602_WriteD(uint8_t d) {
    GPIO_Write(GPIOA, d);
}

static void DC1602_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_Write(GPIOA, 0);

    delay_ms(5);
}

static void DC1602_WriteCmd(uint8_t cmd) {
    DC1602_WriteRS(Bit_RESET);
    DC1602_WriteRW(Bit_RESET);
    DC1602_WriteD(cmd);
    DC1602_WriteE(Bit_SET);
    delay_ms(5);
    DC1602_WriteE(Bit_RESET);
    delay_ms(5);
}

static void DC1602_WriteData(uint8_t data) {
    DC1602_WriteRS(Bit_SET);
    DC1602_WriteRW(Bit_RESET);
    DC1602_WriteD(data);
    DC1602_WriteE(Bit_SET);
    delay_ms(5);
    DC1602_WriteE(Bit_RESET);
    delay_ms(15);
}

void DC1602_Init(void) {
    DC1602_GPIO_Init();

    DC1602_WriteCmd(0b00111000); // 显示模式

    DC1602_WriteCmd(0b00001111); // 打开显示、光标、闪烁

    DC1602_WriteCmd(0b00000110); // 读写光标、指针移动
}

void DC1602_WriteString(uint8_t row, uint8_t col, char *str) {
    DC1602_WriteCmd(0x80 + row * 0x40 + col); // 设置地址

    // 写数据
    for (char *p = str; *p != '\0'; p++) {
        DC1602_WriteData(*p);
    }
}

void DC1602_MoveScreen(MoveDirection direction) {
    if (direction == MoveLeft) {
        DC1602_WriteCmd(0x18); // 移动屏幕
    } else {
        DC1602_WriteCmd(0x1C); // 移动屏幕
    }
}
