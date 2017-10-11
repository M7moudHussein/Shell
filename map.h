//
// Created by mahmoud on 10/8/17.
//

#ifndef SHELL_LINKED_LIST_H
#define SHELL_LINKED_LIST_H
typedef struct map {
    char *key;
    char *value;
    struct map *next;
} map;

void put(map **, char *, char *);

char *get(map **, char *);

char *get_or_default(map **, char *, char *);

void build_map(map **);

#endif //SHELL_LINKED_LIST_H
