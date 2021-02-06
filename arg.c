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

int parse_opt(int argc, char *argv[], char *short_name, char *long_name) {
    for (int i = 1; i < argc; ++i) {
        char *c = argv[i];
        if (!strcmp(c, short_name) || !strcmp(c, long_name)) {
            return 1;
        }
    }
    return 0;
}

int parse_optv(int argc, char *argv[], char *short_name, char *long_name,
               char **value) {
    for (int i = 1; i < argc - 1; ++i) {
        char *c = argv[i];
        if (!strcmp(c, short_name) || !strcmp(c, long_name)) {
            *value = argv[i + 1];
            return 1;
        }
    }
    return 0;
}
