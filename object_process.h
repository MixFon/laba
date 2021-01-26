#ifndef OBJECT_PROCESS_H
#define OBJECT_PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Все возможные коды ошибок программы.
#define ERR_NO_FILE -1
#define ERR_OPEN_FILE -2
#define ERR_BAD_DATA -3
#define ERR_BAD_KEYS -4
#define ERR_MEMORY_ALLOCATION -5

struct object
{
    char *name;
    double mass;
    double volume;
};

int sort_by_density(char *filename);
int print_array(char *filename);
int find_in_array(char *filename, char *substr);
int input_array(FILE *f, struct object *items[], long *count);

int read_struct(FILE *f, struct object *tmp_item);
int getline_new(char **lineptr, size_t *n, FILE *file);
void free_struct(struct object *items[], long *count);
long count_structs(FILE *f);

#endif
