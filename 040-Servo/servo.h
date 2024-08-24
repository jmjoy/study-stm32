/*
 * servo.h
 *
 *  Created on: Aug 19, 2024
 *      Author: jmjoy
 */

#ifndef SERVO_H_
#define SERVO_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

void servo_init(void);

void servo_set_angle(uint32_t angle);

#endif /* SERVO_H_ */
