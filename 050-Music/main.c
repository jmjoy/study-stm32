#include "delay.h"
#include "music.h"
#include "stm32f10x_conf.h"
#include "sys.h"

const uint16_t NOTE_无音_0 = 0;

const uint16_t NOTE_低音1_Do = 262;
const uint16_t NOTE_低音1_Cis = 277;
const uint16_t NOTE_低音2_Re = 294;
const uint16_t NOTE_低音2_Dis = 311;
const uint16_t NOTE_低音3_Mi = 330;
const uint16_t NOTE_低音4_Fa = 349;
const uint16_t NOTE_低音4_Fis = 370;
const uint16_t NOTE_低音5_So = 392;
const uint16_t NOTE_低音5_Sis = 415;
const uint16_t NOTE_低音6_La = 440;
const uint16_t NOTE_低音6_Ais = 466;
const uint16_t NOTE_低音7_Si = 494;

const uint16_t NOTE_中音1_Do = 523;
const uint16_t NOTE_中音1_Cis = 554;
const uint16_t NOTE_中音2_Re = 587;
const uint16_t NOTE_中音2_Dis = 622;
const uint16_t NOTE_中音3_Mi = 659;
const uint16_t NOTE_中音4_Fa = 698;
const uint16_t NOTE_中音4_Fis = 740;
const uint16_t NOTE_中音5_So = 784;
const uint16_t NOTE_中音5_Sis = 831;
const uint16_t NOTE_中音6_La = 880;
const uint16_t NOTE_中音6_Ais = 932;
const uint16_t NOTE_中音7_Si = 988;

const uint16_t NOTE_高音1_Do = 1047;
const uint16_t NOTE_高音1_Cis = 1109;
const uint16_t NOTE_高音2_Re = 1175;
const uint16_t NOTE_高音2_Dis = 1245;
const uint16_t NOTE_高音3_Mi = 1319;
const uint16_t NOTE_高音4_Fa = 1397;
const uint16_t NOTE_高音4_Fis = 1480;
const uint16_t NOTE_高音5_So = 1568;
const uint16_t NOTE_高音5_Sis = 1661;
const uint16_t NOTE_高音6_La = 1760;
const uint16_t NOTE_高音6_Ais = 1865;
const uint16_t NOTE_高音7_Si = 1976;

const uint16_t NOTE_超高音1_Do = 2094;

uint16_t MUSIC_小星星[] = {
    NOTE_中音1_Do, 4,     NOTE_中音1_Do, 4,     NOTE_中音5_So, 4,
    NOTE_中音5_So, 4,     NOTE_中音6_La, 4,     NOTE_中音6_La, 4,
    NOTE_中音5_So, 4 + 4, NOTE_中音4_Fa, 4,     NOTE_中音4_Fa, 4,
    NOTE_中音3_Mi, 4,     NOTE_中音3_Mi, 4,     NOTE_中音2_Re, 4,
    NOTE_中音2_Re, 4,     NOTE_中音1_Do, 4 + 4, NOTE_中音5_So, 4,
    NOTE_中音5_So, 4,     NOTE_中音4_Fa, 4,     NOTE_中音4_Fa, 4,
    NOTE_中音3_Mi, 4,     NOTE_中音3_Mi, 4,     NOTE_中音2_Re, 4 + 4,
    NOTE_中音5_So, 4,     NOTE_中音5_So, 4,     NOTE_中音4_Fa, 4,
    NOTE_中音4_Fa, 4,     NOTE_中音3_Mi, 4,     NOTE_中音3_Mi, 4,
    NOTE_中音2_Re, 4 + 4, NOTE_中音1_Do, 4,     NOTE_中音1_Do, 4,
    NOTE_中音5_So, 4,     NOTE_中音5_So, 4,     NOTE_中音6_La, 4,
    NOTE_中音6_La, 4,     NOTE_中音5_So, 4 + 4, NOTE_中音4_Fa, 4,
    NOTE_中音4_Fa, 4,     NOTE_中音3_Mi, 4,     NOTE_中音3_Mi, 4,
    NOTE_中音2_Re, 4,     NOTE_中音2_Re, 4,     NOTE_中音1_Do, 4 + 4,
};

