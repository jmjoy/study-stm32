#include "breath.h"

void Breathing_Init(uint16_t PSC, uint16_t ARR) {
    // 启用TIM2时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // 查看引脚图，可得TIM2_CH1对应的是PA0
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 需要配置复用推挽
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 使用内部时钟
    TIM_InternalClockConfig(TIM2);

    // 初始化定时器
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = ARR - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = PSC - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCStructInit(&TIM_OCInitStruct);
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM2, &TIM_OCInitStruct);

    // 启用TIM2
    TIM_Cmd(TIM2, ENABLE);
}

void Breathing_SetCCR1(uint16_t Compare1) {
	return TIM_SetCompare1(TIM2, Compare1);
}

void Breathing_SetARR(uint16_t ARR) {
	TIM_PrescalerConfig(TIM2, ARR, TIM_PSCReloadMode_Update);
}
