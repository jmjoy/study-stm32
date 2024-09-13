#ifndef __MUSIC_H
#define __MUSIC_H

#include "stm32f10x_conf.h"
#include <stdint.h>

void Music_Init(void);
void Music_Suspend(void);
void Music_SetNote(uint16_t Hz, uint16_t dur);
void Music_Stop(void);

#define PLAY_MUSIC(MUSIC)                                                      \
    do {                                                                       \
        for (int i = 0; i < sizeof(MUSIC) / sizeof(uint16_t); i += 2) {        \
            if (MUSIC[i + 1] == 0) {                                           \
                Music_SetNote(MUSIC[i], 1);                                    \
            } else {                                                           \
                Music_SetNote(MUSIC[i], MUSIC[i + 1]);                         \
                Music_Suspend();                                               \
            }                                                                  \
        }                                                                      \
    } while (0)

#endif
