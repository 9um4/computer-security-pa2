#ifndef FILE_H_UTILS
#define FILE_H_UTILS

#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>

bool read_all(const char *file_name);
ssize_t readline(char **lineptr, size_t *n, FILE *stream);

#endif // FILE_H_UTILS