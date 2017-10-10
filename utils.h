#ifndef SHELL_UTILS_H
#define SHELL_UTILS_H

#include "map.h"

void trim(char *);

int split(char *, char, char ***);

char *cpy_string(const char *);

char *substring(char *str, int p1, int p2);

#endif //SHELL_UTILS_H
