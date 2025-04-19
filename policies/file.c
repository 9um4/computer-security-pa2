#include "policies/file.h"

FilePolicy files[] = {
    {"unclassified.data", UNCLASSIFIED},
    {"confidential.data", CONFIDENTIAL},
    {"secret.data", SECRET},
    {"top_secret.data", TOP_SECRET}
};

SecurityLevels get_file_level(const char *file_name) {
    for (size_t i = 0; i < sizeof(files) / sizeof(FilePolicy); i++) {
        if (strcmp(files[i].filename, file_name) == 0) {
            return files[i].level;
        }
    }

    return UNCLASSIFIED; // Default level if file not found
}