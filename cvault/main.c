#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>

void print_help() {
    printf("usage:\n"
           "\tcvault add --entry <entry> --value <value> --key-file <file> "
           "--data-file <file>\n"
           "\tcvault -e <entry> -v <value> -k <file> -d <file>\n\n"
           "options:\n"
           "\t-e --entry <file>\tIdentifier of a given entry.\n"
           "\t-v --value <value>\tValue to be stored under the given entry.\n"
           "\t-k --key-file <file>\tPath to key file.\n"
           "\t-d --data-file <file>\tPath to data file.\n");
}

int parse_mut_excl_arg(char *arg, int optc, char *opts[]) {
    for (int i = 0; i < optc; ++i) {
        if (!strcmp(arg, opts[i])) {
            return 1;
        }
    }
    return 0;
}

int parse_pos_args(char *argv[], int ei, int vi, int kfi, int dfi, char **e,
                   char **v, char **kf, char **df) {
    return (!strcmp(argv[ei], "-e") || !strcmp(argv[ei], "--entry")) &&
           (!strcmp(argv[vi], "-v") || !strcmp(argv[vi], "--value")) &&
           (!strcmp(argv[kfi], "-k") || !strcmp(argv[kfi], "--key-file")) &&
           (!strcmp(argv[dfi], "-d") || !strcmp(argv[dfi], "--data-file")) &&
           (*e = argv[ei + 1]) && (*v = argv[vi + 1]) &&
           (*kf = argv[kfi + 1]) && (*df = argv[dfi + 1]);
}

int parse_args(int argc, char *argv[], char **e, char **v, char **kf,
               char **df) {
    // todo calc permutations
    return argc == 9 && (parse_pos_args(argv, 1, 3, 5, 7, e, v, kf, df) ||
                         parse_pos_args(argv, 3, 1, 7, 5, e, v, kf, df));
}

int read_all_text(char *path, char **content) {
    FILE *fp;
    if ((fp = fopen(path, "r")) != NULL) {
        fseek(fp, 0L, SEEK_END);
        int l;
        if ((l = ftell(fp)) > 0) {
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

char *xor_otp(char *pt) { int l = strlen(pt); }

int main(int argc, char *argv[]) {
    char *e, *v, *kf, *df, *entry, *value, *key, *data;
    if (!parse_args(argc, argv, &e, &v, &kf, &df) || !read_all_text(kf, &key) ||
        !read_all_text(df, &data)) {
        print_help();
        return -1;
    }
    printf("%s", key);
    free(key);
    return 0;
}
