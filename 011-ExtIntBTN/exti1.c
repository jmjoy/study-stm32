#include "exti1.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

// 初始化外部中断EXTI0
void EXTI1_Init(void) {
    // 启用GPIOA的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

    // 配置GPIOA的PIN1为输入（浮空或上拉/下拉，根据需要）
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 连接GPIOA的PIN1到EXTI1线（这个函数实际上是AFIO的），看原理图可知，EXT_n必须对应PIN_n
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);

    // 配置EXTI1线
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_StructInit(&EXTI_InitStructure);
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    // 设置组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // 启用EXTI1中断在NVIC
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static Exti1Handler EXTI1_HANDLER;

void Set_Exti1_Handler(Exti1Handler handler) {
    EXTI1_HANDLER = handler;
}

// EXTI1的中断服务例程
void EXTI1_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line1) != RESET) {
        Exti1Trigger trigger =
            GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == SET ? Rising : Falling;
        EXTI1_HANDLER(trigger);

        // 清除EXTI线路1的挂起位
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}
