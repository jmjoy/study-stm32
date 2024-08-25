#include "stm32f10x_conf.h"
#include "sys.h"
#include "breath.h"
#include "btn.h"
#include "delay.h"
#include "ic.h"
#include "lcd.h"
#include "lcd_init.h"
#include "servo.h"

/**
 * @brief 控制舵机（LCD显示PWM频率和占空比，舵机角度）
 * 接线：
 * 舵机控制引脚---> PA3
 * 按钮---> PA1
 * PA6---> PA3 （IC）
 *
 * @return int
 */
int main(void) {
    // LCD初始化
    delay_init();

    LCD_Init();
    LCD_Fill(0, 0, LCD_W, LCD_H, BRRED);

    // btn
    btn_init();

    IC_init();

    servo_init();

    uint16_t angle = 90;

    // 屏幕内容显示
    LCD_ShowString(10, 0, "Freq:", BLACK, BRRED, 24, 0);
    LCD_ShowString(10, 30, "Duty:", BLACK, BRRED, 24, 0);
    LCD_ShowString(10, 60, "ANG:", BLACK, BRRED, 24, 0);

    while (1) {
        if (is_btn_down()) {
            angle += 45;
            if (angle > 180) {
                angle = 0;
            }
        }
        servo_set_angle(angle);

        LCD_ShowIntNum(80, 0, IC_GetFreq(), 5, RED, BRRED, 24);
        LCD_ShowIntNum(80, 30, IC_GetDuty(), 5, RED, BRRED, 24);
        LCD_ShowIntNum(80, 60, angle, 5, RED, BRRED, 24);
    }
}
