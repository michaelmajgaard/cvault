#include <crypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void print_help() {
    printf("usage:\n"
           "\tcvaultkg --size 256\n"
           "\tcvaultkg -s 256 \n\n"
           "options:\n"
           "\t-s --size {64 | 128 | 256 | 512}\tKey size in bits.\n");
}

int parse_mut_excl_arg(char *arg, int optc, char *opts[]) {
    for (int i = 0; i < optc; ++i) {
        if (!strcmp(arg, opts[i])) {
            return 1;
        }
    }
    return 0;
}

int parse_pos_args(char *argv[], char **s) {
    return (!strcmp(argv[1], "-s") || !strcmp(argv[1], "--size")) &&
           (*s = argv[2]);
}

int parse_args(int argc, char *argv[], char **s) {
    if (argc == 3 && parse_pos_args(argv, s)) {
        char *optv[4] = {"64", "128", "256", "512"};
        return parse_mut_excl_arg(*s, 4, optv);
    }
    return 0;
}

char *genkey(int bit_size) {
    int length = bit_size / 8;
    char *buffer = (char *)malloc((length + 1) * sizeof(char));
    for (int i = 0; i < length; ++i) {
        buffer[i] = 126 - rand() % 93;
    }
    buffer[length] = '\0';
    return buffer;
}

int main(int argc, char *argv[]) {
    char *s, *key;
    if (!parse_args(argc, argv, &s)) {
        print_help();
        return -1;
    }
    srand(time(0));
    key = genkey(atoi(s));
    printf("%s\n", key);
    free(key);
    return 0;
}
