#include "flash_movie_clip.h"

FlashMovieClip::FlashMovieClip() {
    asm("xor eax, eax");
    vtable = (void *)0x5dbb90;
    unknown_0x18 = 0;
    playing = 1;
    asm("mov [rdi + 0x20], eax");
    asm("mov [rdi + 0x24], eax");
    unknown_0x28 = 0;
    unknown_0x2c = 0;
    unknown_0x30 = 0;
    unknown_0x10 = 1;
    return;
}

int FlashMovieClip::IsPlaying() { return this->playing; }

FlashMovieClip::~FlashMovieClip() { this->vtable = (void *)0x5dbc90; }
