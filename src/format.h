#pragma once

#include "declarations.h"
#include <string>

RODATA_ADDRESS_IGNORE_IN_DIFF(0x5de628)
char reg_file_path_format[] = "%sreg%i.dat";

RODATA_ADDRESS_IGNORE_IN_DIFF(0x5c0332)
char user_data_path[] = "/SuperMeatBoy/UserData/";

RODATA_ADDRESS(0x818488)
char (*GUserDataPath)[24] = &user_data_path;

RODATA_ADDRESS_IGNORE_IN_DIFF(0x823eb0) int SystemCaps[2];

extern "C" {
TEXT_ADDRESS_IGNORE_IN_DIFF(0x5b7590)
void FormatRegFilePath(unsigned long long int param_9,
                       std::string &param_10); // references libstdc++

TEXT_ADDRESS_IGNORE_IN_DIFF(0x5b7590)
std::string *FormatResourcePath(char *a,
                                std::string *b); // references libstdc++
}
