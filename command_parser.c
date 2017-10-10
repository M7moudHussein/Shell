
#include <ctype.h>
#include "custom_types.h"
#include "utils.h"
#include "environment.h"

extern const char background_run_character;
extern const char comment_character;
extern const char variable_call_character;
extern const char *cd_command;
extern const char *echo_command;

char *replace_variables_by_values(const char *);

command_line *parse_command(const char *line) {
    if (line == NULL) return NULL;

    command_line *command = malloc(sizeof(char *) * 2 + sizeof(char **) + sizeof(bool) * 5);

    char *line_cpy = cpy_string(line);
    trim(line_cpy);
    int len = strlen(line_cpy);

    if (len == 0) command->is_blank = true;
    else if (line_cpy[0] == comment_character) command->is_comment = true;
    else if (line_cpy[len - 1] == background_run_character) {
        command->background_run = true;
        line_cpy[len - 1] = '\0';
    } else command->background_run = false;

    line_cpy = replace_variables_by_values(line_cpy);

    char **splitted_line;
    int parameters_length = split(line_cpy, ' ', &splitted_line);

    command->command = splitted_line[0];
    char **parameters = malloc(sizeof(char *) * parameters_length + 1);

    for (int i = 0; i < parameters_length; i++) parameters[i] = splitted_line[i];

    parameters[parameters_length] = NULL;
    command->parameters = parameters;
    command->parameters_length = parameters_length + 1;
    if (strcmp(command->command, cd_command) == 0) command->is_cd = true;
    if (strcmp(command->command, echo_command) == 0) command->is_echo = true;
    command->origional_command = cpy_string(line);
    return command;
}

char *replace_variables_by_values(const char *str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        puts("HERE");
        if ((str[i] == variable_call_character) && (i == 0 || (i > 0 && isspace(str[i - 1])))) {
            int j = i + 1;
            while (j < len && !isspace(str[j])) j++;
            char *variable_name = substring(*str, i + 1, j);
            char *variable_value = get_variable(variable_name);
            if (variable_value != NULL) {
                int value_len = strlen(variable_value);
                char *tmp = malloc(sizeof(char) * (i + len - j + value_len));
                strcat(tmp, substring(*str, 0, i));
                strcat(tmp, variable_value);
                strcat(tmp, substring(*str, j, len));
                free(*str);
                str = tmp;
                len = strlen(*str);
                i += value_len;
            }
        }
        puts("THere");
    }
}

