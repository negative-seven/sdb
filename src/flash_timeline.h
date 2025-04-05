#pragma once

#include "declarations.h"

struct FlashTimeline {
    int unknown_0x0;
    int unknown_0x4;
    int unknown_0x8;
    int unknown_0xc;
    int unknown_0x10;
    int unknown_0x14;
    long long int unknown_0x18;

    TEXT_ADDRESS(0x574ad0) FlashTimeline();
    TEXT_ADDRESS(0x574ad0) ~FlashTimeline();
};
