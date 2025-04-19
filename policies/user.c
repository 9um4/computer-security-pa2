#include "policies/user.h"

bool can_read(SecurityLevels user_level, SecurityLevels file_level) {
    if (user_level == UNDEFINED || file_level == UNDEFINED) {
        return false; // Cannot access if either level is undefined
    }

    if (user_level >= file_level) {
        return true; // User can access the file
    } else {
        return false; // User cannot access the file
    }
}

bool can_write(SecurityLevels user_level, SecurityLevels file_level) {
    if (user_level == UNDEFINED || file_level == UNDEFINED) {
        return false; // Cannot access if either level is undefined
    }

    if (user_level <= file_level) {
        return true; // User can access the file
    } else {
        return false; // User cannot access the file
    }
}