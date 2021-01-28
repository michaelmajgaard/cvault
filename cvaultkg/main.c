#include <crypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void print_help() {
    printf("usage:\n"
           "\tcvaultkg --size 256 --output <file>\n"
           "\tcvaultkg -s 256 -o <file>\n\n"
           "options:\n"
           "\t-o --output <file>\tPath to key file.\n"
           "\t-s --size {256 | 512}\tKey size in bits.\n");
}

int parse_mut_excl_arg(char *arg, int optc, char *opts[]) {
    for (int i = 0; i < optc; ++i) {
        if (!strcmp(arg, opts[i])) {
            return 1;
        }
    }
    return 0;
}

int parse_pos_args(char *argv[], int kfi, int si, char **kf, char **s) {
    return (!strcmp(argv[kfi], "-o") || !strcmp(argv[kfi], "--output")) &&
           (!strcmp(argv[si], "-s") || !strcmp(argv[si], "--size")) &&
           (*kf = argv[kfi + 1]) && (*s = argv[si + 1]);
}

int parse_args(int argc, char *argv[], char **kf, char **s) {
    if (argc == 5 && parse_pos_args(argv, 1, 3, kf, s) ||
        parse_pos_args(argv, 3, 1, kf, s)) {
        char *optv[3] = {"256", "512"};
        return parse_mut_excl_arg(*s, 2, optv);
    }
    return 0;
}

char *genkey(int l) {
    char *buffer = (char *)malloc((l + 1) * sizeof(char));
    for (int i = 0; i < l; ++i) {
        buffer[i] = 126 - rand() % 93;
    }
    buffer[l] = '\0';
    return buffer;
}

int main(int argc, char *argv[]) {
    char *kf, *si, *key;
    if (!parse_args(argc, argv, &kf, &si)) {
        print_help();
        return -1;
    }
    srand(time(0));
    key = genkey(32);
    printf("%s\n", key);
    free(key);
    return 0;
}
