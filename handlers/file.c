#include "handlers/file.h"

bool file_read(const char *file_name) {
    SecurityLevels user_level = get_current_user_security_level();
    SecurityLevels file_level = get_file_level(file_name);
    
    if (can_read(user_level, file_level)) {
        bool result = read_all(file_name);
        drop_privileges();
        log_operation(file_name, READ);
        return result;
    } else {
        drop_privileges();
        log_operation(file_name, READ);
        return false; // Access denied
    }
}

bool file_write(const char *file_name, const char *data) {
    SecurityLevels user_level = get_current_user_security_level();
    SecurityLevels file_level = get_file_level(file_name);

    if (can_write(user_level, file_level)) {
        FILE *fp = fopen(file_name, "a");
        if (fp == NULL) {
            return false; // Error opening file
        }
        fprintf(fp, "%s\n", data);
        fclose(fp);
        drop_privileges();
        log_operation(file_name, WRITE);
        return true;
    } else {
        drop_privileges();
        log_operation(file_name, WRITE);
        return false; // Access denied
    }
}