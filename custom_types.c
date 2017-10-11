#include <malloc.h>
#include "custom_types.h"

command_line *build_command_line() {
    command_line *ret = malloc(sizeof(char **) + sizeof(bool) * 8 + sizeof(char *) * 3 + sizeof(int));
    ret->background_run = false;
    ret->is_comment = false;
    ret->is_blank = false;
    ret->is_cd = false;
    ret->is_echo = false;
    ret->is_history = false;
    ret->is_exit = false;
    return ret;
}