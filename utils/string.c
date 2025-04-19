#include "utils/string.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat(const char *a, const char *b) {
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    char *result = malloc(len_a + len_b + 1); // +1 for the null terminator
    if (result == NULL) {
        return NULL; // Memory allocation failed
    }
    strcpy(result, a);
    strcat(result, b);
    return result;
}

char *strjoin(int count, ...) {
    va_list args;
    va_start(args, count);

    // 총 길이 계산
    size_t total_len = 0;
    for (int i = 0; i < count; i++) {
        const char *s = va_arg(args, const char *);
        total_len += strlen(s);
    }
    va_end(args);

    // 메모리 할당 (+1 for '\0')
    char *result = malloc(total_len + 1);
    if (!result) return NULL;
    result[0] = '\0';  // 빈 문자열로 초기화

    // 문자열 하나씩 붙이기
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        const char *s = va_arg(args, const char *);
        strcat(result, s);
    }
    va_end(args);

    return result;
}

char *str_join_array(const char **array, const char *delimiter, size_t start, size_t end) {
    if (array == NULL || delimiter == NULL) return NULL;

    size_t total_len = 0;
    size_t delimiter_len = strlen(delimiter);

    // 총 길이 계산
    for (size_t i = start; i < end; i++) {
        total_len += strlen(array[i]);
        if (i > start) total_len += delimiter_len;
    }

    // 메모리 할당 (+1 for '\0')
    
    char *result = malloc(total_len + 1);
    if (!result) return NULL;
    result[0] = '\0';  // 빈 문자열로 초기화

    // 문자열 하나씩 붙이기
    for (size_t i = start; array[i] != NULL; i++) {
        if (i > start) strcat(result, delimiter);
        strcat(result, array[i]);
    }

    return result;
}

char **split(const char *str, char delimiter) {
    if (str == NULL) return NULL;

    size_t count = 1;

    const char *tmp = str;

    while (*tmp) {
        if (*tmp == delimiter) {
            count++;
        }
        tmp++;
    }

    char **result = malloc((count + 1) * sizeof(char *));

    size_t idx = 0;
    const char *start = str;
    const char *end;

    while ((end = strchr(start, delimiter))) {
        size_t len = end - start;
        result[idx] = strndup(start, len);  // 부분 문자열 복사
        idx++;
        start = end + 1;
    }

    // 마지막 토큰
    result[idx++] = strdup(start);
    result[idx] = NULL;

    return result;
}