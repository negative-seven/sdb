#include "flash_timeline.h"

FlashTimeline::FlashTimeline() {
    asm("xor eax, eax");
    unknown_0x0 = 0;
    unknown_0x4 = 1;
    asm("mov [rdi + 0x8], eax");
    asm("mov [rdi + 0xc], eax");
    unknown_0x10 = 0;
    unknown_0x14 = 0;
    unknown_0x18 = 0;
}

FlashTimeline::~FlashTimeline() {}
