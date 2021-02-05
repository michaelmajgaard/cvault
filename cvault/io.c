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
        fprintf(fp, content);
        fclose(fp);
        return 1;
    }
    return 0;
}

void combine_path(char *x, char *y, char **combined) {
    strcat(*combined, x);
    strcat(*combined, "/\0");
    strcat(*combined, y);
}
