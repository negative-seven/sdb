#pragma once

#define SECTION(s) __attribute__((section(#s)))
#define TEXT_ADDRESS(a) SECTION(.text.##a)
#define TEXT_ADDRESS_IGNORE_IN_DIFF(a) SECTION(.text.##a##.ignore_in_diff)
