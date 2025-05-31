#include "error.h"
#include <cstdio>
#include <cstdlib>

void Error::ThrowFatalError(char const *message) {
    fprintf(stderr, "\n\n\nFatal Error: %s\n\n", message);
    fflush(stderr);
    exit(1);
}

void Error::ThrowNonFatalError(char const *message) {
    fprintf(stderr, "ERROR: %s\n", message);
    fflush(stderr);
}

void Error::ThrowFileNotFoundError(char const *message) {
    printf("Could not find: %s\n", message);
    fflush(stdout);
    exit(1);
}
