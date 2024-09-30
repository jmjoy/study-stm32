#ifndef __LED_H
#define __LED_H

#include "sys.h"

#define LED PCout(13) // PC

/**
 * @brief Initializes the LED.
 */
void LED_Init(void);

#endif
