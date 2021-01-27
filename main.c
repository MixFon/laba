#include "object_process.h"

int main(int argc, char **argv)
{
	g_size = 2;
	g_count = 0;
    long int err_lvl = EXIT_SUCCESS;
    setbuf(stdout, NULL);
	t_obj *arr_obj;
	if (argc < 2)
		return (0);
	if (!(arr_obj = (t_obj *)malloc(sizeof(t_obj) * g_size)))
		sys_err("Memory allocation.", ERR_MEMORY_ALLOCATION);
	read_objeckts(&arr_obj, argv[1]);
	if (argc == 2)
	{
		sort_items(arr_obj);
		print_arr_obj(arr_obj);
	}
	else if (argc == 3)
	{
        if (strncmp(argv[2], "ALL", 3) == 0)
			print_arr_obj(arr_obj);
		else
			print_sub_string(arr_obj, argv[2]);
	}
	return (0);	
}
