#include <stddef.h>
#include <malloc.h>
#include <memory.h>
#include "map.h"

void put(map **linked_list, char *key, char *value) {
    map *it = *linked_list;
    while (it->next != NULL) {
        it = it->next;
        if (strcmp(it->key, key) == 0) {
            free(it->value);
            it->value = malloc(sizeof(char) * strlen(value));
            strcpy(it->value, value);
            return;
        }
    }
    it->next = malloc(sizeof(map));
    it = it->next;
    it->key = malloc(sizeof(char) * strlen(key));
    it->value = malloc(sizeof(char) * strlen(value));
    strcpy(it->key, key);
    strcpy(it->value, value);
}

char *get(map **linked_list, char *key) {
    map *it = (*linked_list)->next;
    while (it != NULL) {
        if (strcmp(it->key, key) == 0) {
            char *ret = malloc(sizeof(char) * strlen(it->value));
            strcpy(ret, it->value);
            return ret;
        }
        it = it->next;
    }
    return NULL;
}

void build_map(map **mapper) {
    *mapper = malloc(sizeof(map));
}

char *get_or_default(map **mp, char *key, char *def) {
    char *res = get(mp, key);
    if (res == NULL) {
        return def;
    } else {
        return def;
    }
}

