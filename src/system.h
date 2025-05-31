#pragma once

#include "declarations.h"

extern "C" {
TEXT_ADDRESS_IGNORE_IN_DIFF(0x5b82f0)
int System_GetTimeInMS(); // references libc
TEXT_ADDRESS(0x5b82f0) void System_Startup();
TEXT_ADDRESS(0x5b82f0) void System_ShutDown();
TEXT_ADDRESS(0x5b82f0) void System_Update();
TEXT_ADDRESS(0x5b82f0) int System_IsTrialMode();
TEXT_ADDRESS(0x5b82f0) long long int System_IsUserOnline();
TEXT_ADDRESS(0x5b82f0) long long int System_IsOnline();
TEXT_ADDRESS(0x5b86a0) long long int System_GetRegion();
TEXT_ADDRESS(0x5b86a0) long long int System_ISOSUIShowing();
TEXT_ADDRESS(0x5b86a0) void System_CheckTrialMask();
TEXT_ADDRESS(0x5b86a0) long long int System_WasUserOnline();
TEXT_ADDRESS(0x5b86a0) long long int System_LastUserSignedIn();
}
