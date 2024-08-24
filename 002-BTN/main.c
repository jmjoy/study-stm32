#include "RTE_Components.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "sys.h"
#include CMSIS_device_header
#include "delay.h"

void LED_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void BTN_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t is_key_down(void) {
    uint8_t is = 0;

    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0) {
        delay_ms(20);
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0) {
            while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0) {
            }
            delay_ms(20);
            is = 1;
        }
    }

    return is;
}

int main(void) {
    delay_init();
    LED_Init();
    BTN_Init();

    while (1) {
        if (is_key_down()) {
            GPIO_ToggleBits(GPIOC, GPIO_Pin_13);
        }
    }
}
