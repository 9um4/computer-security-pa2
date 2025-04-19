#include "handlers/log.h"

bool log_raw(char* file_name, char* log_message) {
    umask(0027);

    FILE *fp = fopen(file_name, "a");
    if (fp == NULL) {
        printf("Error opening log file\n");
        return false; // Error opening log file
    }

    fprintf(fp, "%s\n", log_message);
    fclose(fp);
    return true;
}