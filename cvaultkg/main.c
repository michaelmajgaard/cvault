#include <crypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void print_help() {
    printf("usage:\n"
           "\tcvaultkg --output <file>\n"
           "\tcvaultkg -o <file>\n\n"
           "options:\n"
           "\t-o --output <file>\tPath to key file.\n");
}

int parse_pos_args(char *argv[], char **kf) {

    return !strcmp(argv[1], "-o") ||
           !strcmp(argv[1], "--output") && (*kf = argv[2]);
}

int parse_args(int argc, char *argv[], char **kf) {
    return argc == 3 && parse_pos_args(argv, kf);
}

char *genkey(int l) {
    char *buffer = (char *)malloc(l * sizeof(char));
    for (int i = 0; i < l; ++i) {
        buffer[i] = 126 - rand() % 93;
    }
    return buffer;
}

int main(int argc, char *argv[]) {
    char *kf, *key;
    if (!parse_args(argc, argv, &kf)) {
        print_help();
        return -1;
    }
    srand(time(0));
    key = genkey(32);
    printf("%s\n", key);
    free(key);
    return 0;
}
