#ifndef LOG_H_CONTROLLERS
#define LOG_H_CONTROLLERS

#include "handlers/log.h"
#include "enums/operation.h"

#include "utils/user.h"
#include "utils/string.h"

bool log_operation(const char *file_name, Operations operation);

#endif // LOG_H_CONTROLLERS