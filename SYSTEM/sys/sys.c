#include "sys.h"

void NVIC_Configuration(void)
{

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

}


//SPL GPIO Extention for bit toggling
/**
  * @brief  Toggles selected data port bits.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be toggled.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->ODR ^= GPIO_Pin;
}

uint32_t rotate_left(uint32_t value, uint32_t n) {
    uint32_t result;
    __asm__ volatile("ROR %0, %1, %2" // 使用ROR指令，将value循环右移(32-n)位
                     : "=r"(result) // 输出操作数，存储到result
                     : "r"(value), "r"(32 - n) // 输入操作数：value和(32-n)
    );
    return result;
}
