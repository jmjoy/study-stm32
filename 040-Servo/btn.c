#include "btn.h"
#include <stdbool.h>

void btn_init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

bool is_btn_down(void) {
    bool is = false;
    // 按键获取使用中断判断更好吧
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == RESET) {
        delay_ms(20);
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == RESET) {
            while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == RESET) {
            }
            delay_ms(20);
            is = true;
        }
    }
    return is;
}
