/**
 * @file delay.c
 * @brief This file contains the implementation of delay functions.
 */

#include "delay.h"
#include "sys.h"

#if SYSTEM_SUPPORT_UCOS
#include "includes.h"
#endif

static uint8_t fac_us = 0;  /**< Microsecond delay factor */
static uint16_t fac_ms = 0; /**< Millisecond delay factor */

#ifdef OS_CRITICAL_METHOD
/**
 * @brief SysTick interrupt handler for operating system tick.
 */
void SysTick_Handler(void) {
    OSIntEnter();
    OSTimeTick();
    OSIntExit();
}
#endif

/**
 * @brief Initialize the delay module.
 */
void delay_init() {
#ifdef OS_CRITICAL_METHOD
    u32 reload;
#endif
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    fac_us = SystemCoreClock / 8000000;

#ifdef OS_CRITICAL_METHOD
    reload = SystemCoreClock / 8000000;
    reload *= 1000000 / OS_TICKS_PER_SEC;

    fac_ms = 1000 / OS_TICKS_PER_SEC;
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
    SysTick->LOAD = reload;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
#else
    fac_ms = (u16)fac_us * 1000;
#endif
}

#ifdef OS_CRITICAL_METHOD
/**
 * @brief Delay in microseconds.
 * @param nus The number of microseconds to delay.
 */
void delay_us(u32 nus) {
    u32 ticks;
    u32 told, tnow, tcnt = 0;
    u32 reload = SysTick->LOAD;
    ticks = nus * fac_us;
    tcnt = 0;
    told = SysTick->VAL;
    while (1) {
        tnow = SysTick->VAL;
        if (tnow != told) {
            if (tnow < told)
                tcnt += told - tnow;
            else
                tcnt += reload - tnow + told;
            told = tnow;
            if (tcnt >= ticks)
                break;
        }
    };
}

/**
 * @brief Delay in milliseconds.
 * @param nms The number of milliseconds to delay.
 */
void delay_ms(u16 nms) {
    if (OSRunning == TRUE) {
        if (nms >= fac_ms) {
            OSTimeDly(nms / fac_ms);
        }
        nms %= fac_ms;
    }
    delay_us((u32)(nms * 1000));
}
#else

/**
 * @brief Delay in microseconds.
 * @param nus The number of microseconds to delay.
 */
void delay_us(u32 nus) {
    u32 temp;
    SysTick->LOAD = nus * fac_us;
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    do {
        temp = SysTick->CTRL;
    } while (temp & 0x01 && !(temp & (1 << 16)));
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0X00;
}

/**
 * @brief Delay in milliseconds.
 * @param nms The number of milliseconds to delay.
 */
void delay_ms(u16 nms) {
    u32 temp;
    SysTick->LOAD = (u32)nms * fac_ms;
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    do {
        temp = SysTick->CTRL;
    } while (temp & 0x01 && !(temp & (1 << 16)));
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0X00;
}
#endif
