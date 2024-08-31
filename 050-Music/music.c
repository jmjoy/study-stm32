#include "music.h"
#include "delay.h"
#include "stm32f10x.h"

void Music_Init(void) {
    delay_init();

    // 查看引脚图，可得TIM2_CH1对应的是PA0
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 需要配置复用推挽
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 启用TIM2时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // 使用内部时钟
    TIM_InternalClockConfig(TIM2);

    // 初始化定时器
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 100 - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 720 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCStructInit(&TIM_OCInitStruct);
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_Pulse = 0;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OC1Init(TIM2, &TIM_OCInitStruct);

    TIM_SetCompare1(TIM2, 0);

    // 启用TIM2
    TIM_Cmd(TIM2, ENABLE);
}

void Music_Suspend(void) {
    TIM_SetCompare1(TIM2, 0);
    delay_ms(10);
}

void Music_SetNote(uint16_t Hz, uint16_t dur) {
    if (Hz > 0) {
        uint32_t arr = ((uint32_t)720000) / ((uint32_t)Hz);
        TIM_PrescalerConfig(TIM2, arr, TIM_PSCReloadMode_Update);
        TIM_SetCompare1(TIM2, 50);
    }
    delay_ms(100 * dur);
}

void Music_Stop(void) {
    TIM_SetCompare1(TIM2, 0);
}
