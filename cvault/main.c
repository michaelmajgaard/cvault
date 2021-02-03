#include <stdio.h>
#include <stdlib.h>
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

int parse_pos_arg(int argc, char *argv[], char *short_name, char *long_name,
                  char **value) {
    for (int i = 0; i < argc - 1; ++i) {
        char *cur = argv[i];
        if (!strcmp(cur, short_name) || !strcmp(cur, long_name)) {
            *value = argv[i + 1];
            return 1;
        }
    }
    return 0;
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

int main(int argc, char *argv[]) {
    char *command, *commands[] = {"add"}, *entry, *key_dir, *data_dir;
    if (argc >= 9 && parse_mut_excl_arg((command = argv[1]), 1, commands) &&
        parse_pos_arg(argc, argv, "-e", "--entry", &entry) &&
        parse_pos_arg(argc, argv, "-k", "--key-dir", &key_dir) &&
        parse_pos_arg(argc, argv, "-d", "--data-dir", &data_dir)) {
        if (argc == 10 && !strcmp(command, "add")) {
            char *value;
            if (parse_pos_arg(argc, argv, "-v", "--value", &value)) {
                printf("add\n");
                return 0;
            }
        }
    }
    print_help();
    return -1;
}
