#pragma once

#include "declarations.h"

struct Error {
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5b7370)
    static void ThrowFatalError(char const *message); // references libc
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5b7370)
    static void ThrowNonFatalError(char const *message); // references libc
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5b7370)
    static void ThrowFileNotFoundError(char const *message); // references libc
};
