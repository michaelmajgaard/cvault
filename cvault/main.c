#include "arg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

int write_to_file(char *path, char *content) {
    FILE *fp;
    if ((fp = fopen(path, "w+")) != NULL) {
        fprintf(fp, content);
        fclose(fp);
    }
}

char *genkey(int length) {
    char *buffer = (char *)malloc((length + 1) * sizeof(char));
    for (int i = 0; i < length; ++i) {
        buffer[i] = rand() % 254 + 1;
    }
    buffer[length] = '\0';
    return buffer;
}

char *xor_otp(int length, char *value, char *otp_key) {
    char *otp = (char *)malloc((length + 1) * sizeof(char));
    for (int i = 0; i < length; ++i) {
        otp[i] = (char)(value[i] ^ otp_key[i]);
    }
    otp[length] = '\0';
    return otp;
}

void combine_path(char *x, char *y, char **combined) {
    strcat(*combined, x);
    strcat(*combined, "/\0");
    strcat(*combined, y);
}

int add(char *entry, char *value, char *key_dir, char *data_dir) {
    int length;
    char *otp_key, *otp, *key_path, *data_path;
    key_path = malloc((strlen(key_dir) + strlen(entry) + 2) * sizeof(char));
    data_path = malloc((strlen(data_dir) + strlen(entry) + 2) * sizeof(char));
    combine_path(key_dir, entry, &key_path);
    combine_path(data_dir, entry, &data_path);
    srand(time(0));
    length = strlen(value);
    otp_key = genkey(length);
    otp = xor_otp(length, value, otp_key);
    write_to_file(data_path, otp);
    write_to_file(key_path, otp_key);
    free(key_path);
    free(data_path);
    free(otp);
    free(otp_key);
    return 1;
}

int main(int argc, char *argv[]) {
    char *command, *commands[] = {"add"}, *entry, *key_dir, *data_dir;
    if (argc >= 9 && contains((command = argv[1]), 1, commands) &&
        parse_pos_arg(argc, argv, "-e", "--entry", &entry) &&
        parse_pos_arg(argc, argv, "-k", "--key-dir", &key_dir) &&
        parse_pos_arg(argc, argv, "-d", "--data-dir", &data_dir)) {
        if (argc == 10 && !strcmp(command, "add")) {
            char *value;
            if (parse_pos_arg(argc, argv, "-v", "--value", &value)) {
                if (add(entry, value, key_dir, data_dir)) {
                    return 0;
                }
            }
        }
    }
    print_help();
    return -1;
}
