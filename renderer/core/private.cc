#include "api.h"
#include "private.h"

const char* get_file_extensions(const char* filename) {
    const char* from_dot = strrchr(filename, '.');
    return from_dot == NULL ? "" : from_dot + 1;
}