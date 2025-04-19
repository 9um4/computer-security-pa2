#ifndef LOG_H_HANDLERS
#define LOG_H_HANDLERS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>

#include "utils/string.h"


bool log_raw(char* file_name, char* log_message);

#endif // LOG_H_HANDLERS