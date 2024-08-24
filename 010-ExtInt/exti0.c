#include "exti0.h"

// 初始化外部中断EXTI0
void EXTI0_Init(void) {
    // 启用GPIOA的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // 配置GPIOA的PIN0为输入（浮空或上拉/下拉，根据需要）
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 连接GPIOA的PIN0到EXTI0线（这个函数实际上是AFIO的），看原理图可知，EXT_n必须对应PIN_n
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

    // 配置EXTI0线
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_StructInit(&EXTI_InitStructure);
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger =
        EXTI_Trigger_Rising; // 或者EXTI_Trigger_Falling,
                             // EXTI_Trigger_Rising_Falling
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    // 设置组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // 启用EXTI0中断在NVIC
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =
        0x0F; // 可以根据需要调整
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static Exti0Handler EXTI0_HANDLER;

void Set_Exti0_Handler(Exti0Handler handler) {
	EXTI0_HANDLER = handler;
}

// EXTI0的中断服务例程
void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		// 清除EXTI线路0的挂起位
		EXTI_ClearITPendingBit(EXTI_Line0);

		EXTI0_HANDLER();
	}
}
