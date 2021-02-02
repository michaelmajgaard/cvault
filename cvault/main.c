#include "permute.h"
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>

void print_help() {
    printf(
        "usage:\n"
        "\tcvault add --entry <entry> --value <value> --key-dir <directory> "
        "--data-dir <directory>\n"
        "\tcvault add -e <entry> -v <value> -k <directory> -d <directory>\n\n"
        "commands:\n"
        "\tadd\tAdds the specified entry to the data file\n\n"
        "options:\n"
        "\t-e --entry <entry>\tIdentifier of a given entry.\n"
        "\t-v --value <value>\tValue to be stored under the given entry.\n"
        "\t-k --key-dir <directory>\tPath to key file.\n"
        "\t-d --data-dir <directory>\tPath to data file.\n");
}

int parse_mut_excl_arg(char *arg, int optc, char *opts[]) {
    for (int i = 0; i < optc; ++i) {
        if (!strcmp(arg, opts[i])) {
            return 1;
        }
    }
    return 0;
}

int parse_pos_args(char *argv[], int ei, int vi, int kdi, int ddi, char **e,
                   char **v, char **kd, char **dd) {
    return (!strcmp(argv[ei], "-e") || !strcmp(argv[ei], "--entry")) &&
           (!strcmp(argv[vi], "-v") || !strcmp(argv[vi], "--value")) &&
           (!strcmp(argv[kdi], "-k") || !strcmp(argv[kdi], "--key-dir")) &&
           (!strcmp(argv[ddi], "-d") || !strcmp(argv[ddi], "--data-dir")) &&
           (*e = argv[ei + 1]) && (*v = argv[vi + 1]) &&
           (*kd = argv[kdi + 1]) && (*dd = argv[ddi + 1]);
}

int parse_args(int argc, char *argv[], char **c, char **e, char **v, char **kd,
               char **dd) {
    char *opts[] = {"add"};
    if (argc != 10 || !parse_mut_excl_arg((*c = argv[1]), 1, opts)) {
        return 0;
    }
    int ord[4], i = 0, r = 0;
    char *p = permute("2468");
    char *ptr = p;
    while (*ptr) {
        if (*ptr == '\n') {
            if (parse_pos_args(argv, ord[0], ord[1], ord[2], ord[3], e, v, kd,
                               dd)) {
                r = 1;
                break;
            }
            i = 0;
        } else {
            ord[i] = *ptr - '0';
            ++i;
        }
        ++ptr;
    }
    free(p);
    return r;
}

int read_all_text(char *path, char **content) {
    FILE *fp;
    if ((fp = fopen(path, "r")) != NULL) {
        fseek(fp, 0L, SEEK_END);
        int l;
        if ((l = ftell(fp)) >= 0) {
            *content = (char *)malloc((l + 1) * sizeof(char));
            rewind(fp);
            fread(*content, 1, l, fp);
            (*content)[l] = '\0';
            fclose(fp);
            return 1;
        }
    }
    return 0;
}

char *genkey(int length) {
    char *buffer = (char *)malloc((length + 1) * sizeof(char));
    for (int i = 0; i < length; ++i) {
        buffer[i] = rand() % 255;
    }
    buffer[length] = '\0';
    return buffer;
}

char *xor_otp(char *pt) {
    // todo implemen xor otp
    return pt;
}

int add(char **e, char **v, char **kd, char **dd) { printf("add\n"); }

int main(int argc, char *argv[]) {
    char *c, *e, *v, *kd, *dd, *entry, *value;
    if (!parse_args(argc, argv, &c, &e, &v, &kd, &dd)) {
        print_help();
        return -1;
    }
    if (!strcmp(c, "add")) {
        add(&e, &v, &kd, &dd);
    }
    return 0;
}
