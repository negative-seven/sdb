#include "auto_lock_section.h"
#include "critical_section.h"

AutoLockSection::AutoLockSection(CriticalSection *critical_section) {
    this->critical_section = critical_section;
    critical_section->Lock(1);
}

AutoLockSection::~AutoLockSection() { critical_section->Unlock(); }
