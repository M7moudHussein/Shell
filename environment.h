#ifndef ENVIRONMENT_H_   /* Include guard */
#define ENVIRONMENT_H_

#include "custom_types.h"
#include "map.h"

/*
	- This function should be responsible for importing environment variables into your project.
	- Typically, this function should add $PATH, $HOME & any other needed variables into your variables table 
	- Any future work on variables added by this function should be done through your variable table

	- You also need to store the path of the directory containing this project into a variable, 
	  you'll need it in printning the history & log into a files beside your executable file
*/

char **paths;
int number_of_paths;
map *variables;

void setup_environment(void);

char *get_command_path(const command_line command);

void put_variable(char *, char *);

char *get_variable(char *);

char *get_history_path();

char *get_log_path();

#endif // ENVIRONMENT_H_