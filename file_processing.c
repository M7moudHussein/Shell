#include "file_processing.h"
#include "environment.h"
#include "utils.h"
#include <unistd.h>
#include <memory.h>
#include <malloc.h>


void open_log_file() {
    log_file = fopen(get_log_path(), "a");
}

void close_log_file() {
    fclose(log_file);
}


/* 
	CommandsBatch file section
*/
bool open_commands_batch_file(const char *dir) {
    if (access(dir, F_OK) != 0) {
        return false;
    }
    commands_batch_file_ptr = fopen(dir, "r");
    return true;
}

FILE *get_commands_batch_file() {
    return commands_batch_file_ptr;
}

void close_commands_batch_file() {
    fclose(commands_batch_file_ptr);
}

int read_history_file(char ***history) {
    if (!history_file_exists()) {
        return 0;
    }
    char line[520];
    int count = 0;
    history_file_ptr = fopen(get_history_path(), "r");
    while (fgets(line, 520, history_file_ptr)) count++;
    fclose(history_file_ptr);
    *history = malloc(sizeof(char *) * count);
    int index = 0, len;
    history_file_ptr = fopen(get_history_path(), "r");
    while (fgets(line, 520, history_file_ptr)) {
        len = strlen(line);
        (*history)[index] = malloc((len) * sizeof(char));
        strcpy((*history)[index], line);
        (*history)[index++][len - 1] = '\0';
    }
    fclose(history_file_ptr);
    return count;
}

bool history_file_exists() {
    if (access(get_history_path(), F_OK) == false) return true;
    else return false;
}

void write_history_file(char *line) {
    history_file_ptr = fopen(get_history_path(), "a");
    fputs(line, history_file_ptr);
    fclose(history_file_ptr);
}

void logger(char *log_msg) {
    fprintf(log_file, "%s [Date] %s", log_msg, get_time());
}
