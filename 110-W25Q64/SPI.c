#include "SPI.h"
#include "delay.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include <stdint.h>

void MY_SPI_Init(void) {
#if USE_SORTWARE_SPI
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_SetBits(GPIOA, MY_SPI_NSS);
    GPIO_ResetBits(GPIOA, MY_SPI_SCK);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = MY_SPI_NSS | MY_SPI_SCK | MY_SPI_MOSI;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = MY_SPI_MISO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#else
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = MY_SPI_SCK | MY_SPI_MOSI;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = MY_SPI_NSS;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = MY_SPI_MISO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    SPI_InitTypeDef SPI_InitStructure = {
        .SPI_Direction = SPI_Direction_2Lines_FullDuplex,
        .SPI_Mode = SPI_Mode_Master,
        .SPI_DataSize = SPI_DataSize_8b,
        .SPI_CPOL = SPI_CPOL_Low,
        .SPI_CPHA = SPI_CPHA_1Edge,
        .SPI_NSS = SPI_NSS_Soft,
        .SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2,
        .SPI_FirstBit = SPI_FirstBit_MSB,
        .SPI_CRCPolynomial = 7,
    };
    SPI_Init(SPI1, &SPI_InitStructure);
    SPI_Cmd(SPI1, ENABLE);
#endif
}

void MY_SPI_START(void) {
    GPIO_ResetBits(GPIOA, MY_SPI_NSS);
}

void MY_SPI_STOP(void) {
    GPIO_SetBits(GPIOA, MY_SPI_NSS);
}

uint8_t MY_SPI_SWAP(uint8_t data) {
#if USE_SORTWARE_SPI
    for (int i = 0; i < 8; i += 1) {
        GPIO_WriteBit(GPIOA, MY_SPI_MOSI, (data & 0x80) ? Bit_SET : Bit_RESET);
        data <<= 1;
        GPIO_SetBits(GPIOA, MY_SPI_SCK);
        data |= GPIO_ReadInputDataBit(GPIOA, MY_SPI_MISO);
        GPIO_ResetBits(GPIOA, MY_SPI_SCK);
    }
    return data;
#else
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) {
    }
    SPI_I2S_SendData(SPI1, data);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) {
    }
    return SPI_I2S_ReceiveData(SPI1);
#endif
}