uint16_t MUSIC_天空之城[] = {
    NOTE_低音6_La,  2,
    NOTE_低音7_Si,  2,

    NOTE_中音1_Do,  4 + 2,
    NOTE_低音7_Si,  2,
    NOTE_中音1_Do,  4,
    NOTE_中音3_Mi,  4,

    NOTE_低音7_Si,  4 + 4 + 4,
    NOTE_低音3_Mi,  4,

    NOTE_低音6_La,  4 + 2,
    NOTE_低音5_So,  2,
    NOTE_低音6_La,  4,
    NOTE_中音1_Do,  4,

    NOTE_低音5_So,  4 + 4 + 4,
    NOTE_低音3_Mi,  4,

    NOTE_低音4_Fa,  4 + 2,
    NOTE_低音3_Mi,  2,
    NOTE_低音4_Fa,  2,
    NOTE_中音1_Do,  4 + 2,

    NOTE_低音3_Mi,  4 + 4 + 4,
    NOTE_中音1_Do,  4,

    NOTE_低音7_Si,  4 + 2,
    NOTE_低音4_Fis, 2,
    NOTE_低音4_Fis, 4,
    NOTE_低音7_Si,  4,

    NOTE_低音7_Si,  4 + 4 + 4,
    NOTE_低音6_La,  2,
    NOTE_低音7_Si,  2,

    NOTE_中音1_Do,  4 + 2,
    NOTE_低音7_Si,  2,
    NOTE_中音1_Do,  4,
    NOTE_中音3_Mi,  4,

    NOTE_低音7_Si,  4 + 4 + 4,
    NOTE_低音3_Mi,  2,
    NOTE_低音3_Mi,  2,

    NOTE_低音6_La,  4 + 2,
    NOTE_低音5_So,  2,
    NOTE_低音6_La,  4,
    NOTE_中音1_Do,  4,

    NOTE_低音5_So,  4 + 4 + 4,
    NOTE_低音3_Mi,  4,

    NOTE_低音4_Fa,  4,
    NOTE_中音1_Do,  2,
    NOTE_低音7_Si,  4 + 2,
    NOTE_中音1_Do,  4,

    NOTE_中音2_Re,  4,
    NOTE_中音3_Mi,  2,
    NOTE_中音1_Do,  2,
    NOTE_中音1_Do,  4 + 4,

    NOTE_中音1_Do,  2,
    NOTE_低音7_Si,  2,
    NOTE_低音6_La,  4,
    NOTE_低音7_Si,  4,
    NOTE_低音5_Sis, 4,

    NOTE_低音6_La,  4 + 4 + 4,
    NOTE_中音1_Do,  2,
    NOTE_中音2_Re,  2,

    NOTE_中音3_Mi,  4 + 2,
    NOTE_中音2_Re,  2,
    NOTE_中音3_Mi,  4,
    NOTE_中音5_So,  4,

    NOTE_中音2_Re,  4 + 4 + 4,
    NOTE_低音5_So,  4,

    NOTE_中音1_Do,  4 + 2,
    NOTE_低音7_Si,  2,
    NOTE_中音1_Do,  4,
    NOTE_中音2_Re,  2,
    NOTE_中音3_Mi,  2,

    NOTE_中音3_Mi,  4 + 4 + 4 + 4,

    NOTE_低音6_La,  2,
    NOTE_低音7_Si,  2,
    NOTE_中音1_Do,  4,
    NOTE_低音7_Si,  2,
    NOTE_中音1_Do,  2,
    NOTE_中音2_Re,  4,

    NOTE_中音1_Do,  4 + 2,
    NOTE_低音5_So,  2,
    NOTE_低音5_So,  4 + 4,

    NOTE_中音4_Fa,  4,
    NOTE_中音3_Mi,  4,
    NOTE_中音2_Re,  4,
    NOTE_中音1_Do,  4,

    NOTE_中音3_Mi,  4 + 4 + 4,
    NOTE_中音3_Mi,  4,

    NOTE_中音6_La,  4 + 2,
    NOTE_中音6_La,  2,
    NOTE_中音5_So,  4 + 2,
    NOTE_中音5_So,  2,

    NOTE_中音3_Mi,  2,
    NOTE_中音2_Re,  2,
    NOTE_中音1_Do,  4,
    NOTE_中音1_Do,  4 + 4,

    NOTE_中音2_Re,  4 + 2,
    NOTE_中音1_Do,  2,
    NOTE_中音2_Re,  4,
    NOTE_中音5_So,  4,

    NOTE_中音3_Mi,  4 + 4 + 4,
    NOTE_中音3_Mi,  4,

    NOTE_中音6_La,  4 + 2,
    NOTE_中音6_La,  2,
    NOTE_中音5_So,  4 + 2,
    NOTE_中音5_So,  2,

    NOTE_中音3_Mi,  2,
    NOTE_中音2_Re,  2,
    NOTE_中音1_Do,  4,
    NOTE_中音1_Do,  4 + 4,

    NOTE_中音2_Re,  4 + 2,
    NOTE_中音1_Do,  2,
    NOTE_中音2_Re,  4,
    NOTE_低音7_Si,  4,

    NOTE_低音6_La,  4 + 4 + 4,
    NOTE_无音_0,
};

