#include "controllers/log.h"

bool log_operation(const char *file_name, Operations operation) {
    char *log_file_name = concat(get_current_user_name(), ".log");
    if (log_file_name == NULL) {
        printf("Error creating log file name\n");
        return false; // Error opening log file
    }

    char *log_message = strjoin(3, operations_raw[operation], " ", file_name);

    if (log_message == NULL) {
        free(log_message);
        free(log_file_name);
        printf("Error creating log message\n");
        return false; // Error creating log message
    }

    if (log_raw(log_file_name, log_message)) {
        free(log_message);
        free(log_file_name);
        return true;
    };
    free(log_message);
    free(log_file_name);
    printf("Error logging operation\n");
    return false;
}