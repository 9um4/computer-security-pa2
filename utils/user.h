#ifndef USER_H_UTILS
#define USER_H_UTILS

#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "enums/security_level.h"
#include "macros/user.h"
#include "utils/file.h"

char *get_current_user_name();

SecurityLevels get_user_security_level(const char *username);
SecurityLevels get_current_user_security_level();

bool drop_privileges();

#endif // USER_H_UTILS