#include "declarations.h"
#include <cstddef>
#include <sys/time.h>

#include "system.h"

BSS_ADDRESS_IGNORE_IN_DIFF(0x824040) int bTrial;

extern "C" {
int System_GetTimeInMS() {
    timeval time;
    gettimeofday(&time, NULL);
    return time.tv_usec / 1000LLU + time.tv_sec * 1000;
}

void System_Startup() {}

void System_ShutDown() {}

void System_Update() {}

int System_IsTrialMode() { return bTrial; }

long long int System_IsUserOnline() { return 1; }

long long int System_IsOnline() { return 1; }

long long int System_GetRegion() { return 0; }

long long int System_ISOSUIShowing() { return 0; }

void System_CheckTrialMask() {}

long long int System_WasUserOnline() { return 0; }

long long int System_LastUserSignedIn() { return 0; }
}
