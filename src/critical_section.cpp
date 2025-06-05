#include "critical_section.h"
#include <pthread.h>

CriticalSection::CriticalSection() {
    pthread_mutexattr_t attributes;
    pthread_mutexattr_init(&attributes);
    pthread_mutexattr_settype(&attributes, 1);
    pthread_mutex_init(&mutex, &attributes);
    pthread_mutexattr_destroy(&attributes);
}

CriticalSection::~CriticalSection() { pthread_mutex_destroy(&mutex); }

int CriticalSection::Lock(int blocking) {
    if (blocking == 1) {
        pthread_mutex_lock(&mutex);
        return 1;
    }
    return pthread_mutex_trylock(&mutex) == 0;
}

void CriticalSection::Unlock() { pthread_mutex_unlock(&mutex); }
