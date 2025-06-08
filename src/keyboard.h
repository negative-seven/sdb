#pragma once

#include "declarations.h"
#include <cstddef>

enum tagButtonProps {};

enum tagKeyboardKey : int {};

typedef void (*InputCallbackFunction)(tagButtonProps const *, void *);

struct InputCallback {
    InputCallbackFunction a;
    void *b;
};

struct KeyState {
    int a;
    int b;
    int c;
};

struct TKeyboard {
    unsigned char *unknown_0x0;
    unsigned char *_padding_0x8;
    KeyState key_states[256];
    int locked;
    InputCallback input_callbacks[512];
    InputCallbackFunction any_key_callback_function;

    TEXT_ADDRESS_IGNORE_IN_DIFF(0x58bf10) TKeyboard();  // incomplete
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x58c000) ~TKeyboard(); // inlined
    TEXT_ADDRESS(0x58c020)
    void AddKeyCallback(tagKeyboardKey param_1, InputCallbackFunction param_2,
                        void *param_3);
    TEXT_ADDRESS(0x58c040)
    void AddAnyKeyCallback(void (*function)(tagButtonProps const *, void *));
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x58c040)
    bool Lock(); // `mov eax, 1` vs `mov al, 1` when returning bool
    TEXT_ADDRESS(0x58c070)
    void UnLock();
    TEXT_ADDRESS(0x58c070)
    int GetExclusiveState(tagKeyboardKey key) const;
    TEXT_ADDRESS(0x58c070)
    void BackupCallbacks(InputCallback **callbacks); // TODO
    TEXT_ADDRESS(0x58c2b0)
    void RestoreCallbacks(InputCallback **callbacks); // TODO
    TEXT_ADDRESS(0x58c520)
    void BackupKeyboardCallbacks(); // TODO
    TEXT_ADDRESS(0x58c5e0)
    void RestoreKeyboardCallbacks(); // TODO
};

TEXT_ADDRESS_IGNORE_IN_DIFF(0x570630)
void iptRegisterKeyboard(TKeyboard *keyboard) {
    // TODO
}

TEXT_ADDRESS_IGNORE_IN_DIFF(0x5706d0)
void iptUnRegisterKeyboard(TKeyboard *keyboard) { keyboard = nullptr; }

TEXT_ADDRESS_IGNORE_IN_DIFF(0x58c6e0)
tagKeyboardKey FormatStringToKeyboardKey(char const *string); // references libc

BSS_ADDRESS_IGNORE_IN_DIFF(0x822280) TKeyboard *Keyboard;
BSS_ADDRESS_IGNORE_IN_DIFF(0x820200) TKeyboard *keyboard;

BSS_ADDRESS_IGNORE_IN_DIFF(0x817fc0) char const *strKeyNames;
