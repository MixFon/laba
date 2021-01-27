#ifndef OBJECT_PROCESS_H
#define OBJECT_PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

//Все возможные коды ошибок программы.
#define ERR_NO_FILE -1
#define ERR_OPEN_FILE -2
#define ERR_BAD_DATA -3
#define ERR_BAD_KEYS -4
#define ERR_MEMORY_ALLOCATION -5


size_t	g_size;
size_t	g_count;

typedef struct	s_obj
{
    char		*name;
    double		mass;
    double		volume;
	double		density;
}				t_obj;

void print_item(t_obj *item);
void print_arr_obj(t_obj *items);
void	sys_err(char *str, int error);
int	check_number(char *line);
void	check_mass_volume(char *line);
void	read_objeckts(t_obj **objs, char *name_file);
void	sort_items(t_obj *items);
void	print_sub_string(t_obj *items, char *sub_str);
#endif
