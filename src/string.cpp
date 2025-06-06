#include "string.h"
#include <alloca.h>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cwchar>

size_t safe_wcslen(wchar_t const *string) {
    const wchar_t *string_end = string;
    wchar_t character;
    do {
        character = *string_end;
        string_end++;
    } while (character != L'\0');
    return string_end - string - 1;
}

void DebugMsg(const char *format...) {
    va_list arguments;
    va_start(arguments, format);

    vfprintf(stderr, format, arguments);
    fputc('\n', stderr);
    fflush(stderr);

    va_end(arguments);
}

void Sprint(char *buffer, const char *format...) {
    va_list arguments;
    va_start(arguments, format);
    SprintArgList(format, buffer, arguments);
    va_end(arguments);
}

void SprintArgList(const char *format, char *buffer, // NOLINT
                   va_list arguments) {
    if (buffer == nullptr) {
        buffer = reinterpret_cast<char *>(0x824d00);
    }
    // TODO
    // vsprintf(buffer, format, arguments);
}

void SprintW(wchar_t *param_9, wchar_t *buffer, const wchar_t *format...) {
    va_list arguments;
    va_start(arguments, format);

    long long int length = safe_wcslen(param_9);
    const wchar_t *pwVar2 = format;
    wchar_t *pwVar4;
    while (true) {
        pwVar4 = const_cast<wchar_t *>(pwVar2);
        wchar_t wVar1 = *param_9;
        if (wVar1 == L'\0') {
            break;
        }
        param_9 = param_9 + 1;
        *pwVar4 = wVar1;
        pwVar2 = pwVar4 + 1;
        if ((wVar1 == L'%') && (*param_9 == L's')) {
            pwVar4[1] = L'l';
            pwVar2 = pwVar4 + 2;
        }
    }
    if (buffer == nullptr) {
        buffer = reinterpret_cast<wchar_t *>(0x824cf0);
    }
    *pwVar4 = L'\0';
    // *(undefined8 *)((long)&auStack_f0 + lVar3) = 0x5bd425;
    vswprintf(buffer, 0xffffff, format, arguments);

    va_end(arguments);
}

void SprintArgListW(wchar_t *format, wchar_t *buffer, va_list arguments) {
    wchar_t format_previous;
    wchar_t *format_copy;
    wchar_t *format_copy_previous;

    size_t lVar3 = safe_wcslen(format);
    format_copy = (wchar_t *)alloca((lVar3 + 1) *
                                    sizeof(*format_copy)); // likely incorrect
    while (true) {
        format_copy_previous = format_copy;
        format_previous = *format;
        if (format_previous == L'\0') {
            break;
        }
        *format_copy = format_previous;
        format_copy++;
        format++;
        if ((format_previous == L'%') && (*format == L's')) {
            *format_copy = L'l';
            format_copy++;
        }
    }
    if (buffer == (wchar_t *)0x0) {
        buffer = reinterpret_cast<wchar_t *>(0x824cf0);
    }
    *format_copy_previous = L'\0';
    vswprintf(buffer, 0xffffff, (wchar_t *)0, arguments);
}

float StringToFloat(char *string) { return strtod(string, nullptr); }

int StringToInt(char *string) { return strtol(string, nullptr, 10); }

float StringToFloatW(wchar_t *string) { return wcstof(string, nullptr); }

int StringToIntW(wchar_t *string) { return wcstol(string, nullptr, 10); }
