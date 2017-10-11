#ifndef COMMANDS_H_   /* Include guard */
#define COMMANDS_H_

const char home_dir_char = '~';

const char *cd_command = "cd";

const char *echo_command = "echo";

const char *history_command = "history";

const char *exit_command = "exit";

bool cd(command_line *command);

bool echo(const char *message);

bool show_history();

void exit_shell();

#endif // COMMANDS_H_