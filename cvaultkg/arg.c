#include "arg.h"
#include <string.h>

int contains(char *arg, int optc, char *opts[]) {
    for (int i = 0; i < optc; ++i) {
        if (!strcmp(arg, opts[i])) {
            return 1;
        }
    }
    return 0;
}

int parse_pos_arg(int argc, char *argv[], char *short_name, char *long_name,
                  char **value) {
    for (int i = 0; i < argc - 1; ++i) {
        char *cur = argv[i];
        if (!strcmp(cur, short_name) || !strcmp(cur, long_name)) {
            *value = argv[i + 1];
            return 1;
        }
    }
    return 0;
}
