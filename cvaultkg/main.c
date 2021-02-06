#include "arg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void print_help() {
    printf("usage:\n"
           "\trkg -s <key-size> [-n]\n\n"
           "options:\n"
           "\t-s --size {64 | 128 | 256 | 512}\tKey size in bits.\n"
           "\t-n\t\t\t\t\tOmit trailing newline in output.\n");
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
    if (parse_optv(argc, argv, "-s", "--size", &s)) {
        char *optv[4] = {"64", "128", "256", "512"};
        if (contains(s, 4, optv)) {
            srand(time(0));
            key = genkey(atoi(s));
            printf("%s", key);
            if (!parse_opt(argc, argv, "-n", "")) {
                printf("\n");
            }
            free(key);
            return 0;
        }
    }
    print_help();
    return -1;
}
