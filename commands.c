#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include "environment.h"
#include "file_processing.h"

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

bool show_history() {
    char **hisrory;
    int history_size = read_history_file(&hisrory);
    for (int i = 0; i < history_size; i++) puts(hisrory[i]);
    return true;
}

void exit_shell() {
    exit(0);
}
