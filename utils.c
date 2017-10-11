#include <memory.h>
#include <malloc.h>
#include <ctype.h>
#include <sys/wait.h>
#include <time.h>
#include "file_processing.h"

void trim(char *str) {
    int first_non_whitespace_index = 0;
    int len = strlen(str);
    while (first_non_whitespace_index < len && isspace(str[first_non_whitespace_index])) {
        first_non_whitespace_index++;
    }
    int last_non_whitespace_index = len - 1;
    while (last_non_whitespace_index > first_non_whitespace_index && isspace(str[last_non_whitespace_index])) {
        last_non_whitespace_index--;
    }
    int actual_len = last_non_whitespace_index - first_non_whitespace_index + 1;
    for (int i = 0; i < actual_len; i++) {
        str[i] = str[i + first_non_whitespace_index];
    }
    str[actual_len] = '\0';
}

int split(char *str, char delimiter, char ***result) {
    int len = strlen(str);
    int actual_start = 0, actual_end = len - 1;
    while (actual_start < len && str[actual_start] == delimiter) actual_start++;
    while (actual_end >= 0 && str[actual_end] == delimiter) actual_end--;

    int partitions_number = 1;
    for (int i = actual_start; i <= actual_end; i++) {
        if (str[i] == delimiter) {
            while (i <= actual_end && str[i] == delimiter) i++;
            partitions_number++;
        }
    }
    *result = malloc(partitions_number * sizeof(char *));
    int prev = actual_start, partition_index = 0;
    for (int index = actual_start; index <= actual_end; index++) {
        while (index <= actual_end && str[index] != delimiter) index++;
        (*result)[partition_index] = malloc(sizeof(char) * (index - prev) + 1);
        for (int i = prev; i < index; i++) (*result)[partition_index][i - prev] = str[i];
        (*result)[partition_index][index - prev] = '\0';
        while (index <= actual_end && str[index] == delimiter) index++;
        prev = index--;
        partition_index++;
    }
    return partitions_number;
}

char *cpy_string(const char *src) {
    int len = strlen(src);
    char *copy = malloc((len + 1) * sizeof(char));
    int index = 0;
    for (index = 0; index < len; index++) copy[index] = src[index];
    copy[index] = '\0';
    return copy;
}

char *substring(const char *str, int p1, int p2) {
    char *ret = malloc(sizeof(char) * (p2 - p1 + 1));
    int index = 0;
    for (int i = p1; i < p2; i++) {
        ret[index++] = str[i];
    }
    ret[index] = '\0';
    return ret;
}

char *join_by(const char *str1, const char *str2, char delimiter) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    char *ret = malloc(sizeof(char) * (len1 + len2 + 2));
    int index = 0;
    for (int i = 0; i < len1; i++) ret[index++] = str1[i];
    ret[index++] = delimiter;
    for (int i = 0; i < len2; i++) ret[index++] = str2[i];
    ret[index] = '\0';
    return ret;
}

void proccess_ended_log() {
    pid_t pid;
    while ((pid = wait(0)) != -1);
    open_log_file();
    logger("Chlid Process Ended!");
    close_log_file();
}

char *get_time() {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    return asctime(timeinfo);
}
