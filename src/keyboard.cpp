#include "keyboard.h"
#include "error.h"
#include <cstring>

TKeyboard::TKeyboard() {
    for (int i = 0; i < 256; i++) {
        key_states[i].a = 0;
        key_states[i].b = 0;
        key_states[i].c = 0;
    }
    this->locked = 0;
    this->any_key_callback_function = 0;
    if (Keyboard != nullptr) {
        Error::ThrowFatalError(
            "A Keyboard has already been created, only support for 1 keyboard");
    }
    iptRegisterKeyboard(this);
    Keyboard = this;
}

TKeyboard::~TKeyboard() {
    iptUnRegisterKeyboard(this);
    Keyboard = nullptr;
}

void TKeyboard::AddKeyCallback(tagKeyboardKey param_1,
                               InputCallbackFunction param_2, void *param_3) {
    input_callbacks[param_1] = InputCallback{
        param_2,
        param_3,
    };
}

void TKeyboard::AddAnyKeyCallback(InputCallbackFunction function) {
    any_key_callback_function = function;
}

bool TKeyboard::Lock() {
    if (locked == 0) {
        locked = 1;
        return true;
    }
    return false;
}

void TKeyboard::UnLock() { locked = 0; }

int TKeyboard::GetExclusiveState(tagKeyboardKey key) const {
    if (locked != 0) {
        return 4;
    }
    return key_states[key].a;
}

tagKeyboardKey FormatStringToKeyboardKey(char const *string) {
    for (size_t index = 0; index < 0x90; index++) {
        char const *name = (&strKeyNames)[index];
        if (name != nullptr && strcmp(string, name) == 0) {
            return static_cast<tagKeyboardKey>(index);
        }
    };
    return static_cast<tagKeyboardKey>(0);
}
