#include "custom_types.h"
#include "environment.h"
#include "file_processing.h"
#include "commands.h"
#include "command_parser.h"
#include "utils.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <ctype.h>

void start_shell(bool);

void shell_loop(bool);

command_line *read_command(FILE *);

char *get_command_path(command_line line);

void handle_exec_mode(const char *, const command_line *);

void handle_variables(char **, int);

void handle_expression(char *);

bool valid_variable_name(const char *);

pid_t main_process_pid;

char **shell_parameters;

int main(int argc, char *argv[]) {
    shell_parameters = argv;
    main_process_pid = getpid();
    setup_environment();

    if (argc == 2) {
        start(true);
    } else {
        if (argc != 1) {
            perror("wrong optional parameters!");
        }
        start(false);
    }

    return 0;
}

void start(bool read_from_file) {
    if (read_from_file) {
        open_commands_batch_file(shell_parameters[1]);
        shell_loop(true);
    } else {
        shell_loop(false);
    }
}

void shell_loop(bool input_from_file) {
    bool from_file = input_from_file;
    command_line *command;
    while (true) {
        printf("Shell>");
        if (from_file) {
            command = read_command(get_commands_batch_file());
            if (command == NULL) {
                from_file = false;
                continue;
            }
        } else {
            command = read_command(stdin);
        }
        handle_command(command);
    }
}

int handle_command(command_line *cmd) {
    bool exec_result = true;
    if (cmd->is_comment || cmd->is_blank) return exec_result;
    if (cmd->is_cd) return cd(cmd);
    if (cmd->is_echo)return echo(cmd->origional_command);
    char *command_path = get_command_path(*cmd);
    if (command_path != NULL) handle_exec_mode(command_path, cmd);
    handle_variables(cmd->parameters, cmd->parameters_length - 1);
}

void handle_variables(char **expressions, int expressions_count) {
    for (int i = 0; i < expressions_count; i++) {
        handle_expression(expressions[i]);
    }
}

void handle_expression(char *expression) {
    int len = strlen(expression);
    int equals_index = -1;
    for (int i = 0; i < len; i++) {
        if (expression[i] == '=') {
            equals_index = i;
            break;
        }
    }
    if (equals_index == -1) {
        return;
    }
    char *variable_name = substring(expression, 0, equals_index);
    char *variable_value = substring(expression, equals_index + 1, len);
    if (valid_variable_name(variable_name)) {
        put_variable(variable_name, variable_value);
    }
}

bool valid_variable_name(const char *variable_name) {
    if (!variable_name) return false;
    const char *s = variable_name;
    while (*s != '\0') {
        if ((s == variable_name && isdigit(*s)) ||
            (!(*s == '_') && (!isascii(*s) || iscntrl(*s) || ispunct(*s)))) {
            return false;
        }
        ++s;
    }
    return true;
}

void handle_exec_mode(const char *command_path, const command_line *command) {
    if (command->background_run) {
        fork();
        if (getpid() != main_process_pid) {
            execv(command_path, command->parameters);
            exit(0);
        }
    } else {
        fork();
        if (getpid() != main_process_pid) {
            execv(command_path, command->parameters);
            exit(0);
        } else {
            wait(0);
        }
    }
}

command_line *read_command(FILE *steam) {
    char line[520];
    if (!fgets(line, sizeof(line), steam)) {
        return NULL;
    }
    command_line *ret = parse_command(line);
    return ret;
}