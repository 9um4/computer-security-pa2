#ifndef FILE_H_POLICIES
#define FILE_H_POLICIES

#include "enums/security_level.h"
#include <string.h>

typedef struct {
    char *filename;
    SecurityLevels level;
} FilePolicy;

extern FilePolicy files[];

SecurityLevels get_file_level();

#endif // FILE_H_POLICIES