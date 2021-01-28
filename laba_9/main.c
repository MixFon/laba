#include "object_process.h"

int main(int argc, char **argv)
{
    long int err_lvl = EXIT_SUCCESS;
    setbuf(stdout, NULL);

    if (argc == 2)
    {
        err_lvl = sort_by_density(argv[1]);
        return err_lvl;
    }
    if (argc == 3)
    {
        if (strncmp(argv[2], "ALL", 3) == 0)
        {
            err_lvl = print_array(argv[1]);
            return err_lvl;
        }
        else
        {
            err_lvl = find_in_array(argv[1], argv[2]);
            return err_lvl;
        }
    }
    else
        return ERR_BAD_KEYS;
}
