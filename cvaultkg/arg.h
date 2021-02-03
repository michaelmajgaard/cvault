#ifndef ARG_H
#define ARG_H

int contains(char *arg, int optc, char *opts[]);
int parse_pos_arg(int argc, char *argv[], char *short_name, char *long_name,
                  char **value);

#endif
