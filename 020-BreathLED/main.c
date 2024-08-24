#include "RTE_Components.h"
#include "sys.h"
#include CMSIS_device_header
#include "delay.h"
#include "lcd.h"
#include "lcd_init.h"
#include "breath.h"

/**
 * @brief 呼吸灯
 * 
 * @return int 
 */
int main(void) {
	delay_init();

	Breathing_Init(720, 100);

	uint16_t i = 0;

	while (1) {
		for (i = 0; i < 100; i += 1) {
			Breathing_SetCCR1(i);
			delay_ms(10);
		}
		for (i = 0; i < 100; i += 1) {
			Breathing_SetCCR1(100 - i);
			delay_ms(10);
		}
	}
}
