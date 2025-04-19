#ifndef FILE_H_HANDLERS
#define FILE_H_HANDLERS

#include "policies/file.h"
#include "utils/file.h"
#include "utils/user.h"
#include "controllers/log.h"

#include <stdio.h>
#include <stdbool.h>

bool file_read(const char *file_name);
bool file_write(const char *file_name, const char *data);

#endif