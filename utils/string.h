#ifndef StRING_H_UTILS
#define StRING_H_UTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

char *concat(const char *a, const char *b);
char *strjoin(int count, ...);
char **split(const char *str, char delimiter);

char *str_join_array(const char **array, const char *delimiter, size_t start, size_t end);


#endif // StRING_H_UTILS