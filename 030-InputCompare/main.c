#include "RTE_Components.h"
#include "sys.h"
#include CMSIS_device_header
#include "delay.h"
#include "lcd.h"
#include "lcd_init.h"
#include "ic.h"
#include "breath.h"

/**
 * @brief 输入比较（测试频率和占用比）
 * 
 * @return int 
 */
int main(void) {
	delay_init();

	LCD_Init();
	LCD_Fill(0, 0, LCD_W, LCD_H, BRRED);

	Breathing_Init(720, 100);
	Breathing_SetCCR1(10);

	// 屏幕内容显示
	LCD_ShowString(10, 0, "Freq:", BLACK, BRRED, 24, 0);
	LCD_ShowString(10, 30, "Duty:", BLACK, BRRED, 24, 0);

	IC_init();

	uint16_t ccr1 = 10;
	uint16_t arr = 720;

	while (1)
	{
		Breathing_SetCCR1(ccr1);
		ccr1 += 1;
		if (ccr1 == 100) {
			ccr1 = 1;
		}

//		Breathing_SetARR(arr);
//		arr *= 2;
//		if (arr >= 720*20) {
//			arr = 720;
//		}

		LCD_ShowIntNum(80, 0, IC_GetFreq(), 5, RED, BRRED, 24);
		LCD_ShowIntNum(80, 30, IC_GetDuty(), 5, RED, BRRED, 24);

		delay_ms(100);
	}
}
