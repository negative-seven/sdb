#pragma once

#include "declarations.h"
#include <cstdarg>
#include <cstddef>

BSS_ADDRESS_IGNORE_IN_DIFF(0x824d00) extern char *strLargeString;

TEXT_ADDRESS(0x5b82d0)
size_t safe_wcslen(wchar_t const *string);

extern "C" {
TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bd190)
void DebugMsg(const char *format...); // incorrect function/constant addresses

TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bd190)
void Sprint(const char *format,
            char *buffer...); // references libc

TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bd300)
void SprintArgList(const char *format, char *buffer,
                   va_list arguments); // references libc

TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bd320)
void SprintW(
    wchar_t *param_9, wchar_t *buffer,
    const wchar_t *format...); // complex due to va_list, unsure if correct

TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bd430)
void SprintArgListW(
    wchar_t *format, wchar_t *buffer,
    va_list arguments); // complex due to va_list, unsure if correct

TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bd4d0)
float StringToFloat(char *string); // references libc

TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bd4d0)
int StringToInt(char *string); // references libc

TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bd4d0)
float StringToFloatW(wchar_t *string); // references libc

TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bd4d0)
int StringToIntW(wchar_t *string); // references libc
}
