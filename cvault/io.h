#ifndef IO_H
#define IO_H

int read_all_text(char *path, char **content);
int write_all_text(char *path, char *content);
void combine_path(char *x, char *y, char **combined);

#endif
