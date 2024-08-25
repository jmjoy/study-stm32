#include "stm32f10x_conf.h"
#include "main.h"
#include "delay.h"

int main(void) {
    delay_init();

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = SER_PIN | SCK_PIN | RCK_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 1代表亮，0代表不亮
    uint8_t led_num = 0b11100000;

    while (1) {
        uint8_t num = led_num;

        GPIO_ResetBits(GPIOA, RCK_PIN);
        for (int i = 0; i < 8; i += 1) {
            GPIO_ResetBits(GPIOA, SCK_PIN);
            // 我的8颗LED是共阳极接VCC的，所以这里要取反
            GPIO_WriteBit(GPIOA, SER_PIN, !(num & 0x01));
            num >>= 1;
            GPIO_SetBits(GPIOA, SCK_PIN);
        }
        GPIO_SetBits(GPIOA, RCK_PIN);

        // ARM32好像是没有循环左移的指令吧
        led_num = (led_num << 1) | (led_num >> 7);

        delay_ms(100);
    }
}
