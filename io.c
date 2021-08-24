#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int write_all_text(char *path, char *content) {
    FILE *fp;
    if ((fp = fopen(path, "w+")) != NULL) {
        fprintf(fp,"%s", content);
        fclose(fp);
        return 1;
    }
    return 0;
}

char *combine_path(char *x, char *y) {
    char *buffer;
    int x_length = strlen(x), sep = y[0] != '/';
    x_length = x_length - (x[x_length - 1] == '/');
    buffer = malloc((x_length + strlen(y) + sep + 1) * sizeof(char));
    for (int i = 0; i < x_length; ++i) {
        buffer[i] = x[i];
    }
    buffer[x_length] = '\0';
    if (sep) {
        strcat(buffer, "/\0");
    }
    strcat(buffer, y);
    return buffer;
}
