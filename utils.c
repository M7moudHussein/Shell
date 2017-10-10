#include <memory.h>
#include <malloc.h>
#include <ctype.h>
#include "utils.h"

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
    result[0] = malloc(partitions_number * sizeof(char **));
    int prev = actual_start, partition_index = 0;
    for (int index = actual_start; index <= actual_end; index++) {
        while (index <= actual_end && str[index] != delimiter) index++;
        result[0][partition_index] = malloc(sizeof(char) * (index - prev));
        for (int i = prev; i < index; i++) result[0][partition_index][i - prev] = str[i];
        while (index <= actual_end && str[index] == delimiter) index++;
        prev = index--;
        partition_index++;
    }
    return partitions_number;
}

char *cpy_string(const char *src) {
    int len = strlen(src);
    char *copy = malloc(len * sizeof(char) * len);
    strcpy(copy, src);
    return copy;
}

char *substring(char *str, int p1, int p2) {
    char *ret = malloc(sizeof(char) * (p2 - p1));
    for (int i = p1; i < p2; i++) {
        ret[i - p1] = str[i];
    }
    return ret;
}