uint16_t MUSIC_鸡你太美[] = {
    NOTE_无音_0,   2, NOTE_低音6_La, 1, NOTE_低音6_La, 1, NOTE_中音3_Mi, 2,
    NOTE_中音3_Mi, 2,

    NOTE_低音6_La, 4, NOTE_无音_0,   4, NOTE_无音_0,   4, NOTE_无音_0,   2,
    NOTE_低音6_La, 1, NOTE_低音6_La, 1,

    NOTE_低音6_La, 2, NOTE_无音_0,   2, NOTE_无音_0,   4, NOTE_无音_0,   2,
    NOTE_低音6_La, 1, NOTE_低音6_La, 1, NOTE_中音3_Mi, 2, NOTE_中音3_Mi, 2,

    NOTE_低音6_La, 4, NOTE_无音_0,   4, NOTE_无音_0,   4, NOTE_无音_0,   2,
    NOTE_低音6_La, 1, NOTE_低音6_La, 1,

    NOTE_低音6_La, 2, NOTE_无音_0,   2, NOTE_无音_0,   2, NOTE_低音6_La, 1,
    NOTE_低音6_La, 1, NOTE_低音6_La, 2, NOTE_低音6_La, 1, NOTE_低音6_La, 1,
    NOTE_中音3_Mi, 2, NOTE_中音3_Mi, 2,

    NOTE_低音6_La, 4, NOTE_无音_0,   4, NOTE_无音_0,   4, NOTE_无音_0,   2,
    NOTE_低音6_La, 1, NOTE_低音6_La, 1,

    NOTE_低音6_La, 2, NOTE_无音_0,   2, NOTE_无音_0,   4, NOTE_无音_0,   2,
    NOTE_低音6_La, 1, NOTE_低音6_La, 1, NOTE_中音3_Mi, 2, NOTE_中音3_Mi, 2,

    NOTE_低音6_La, 4, NOTE_无音_0,   4, NOTE_无音_0,   4, NOTE_无音_0,   2,
    NOTE_低音6_La, 1, NOTE_低音6_La, 1,

    NOTE_低音6_La, 2, NOTE_无音_0,   2, NOTE_无音_0,   4, NOTE_无音_0,   4,
    NOTE_无音_0,   4,
};

uint16_t MUSIC_大鱼[] = {
    NOTE_高音3_Mi,   2,         NOTE_高音2_Re, 2, NOTE_高音3_Mi, 2,
    NOTE_高音6_La,   2,         NOTE_高音3_Mi, 2, NOTE_高音2_Re, 2,
    NOTE_高音3_Mi,   2,         NOTE_高音7_Si, 2,

    NOTE_高音3_Mi,   2,         NOTE_高音2_Re, 2, NOTE_高音3_Mi, 2,
    NOTE_超高音1_Do, 2,         NOTE_高音7_Si, 4, NOTE_高音5_So, 4,

    NOTE_高音2_Re,   0,         NOTE_高音3_Mi, 2, NOTE_高音2_Re, 2,
    NOTE_高音3_Mi,   2,         NOTE_高音6_La, 2, NOTE_高音2_Re, 0,
    NOTE_高音3_Mi,   2,         NOTE_高音2_Re, 2, NOTE_高音3_Mi, 2,
    NOTE_高音7_Si,   2,

    NOTE_高音5_So,   4 + 4 + 4, NOTE_无音_0,   4,

    NOTE_高音3_Mi,   2,         NOTE_高音2_Re, 2, NOTE_高音3_Mi, 2,
    NOTE_高音6_La,   2,         NOTE_高音3_Mi, 2, NOTE_高音2_Re, 2,
    NOTE_高音3_Mi,   2,         NOTE_高音7_Si, 2,

    NOTE_高音3_Mi,   2,         NOTE_高音2_Re, 2, NOTE_高音3_Mi, 2,
    NOTE_超高音1_Do, 2,         NOTE_高音7_Si, 4, NOTE_高音5_So, 4,

    NOTE_高音2_Re,   2,         NOTE_高音3_Mi, 2, NOTE_中音6_La, 4,
    NOTE_高音2_Re,   2,         NOTE_高音3_Mi, 2, NOTE_中音6_La, 2,
    NOTE_中音5_So,   2,

    NOTE_中音6_La,   4 + 4 + 4, NOTE_无音_0,   4,
};

int main(void) {

    Music_Init();

    PLAY_MUSIC(MUSIC_大鱼);
    PLAY_MUSIC(MUSIC_鸡你太美);
    PLAY_MUSIC(MUSIC_天空之城);
    PLAY_MUSIC(MUSIC_小星星);

    Music_Stop();

    while (1) {
    }
}
