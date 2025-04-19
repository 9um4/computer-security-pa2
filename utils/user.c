#include "utils/user.h"
#include <inttypes.h> // for PRIxPTR


char *get_current_user_name() {
    uid_t uid = getuid();
    struct passwd* usr_info = getpwuid(uid);
    if (usr_info == NULL) {
        return NULL;
    }

    return usr_info->pw_name;
}

SecurityLevels get_user_security_level(const char *username) {
    FILE *fp = fopen(USER_SECURITY_POLICY_FILE, "r");

    if (fp == NULL) {
        return UNDEFINED; // Error opening policy file
    }

    char *line = NULL;
    size_t len = 0;

    while (readline(&line, &len, fp) != -1) {
        char **tokens = split(line, ':');

        SecurityLevels level = NOT_INITIALIZED;
        if (tokens == NULL) {
            level = UNDEFINED; // Error splitting line
        }
        else if (strcmp(tokens[0], username) == 0) {
            
            if (tokens[1] == NULL) {
                level = UNDEFINED; // Error: no security level found
            }
            else if (strcmp(tokens[1], "UNCLASSIFIED") == 0) {
                level = UNCLASSIFIED;
            }
            else if (strcmp(tokens[1], "CONFIDENTIAL") == 0) {
                level = CONFIDENTIAL;
            }
            else if (strcmp(tokens[1], "SECRET") == 0) {
                level = SECRET;
            }
            else if (strcmp(tokens[1], "TOP_SECRET") == 0) {
                level = TOP_SECRET;
            }
            else {
                level = UNDEFINED; // Error: unknown security level
            }
        }

        free(line);
        for (int i = 0; tokens[i]; i++) {
            free(tokens[i]);
        }
        free(tokens);

        if (level != NOT_INITIALIZED) {
            fclose(fp);
            return level;
        }
    }

    fclose(fp);
    return UNDEFINED; // User not found in policy file
}

SecurityLevels get_current_user_security_level() {
    char *username = get_current_user_name();
    if (username == NULL) {
        return UNDEFINED; // Error getting username
    }

    return get_user_security_level(username);
}

bool drop_privileges() {
    uid_t uid = getuid();
    gid_t gid = getgid();

    if (setresuid(uid, uid, uid) == -1) {
        return false; // Error dropping privileges
    }

    if (setresgid(gid, gid, gid) == -1) {
        return false; // Error dropping privileges
    }

    return true;
}