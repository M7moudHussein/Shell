#ifndef SHELL_UTILS_H
#define SHELL_UTILS_H

void trim(char *);

int split(char *, char, char ***);

char *cpy_string(const char *);

char *substring(const char *str, int p1, int p2);

char *join_by(const char *str1, const char *str2, char delimiter);

void proccess_ended_log();

char *get_time();

#endif //SHELL_UTILS_H
