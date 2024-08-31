#ifndef __MUSIC_H
#define __MUSIC_H

#include <stdint.h>
#include "stm32f10x_conf.h"

void Music_Init(void);
void Music_Suspend(void);
void Music_SetNote(uint16_t Hz, uint16_t dur);
void Music_Stop(void);

#endif
