#pragma once

#include "declarations.h"
#include <pthread.h>

struct CriticalSection {
    pthread_mutex_t mutex;

    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5b7190)
    CriticalSection(); // references libpthread
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5b7190)
    ~CriticalSection(); // references libpthread
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5b7190)
    int Lock(int blocking); // references libpthread
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5b7190)
    void Unlock(); // references libpthread
};
