#ifndef SHELL_CUSTOM_TYPES_H
#define SHELL_CUSTOM_TYPES_H

typedef enum {
    true = 1,
    false = 0
} bool;

typedef struct command_line {
    char *command;
    char **parameters;
    char *full_parameter;
    char *full_command;
    int parameters_length;
    bool background_run;
    bool is_comment;
    bool is_blank;
    bool is_cd;
    bool is_echo;
    bool is_history;
    bool is_exit;
} command_line;

command_line *build_command_line();

#endif //SHELL_CUSTOM_TYPES_H
