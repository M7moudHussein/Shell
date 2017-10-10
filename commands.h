#ifndef COMMANDS_H_   /* Include guard */
#define COMMANDS_H_

#include "custom_types.h"

/*
	- This function should be responsible for implementing the "cd" shell command
*/

const char home_dir_char = '~';

const char *cd_command = "cd";

const char *echo_command = "echo";

bool cd(command_line *command);

/* 
	- This function should be responsible for implementing the "echo" shell command
	- Typically should lookup any variable included in the message
*/
bool echo(const char *message);

#endif // COMMANDS_H_