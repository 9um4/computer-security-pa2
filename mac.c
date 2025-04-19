#include <stdio.h>
#include <string.h>
#include "policies/file.h"
#include "policies/user.h"
#include "utils/string.h"

#include "handlers/file.h"

int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("[Mac] Error: Not enough arguments\n");
        printf("Usage: %s <read|write> <filename>\n", argv[0]);
    }
    else if (strcmp(argv[1], "read") == 0){
        if (!file_read(argv[2])) {
            printf("ACCESS DENIED\n", argv[2]);
        }
    }
    else if (strcmp(argv[1], "write") == 0){
        if (!file_write(argv[2], str_join_array(argv, " ", 3, argc))) {
            printf("ACCESS DENIED\n", argv[2]);
        }
    }
    else {
        printf("[Mac] Error: Invalid operation\n");
        printf("Usage: %s <read|write> <filename>\n", argv[0]);
    }

    return 0;

}