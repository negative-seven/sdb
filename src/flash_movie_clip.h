#pragma once

#include "declarations.h"

struct FlashMovieClip {
    void *vtable;
    unsigned char _padding_0x8[8];
    int unknown_0x10;
    unsigned char _padding_0x14[4];
    int unknown_0x18;
    int playing;
    int unknown_0x20;
    int unknown_0x24;
    int unknown_0x28;
    int unknown_0x2c;
    long long int unknown_0x30;

    TEXT_ADDRESS(0x574ed0) FlashMovieClip();
    TEXT_ADDRESS(0x574ed0) int IsPlaying();
    TEXT_ADDRESS(0x574ed0)
    int FindInstance(int param_1, int param_2, int *param_3, int param_4);
    TEXT_ADDRESS(0x5713a0) ~FlashMovieClip();
};
