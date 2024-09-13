#include "key.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

static void tim2_init() {
    // 启用TIM2时钟，TIM2在总线1上
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    // 内部时钟
    TIM_InternalClockConfig(TIM2);

    // 初始化定时器，希望20ms产生一次中断，这个是按钮抖动的时间
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 200 - 1;
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

static void gpioa_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin =
        GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void Key_Init(void) {
    gpioa_Init();
    tim2_init();
}

static bool IS_KEY_DOWN[KEY_COUNT] = {false, false, false, false};

const uint16_t GPIO_PINS[KEY_COUNT] = {GPIO_Pin_1, GPIO_Pin_2, GPIO_Pin_3,
                                       GPIO_Pin_4};

/**
 * 固定的TIM2中断函数名
 */
void TIM2_IRQHandler(void) {
    static uint8_t KEY_STATUS[KEY_COUNT] = {1, 1, 1, 1};
    static uint8_t LAST_KEY_STATUS[KEY_COUNT] = {1, 1, 1, 1};

    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        // 清除TIM2更新中断标志
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

        for (int i = 0; i < KEY_COUNT; i += 1) {
            // 这里是gpio->btn->GND这样接法，所以高电平表示的是没按下
            KEY_STATUS[i] = GPIO_ReadInputDataBit(GPIOA, GPIO_PINS[i]);

            // 20ms取样一次，如果上次是低电平，这次是高电平，则表示松开按钮了
            if (KEY_STATUS[i] && !LAST_KEY_STATUS[i]) {
                IS_KEY_DOWN[i] = true;
            }

            LAST_KEY_STATUS[i] = KEY_STATUS[i];
        }
    }
}

bool Is_Key_Down(int key) {
    bool is = IS_KEY_DOWN[key];
    IS_KEY_DOWN[key] = false;
    return is;
}
