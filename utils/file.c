#pragma once

#include "utils/file.h"

bool read_all(const char *file_name) {
    FILE *fp = fopen(file_name, "r");

    if (fp == NULL) {
        printf("Error opening file: %s\n", file_name);
        return false; // Error opening file
    }

    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, fp) != -1) {
        printf("%s", line);
    }

    free(line);
    fclose(fp);
    return true;
}

ssize_t readline(char **lineptr, size_t *n, FILE *stream) {
    ssize_t result = getline(lineptr, n, stream);
    if (result != -1) {
        // 개행 문자 제거
        size_t len = strcspn(*lineptr, "\r\n");
        (*lineptr)[len] = '\0';
    }
    return result;
}

bool write_all(const char *file_name, const char *content) {
    FILE *fp = fopen(file_name, "w");

    if (fp == NULL) {
        printf("Error opening file: %s\n", file_name);
        return false; // Error opening file
    }

    fprintf(fp, "%s", content);
    fclose(fp);
    return true;
}