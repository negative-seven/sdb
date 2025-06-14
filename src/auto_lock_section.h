#pragma once

#include "critical_section.h"
#include "declarations.h"

struct AutoLockSection {
    CriticalSection *critical_section;

    TEXT_ADDRESS(0x5b59b0) AutoLockSection(CriticalSection *critical_section);
    TEXT_ADDRESS(0x5b59b0) ~AutoLockSection();
};
