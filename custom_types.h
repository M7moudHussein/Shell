#ifndef SHELL_CUSTOM_TYPES_H
#define SHELL_CUSTOM_TYPES_H

#include <malloc.h>
#include <memory.h>

typedef enum {
    true = 1,
    false = 0
} bool;

typedef struct command_line {
    char *command;
    char **parameters;
    char *origional_command;
    int parameters_length;
    bool background_run;
    bool is_comment;
    bool is_blank;
    bool is_cd;
    bool is_echo;
} command_line;
#endif //SHELL_CUSTOM_TYPES_H
