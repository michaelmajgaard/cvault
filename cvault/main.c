#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>

void print_help() {
    printf("usage:\n"
           "\tcvault --key-file <file> --data-file <file>\n"
           "\tcvault -k <file> -d <file>\n\n"
           "options:\n"
           "\t-k --key-file <file>\tPath to key file.\n"
           "\t-d --data-file <file>\tPath to data file.\n");
}

int parse_pos_args(char *argv[], int kfi, int dfi, char **kf, char **df) {
    return (!strcmp(argv[kfi], "-k") || !strcmp(argv[kfi], "--key-file")) &&
           (!strcmp(argv[dfi], "-d") || !strcmp(argv[dfi], "--data-file")) &&
           (*kf = argv[kfi + 1]) && (*df = argv[dfi + 1]);
}

int parse_args(int argc, char *argv[], char **kf, char **df) {
    return argc == 5 && (parse_pos_args(argv, 1, 3, kf, df) ||
                         parse_pos_args(argv, 3, 1, kf, df));
}

int main(int argc, char *argv[]) {
    char *kf, *df;
    if (!parse_args(argc, argv, &kf, &df)) {
        print_help();
        return -1;
    }
    return 0;
}
