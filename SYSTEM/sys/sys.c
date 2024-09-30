#include "sys.h"

/**
 * @brief Configures the NVIC (Nested Vectored Interrupt Controller) priority
 * group.
 *
 * This function sets the priority group for the NVIC, which determines the
 * number of priority bits used for interrupt priority levels. The priority
 * group can be set to one of the following values:
 * - NVIC_PriorityGroup_0: 0 bits for preemption priority, 4 bits for
 * subpriority
 * - NVIC_PriorityGroup_1: 1 bit for preemption priority, 3 bits for subpriority
 * - NVIC_PriorityGroup_2: 2 bits for preemption priority, 2 bits for
 * subpriority
 * - NVIC_PriorityGroup_3: 3 bits for preemption priority, 1 bit for subpriority
 * - NVIC_PriorityGroup_4: 4 bits for preemption priority, 0 bits for
 * subpriority
 *
 * @note The NVIC priority group should be configured based on the specific
 * requirements of the application.
 */
void NVIC_Configuration(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

// SPL GPIO Extention for bit toggling
/**
 * @brief  Toggles selected data port bits.
 * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
 * @param  GPIO_Pin: specifies the port bits to be toggled.
 *   This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
 * @retval None
 */
void GPIO_ToggleBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    GPIOx->ODR ^= GPIO_Pin;
}

/**
 * @brief Performs a circular right shift on a 32-bit value.
 *
 * This function uses the ROR instruction to perform a circular right shift on
 * the given value by n bits.
 *
 * @param value The value to be rotated.
 * @param n The number of bits to rotate by.
 * @return The result of the circular right shift operation.
 */
uint32_t rotate_left(uint32_t value, uint32_t n) {
    uint32_t result;
    __asm__ volatile("ROR %0, %1, %2" // 使用ROR指令，将value循环右移(32-n)位
                     : "=r"(result) // 输出操作数，存储到result
                     : "r"(value), "r"(32 - n) // 输入操作数：value和(32-n)
    );
    return result;
}
