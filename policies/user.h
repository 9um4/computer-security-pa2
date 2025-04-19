#ifndef USER_H_POLICIES
#define USER_H_POLICIES

#include <stdio.h>
#include <stdbool.h>

#include "macros/user.h"
#include "enums/security_level.h"

bool can_read(SecurityLevels user_level, SecurityLevels file_level);
bool can_write(SecurityLevels user_level, SecurityLevels file_level);

#endif // USER_H_POLICIES