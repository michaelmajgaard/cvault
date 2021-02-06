#include "arg.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void print_help() {
    printf(
        "usage:\n"
        "\tcvault add -e <entry> -v <value> -k <directory> -d <directory>\n"
        "\tcvault get -e <entry> -k <directory> -d <directory>\n"
        "\tcvault delete -e <entry> -k <directory> -d <directory>\n\n"
        "commands:\n"
        "\tadd\tAdds the specified entry to the data file.\n"
        "\tget\tGets the specified entry from the data file, decrypts it "
        "and writes it to stdout.\n"
        "\tdelete\tDeletes the specified entry from the data and key file.\n\n"
        "options:\n"
        "\t-e --entry <entry>\t\tIdentifier of a given entry.\n"
        "\t-v --value <value>\t\tValue to be stored under the given entry.\n"
        "\t-k --key-dir <directory>\tPath to key file.\n"
        "\t-d --data-dir <directory>\tPath to data file.\n");
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

int add(char *entry, char *value, char *key_dir, char *data_dir) {
    int length, result;
    char *otp_key, *otp, *key_path, *data_path;
    key_path = combine_path(key_dir, entry);
    data_path = combine_path(data_dir, entry);
    srand(time(0));
    length = strlen(value);
    otp_key = genkey(length);
    otp = xor_otp(length, value, otp_key);
    result = write_all_text(data_path, otp) & write_all_text(key_path, otp_key);
    free(key_path);
    free(data_path);
    free(otp);
    free(otp_key);
    return result;
}

int get(char *entry, char *key_dir, char *data_dir, char **value) {
    int result;
    char *otp_key, *otp, *key_path, *data_path;
    key_path = combine_path(key_dir, entry);
    data_path = combine_path(data_dir, entry);
    result = read_all_text(key_path, &otp_key) &&
             read_all_text(data_path, &otp) && strlen(otp_key) == strlen(otp);
    if (result) {
        *value = xor_otp(strlen(otp), otp, otp_key);
    }
    free(key_path);
    free(data_path);
    free(otp);
    free(otp_key);
    return result;
}

int delete (char *entry, char *key_dir, char *data_dir) {
    char *key_path = combine_path(key_dir, entry),
         *data_path = combine_path(data_dir, entry);
    return !remove(key_path) && !remove(data_path);
}

int main(int argc, char *argv[]) {
    char *command, *commands[] = {"add", "get", "delete"}, *entry, *key_dir,
                   *data_dir;
    if (argc >= 8 && contains((command = argv[1]), 3, commands) &&
        parse_optv(argc, argv, "-e", "--entry", &entry) &&
        parse_optv(argc, argv, "-k", "--key-dir", &key_dir) &&
        parse_optv(argc, argv, "-d", "--data-dir", &data_dir)) {
        if (argc == 10 && !strcmp(command, "add")) {
            char *value;
            if (parse_optv(argc, argv, "-v", "--value", &value)) {
                if (add(entry, value, key_dir, data_dir)) {
                    return 0;
                }
            }
        } else if (!strcmp(command, "get")) {
            char *value;
            if (get(entry, key_dir, data_dir, &value)) {
                printf("%s", value);
                return 0;
            }
        } else if (!strcmp(command, "delete")) {
            if (delete (entry, key_dir, data_dir)) {
                return 0;
            }
        }
    }
    print_help();
    return -1;
}
