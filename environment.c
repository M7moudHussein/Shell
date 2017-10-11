#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <signal.h>
#include "environment.h"
#include "utils.h"

void setup_environment(void) {
    signal(SIGCHLD, proccess_ended_log);
    char *unsplitted_paths = getenv("PATH");
    char **result;
    number_of_paths = split(unsplitted_paths, ':', &result);
    paths = result;
    build_map(&variables);
    put(&variables, "HOME", getenv("HOME"));
    put(&variables, "PATH", getenv("PATH"));
}

char *get_command_path(const command_line command) {
    for (int i = 0; i < number_of_paths; i++) {
        if (access(command.command, F_OK) == false) {
            return cpy_string(command.command);
        }
        char *command_path = cpy_string(paths[i]);
        strcat(command_path, "/");
        strcat(command_path, command.command);
        if (access(command_path, F_OK) == false) {
            return cpy_string(command_path);
        }
    }
    return NULL;
}

void put_variable(char *variable_name, char *variable_value) {
    put(&variables, variable_name, variable_value);
}

char *get_variable(char *variable_name) {
    return get(&variables, variable_name);
}

char *get_history_path() {
    return join_by(getenv("HOME"), "Shell/history", '/');
}

char *get_log_path() {
    return join_by(getenv("HOME"), "Shell/log", '/');
}
