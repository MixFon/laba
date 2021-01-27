#include "object_process.h"

void print_item(t_obj *item)
{
	printf("name = {%s}\n", item->name);
	printf("mass = {%lf}\n", item->mass);
	printf("volume = {%lf}\n", item->volume);
	printf("density = {%lf}\n", item->density);

}

void print_arr_obj(t_obj *items)
{
	for(int i = 0; i < g_count; i++)
		print_item(items + i);
}

void	sys_err(char *str, int error)
{
	fprintf(stderr, "Error. %s\n", str);
	exit(error);
}

int	check_number(char *line)
{
	while(*line != '\0')
	{
		if (!isdigit(*line) && *line != '.')
			return (0);
		line++;
	}
	return (1);
}

void	check_mass_volume(char *line)
{
	double temp = atof(line);
	if (temp <= 0)
		sys_err("Vrong data.", ERR_BAD_DATA);
}

void	read_objeckts(t_obj **objs, char *name_file)
{
    FILE	*f;
	char	*line = NULL;
	size_t	size = 0;

    f = fopen(name_file, "r");
	if (f == NULL)
		sys_err("Invalid file name.", ERR_OPEN_FILE);
	ssize_t read;	
	size_t i = 0;
	while((read = getline(&line, &size, f)) != -1)
	{
		size_t index = i / 3;
		line[read - 1] = '\0';
		if (i % 3 == 0)
			(*objs)[index].name = strdup(line);
		else
		{
			if (!check_number(line))
				sys_err("Vrong number.", ERR_BAD_DATA);
			if (i % 3 == 1)
			{
				check_mass_volume(line);
				(*objs)[index].mass = atof(line);
			}
			if (i % 3 == 2)
			{
				check_mass_volume(line);
				(*objs)[index].volume = atof(line);
			}
		}
		(*objs)[index].density = (*objs)[index].mass / (*objs)[index].volume;
		free(line);
		line = NULL;
		i++; 
		if (i / 3  >= g_size)
		{
			g_size *= 2;
			if (!(*objs = (t_obj *)realloc(*objs, sizeof(t_obj) * g_size)))
				sys_err("Memory allocation.", ERR_MEMORY_ALLOCATION);
		}
	}
	fclose(f);
	if (i % 3 != 0)
		sys_err("Vrong count struct", ERR_BAD_DATA);
	g_count = i / 3;
}

void	sort_items(t_obj *items)
{
	for (int i = 0; i < g_count; i++)
		for (int j = 0; j < g_count; j++)
		{
			if (items[i].density < items[j].density)
			{
				t_obj buf;
				buf.name = items[i].name;
				buf.mass = items[i].mass;
				buf.volume = items[i].volume;
				buf.density = items[i].density;

				items[i].name = items[j].name;
				items[i].mass = items[j].mass;
				items[i].volume = items[j].volume;
				items[i].density = items[j].density;

				items[j].name = buf.name;
				items[j].mass = buf.mass;
				items[j].volume = buf.volume;
				items[j].density = buf.density;
			}
		}
}

void	print_sub_string(t_obj *items, char *sub_str)
{
	for (int i = 0; i < g_count; i++)
	{
		char *iter = strstr(items[i].name, sub_str);
		if (iter != NULL && iter - items[i].name == 0 && *sub_str != '\0')
			print_item(items + i);
		if (*items[i].name == '\0' && *sub_str == '\0')
			print_item(items + i);
	}	
}
