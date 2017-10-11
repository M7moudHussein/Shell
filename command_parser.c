#include <ctype.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "environment.h"

extern const char background_run_character;
extern const char comment_character;
extern const char *cd_command;
extern const char *echo_command;
extern const char *history_command;
extern const char *exit_command;
extern const char variable_call_character;

char *replace_variables_by_values(const char *);

char *set_full_parameter(const char *);

command_line *parse_command(const char *line) {
    if (line == NULL) return NULL;
    command_line *command = build_command_line();
    char *line_cpy = cpy_string(line);
    trim(line_cpy);

    command->full_command = cpy_string(line_cpy);
    int len = strlen(line_cpy);

    if (len == 0) command->is_blank = true;
    else if (line_cpy[0] == comment_character) command->is_comment = true;
    else if (line_cpy[len - 1] == background_run_character) {
        command->background_run = true;
        line_cpy[len - 1] = '\0';
    } else command->background_run = false;

    char *line_after_replacing_variables = replace_variables_by_values(line_cpy);

    char **splitted_line;
    int parameters_length = split(line_after_replacing_variables, ' ', &splitted_line);
    command->command = splitted_line[0];

    char **parameters = malloc(sizeof(char *) * (parameters_length + 1));

    for (int i = 0; i < parameters_length; i++) parameters[i] = splitted_line[i];
    parameters[parameters_length] = NULL;
    command->parameters = parameters;
    command->parameters_length = parameters_length + 1;

    if (strlen(command->full_command) == 0) command->is_blank = true;
    else if (strcmp(command->command, cd_command) == 0) command->is_cd = true;
    else if (strcmp(command->command, echo_command) == 0) command->is_echo = true;
    else if (strcmp(command->command, history_command) == 0) command->is_history = true;
    else if (strcmp(command->command, exit_command) == 0) command->is_exit = true;
    command->full_parameter = set_full_parameter(line_after_replacing_variables);
    free(line_after_replacing_variables);
    return command;
}

char *set_full_parameter(const char *line) {
    int index = 0, len = strlen(line);;
    while (index < len && !isspace(line[index])) index++;
    while (index < len && isspace(line[index])) index++;
    return substring(line, index, len);
}

char *replace_variables_by_values(const char *command_string) {
    char *str = cpy_string(command_string);
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == '\'' || str[i] == '\"') {
            int j = i;
            j++;
            while (j < len && str[j] != str[i]) j++;
            i = j;
            continue;
        }
        if (str[i] == variable_call_character) {
            if ((i < len - 1 && isspace(str[i + 1])) || i == len - 1) continue;
            int j = i + 1;
            while (j < len && !isspace(str[j])) j++;
            char *variable_name = substring(str, i + 1, j);
            char *variable_value = get(&variables, variable_name);
            free(variable_name);

            if (variable_value == NULL) variable_value = "";

            int value_len = strlen(variable_value);
            int size = sizeof(char) * (i + value_len + (len - j) + 1);
            char *tmp = malloc(size);
            int k = 0;
            while (k < i) tmp[k] = str[k++];
            for (int l = 0; l < value_len; l++) tmp[k++] = variable_value[l];
            j++;
            while (j < len) tmp[k++] = str[j++];
            tmp[k] = '\0';
            free(str);
            str = tmp;
            len = strlen(str);
            i += value_len;
        }
    }
    return str;
}

