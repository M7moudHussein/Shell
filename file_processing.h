#ifndef FILE_PROCESSING_H_   /* Include guard */
#define FILE_PROCESSING_H_

#include <stdio.h>
#include "custom_types.h"

FILE *history_file_ptr;

FILE *log_file;

int read_history_file(char ***);

bool history_file_exists();

void write_history_file(char *);

/* 
	log file basic functions' prototypes
*/
void open_log_file();

void logger(char *);

void close_log_file();


FILE *commands_batch_file_ptr;

bool open_commands_batch_file(const char *dir);

FILE *get_commands_batch_file();

void close_commands_batch_file();


#endif // FILE_PROCESSING_H_