#include "environment.h"
#include "file_processing.h"
#include "commands.h"
#include "command_parser.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <ctype.h>
#include <memory.h>

void start_shell(bool);

void shell_loop(bool);

command_line *read_command(FILE *);

char *get_command_path(command_line line);

bool handle_exec_mode(const char *, const command_line *);

bool handle_variables(char **, int);

bool handle_expression(char *);

bool valid_variable_name(const char *);

void handle_command(command_line *);

void start(bool);

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
        if (!open_commands_batch_file(shell_parameters[1])) {
            fprintf(stderr, "Error while opening batch file %s make sure it exists\n", shell_parameters[1]);
            exit_shell();
        }
        shell_loop(true);
    } else {
        shell_loop(false);
    }
}

void shell_loop(bool input_from_file) {
    bool from_file = input_from_file;
    command_line *command;
    while (true) {
        if (from_file) {
            command = read_command(get_commands_batch_file());
            if (command == NULL) {
                close_commands_batch_file();
                from_file = false;
                continue;
            }
        } else {
            if (getpid() == main_process_pid)
                printf("Shell>");
            command = read_command(stdin);
        }
        handle_command(command);
    }
}

void handle_command(command_line *cmd) {
    if (cmd->is_comment || cmd->is_blank) {
        return;
    } else if (cmd->is_cd) {
        cd(cmd);
        return;
    } else if (cmd->is_echo) {
        echo(cmd->full_parameter);
        return;
    } else if (cmd->is_history) {
        show_history();
        return;
    } else if (cmd->is_exit) {
        exit_shell();
    }
    char *command_path = get_command_path(*cmd);
    if (handle_variables(cmd->parameters, cmd->parameters_length - 1)) return;
    if (command_path != NULL) {
        if (!handle_exec_mode(command_path, cmd)) {
            fprintf(stderr, "Error executing command %s\n", cmd->full_command);
            fflush(stderr);
            return;
        }
    } else {
        fprintf(stderr, "%s : command not found\n", cmd->command);
        fflush(stderr);
        return;
    }
}

bool handle_variables(char **expressions, int expressions_count) {
    int number_of_expressions = 0;
    for (int i = 0; i < expressions_count; i++) {
        if (handle_expression(expressions[i]))
            number_of_expressions++;
    }
    return number_of_expressions == expressions_count ? true : false;
}

bool handle_expression(char *expression) {
    int len = strlen(expression);
    int equals_index = -1;
    for (int i = 0; i < len; i++) {
        if (expression[i] == '=') {
            equals_index = i;
            break;
        }
    }
    if (equals_index == -1) {
        return false;
    }
    char *variable_name = substring(expression, 0, equals_index);
    char *variable_value = substring(expression, equals_index + 1, len);
    if (valid_variable_name(variable_name)) {
        put_variable(variable_name, variable_value);
        return true;
    } else {
        return false;
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

bool handle_exec_mode(const char *command_path, const command_line *command) {
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
            exit_shell(0);
        } else {
            wait(0);
        }
    }
}

command_line *read_command(FILE *steam) {
    char line[520];
    command_line *ret;
    if (!fgets(line, sizeof(line), steam)) return NULL;
    if (strlen(line) > MAX_LINE_LENGTH) {
        echo("Wrong number of arguments");
        ret = build_command_line();
        ret->is_blank = true;
    }
    write_history_file(line);
    ret = parse_command(line);
    return ret;
}