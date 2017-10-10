#include "file_processing.h"

/* 
	history file section
*/
void open_history_file() {
    // you should implement this function
}

FILE *get_history_file() {
    // you should implement this function
}

void close_history_file() {
    // you should implement this function
}


/* 
	log file section
*/
void open_log_file() {
    // you should implement this function
}

FILE *get_log_file() {
    // you should implement this function
}

void close_log_file() {
    // you should implement this function
}


/* 
	CommandsBatch file section
*/
void open_commands_batch_file(const char *dir) {
    commands_batch_file_ptr = fopen(dir, "r");
}

FILE *get_commands_batch_file() {
    return commands_batch_file_ptr;
}

void close_commands_batch_file() {
    fclose(commands_batch_file_ptr);
}