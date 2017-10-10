#ifndef COMMAND_PARSER_H   /* Include guard */
#define COMMAND_PARSER_H

#include "custom_types.h"

/*
	- This function should be responsible for importing all details of the command 
	- Should specify the type of the command "comment, cd, echo, expression - X=5 -, else"
	- Should specify the arguments of the command
	- Should specify if the command is background or foreground
	- Should consider all parsing special cases, example: many spaces in  "ls     -a"

	- You're left free to decide how to return your imported details of this command

	- Best practice is to use helper function for each collection of logical instructions,
	  example: function for splitting the command by space into array of strings, ..etc
*/

const char background_run_character = '&';
const char comment_character = '#';
const char variable_call_character = '$';

command_line *parse_command(const char *line);


#endif // COMMAND_PARSER_H