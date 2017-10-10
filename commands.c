#include <unistd.h>
#include "custom_types.h"
#include "environment.h"

extern const char home_dir_char;

bool cd(command_line *command) {
    if (command->parameters_length != 3) {
        return false;
    }
    if (command->parameters[1][0] == home_dir_char) {
        int len = strlen(command->parameters[1]);
        char *tmp = malloc(sizeof(char) * (len - 1) + sizeof(get_variable("HOME")));
        strcat(tmp, get_variable("HOME"));
        int current_len = strlen(tmp);
        for (int i = current_len, j = 1; j < len; j++, i++) tmp[i] = command->parameters[1][j];
        free(command->parameters[1]);
        command->parameters[1] = tmp;
    }
    if (chdir(command->parameters[1]) != false) {
        return false;
    }
    return true;
}


bool echo(const char *message) {
    puts(message);
    return true;
}