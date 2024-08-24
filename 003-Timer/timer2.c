#include "timer2.h"

void TIM2_Init(bool is_external) {
    // 启用TIM2时钟，TIM2在总线1上
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    if (!is_external) {
        // 内部时钟
        TIM_InternalClockConfig(TIM2);
    } else {
        // 外部时钟
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x00);
    }

    // 初始化定时器
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 10000 - 1; // 假设系统时钟为72MHz，预分频器为7199，则产生1秒的中断
    TIM_TimeBaseStructure.TIM_Prescaler = 7200 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_ClearFlag(TIM2, TIM_IT_Update);

    // 启用TIM2中断
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    // 启用TIM2
    TIM_Cmd(TIM2, ENABLE);

    // 启用TIM2中断在NVIC
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static TimHandler TIM2_HANDLER;

void Set_TIM2_Handler(TimHandler handler) {
	TIM2_HANDLER = handler;
}

void TIM2_IRQHandler(void) {
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        // 清除TIM2更新中断标志
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

        TIM2_HANDLER();
    }
}

uint16_t Get_Timer_Count(void) {
    return TIM_GetCounter(TIM2);
}
