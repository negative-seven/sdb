#include "format.h"
#include "string.h"
#include <cstring>
#include <string>

extern "C" {

void FormatRegFilePath(unsigned long long int param_9, std::string &param_10) {
    unsigned int uVar1;
    char *puVar2;
    char local_1018[4096];

    puVar2 = local_1018;
    Sprint(reg_file_path_format, local_1018, GUserDataPath, (int)param_9);
    param_10.assign((char *)local_1018);
}

std::string *FormatResourcePath(char *a, std::string *b) {
    switch (SystemCaps[1]) {
    case 4:
    case 8:
        *b = "pc_low";
        break;
    case 2:
        *b = "pc_med";
        break;
    default:
        *b = "pc";
        break;
    }
    b->append(a);
    return b;
}
}
