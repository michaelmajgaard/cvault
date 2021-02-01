#include "permute.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap_chars(char *x, char *y) {
    char t = *x;
    *x = *y;
    *y = t;
}

void rec_permute(char *v, int ci, int ei, int l, char **r) {
    if (ci == ei) {
        char buffer[l + 2];
        sprintf(buffer, "%s\n\0", v);
        strcat(*r, buffer);
    } else {
        for (int i = ci; i <= ei; ++i) {
            swap_chars(v + ci, v + i);
            rec_permute(v, ci + 1, ei, l, r);
            swap_chars(v + ci, v + i);
        }
    }
}

char *permute(char *v) {
    char *ptr = v;
    int c = 0, p = 1;
    while (*ptr) {
        ++c;
        p *= c;
        ++ptr;
    }

    char cpy[c + 1], *buffer = malloc(((c + 1) * p + 1) * sizeof(char));
    strcpy(cpy, v);
    rec_permute(cpy, 0, c - 1, c, &buffer);

    return buffer;
}
