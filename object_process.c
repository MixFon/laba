#include "object_process.h"

int sort_by_density(char *filename)
{
    struct object *items = NULL;
    FILE *f;
    struct object buf;
    double tmp_density, next_density;
    long count = 0, i, j;
    int flag;

    f = fopen(filename, "r");
    if (f == NULL)
        return ERR_OPEN_FILE;
    flag = input_array(f, &items, &count);
    if (flag != EXIT_SUCCESS)
    {
        fclose(f);
        return flag;
    }
    if (count > 0)
        for (i = 0; i < count; i++)
            for (j = i + 1; j <= count; j++)
            {
                tmp_density = items[i].mass / items[i].volume;
                next_density = items[j].mass / items[j].volume;
                if (tmp_density > next_density)
                {
                    buf.name = (char*)calloc(1, sizeof(items[i].name));
                    if (buf.name == NULL)
                    {
                        fclose(f);
                        free_struct(&items, &count);
                        free(items);
                        return ERR_MEMORY_ALLOCATION;
                    }
                    strcpy(buf.name, items[i].name);
                    buf.mass = items[i].mass;
                    buf.volume = items[i].volume;
                    free(items[i].name);
                    items[i].name = (char*)calloc(1, sizeof(items[j].name));
                    if (items[i].name == NULL)
                    {
                        fclose(f);
                        free(buf.name);
                        free_struct(&items, &count);
                        free(items);
                        return ERR_MEMORY_ALLOCATION;
                    }
                    strcpy(items[i].name, items[j].name);
                    items[i].mass = items[j].mass;
                    items[i].volume = items[j].volume;
                    free(items[j].name);
                    items[j].name = (char*)calloc(1, sizeof(buf.name));
                    if (items[j].name == NULL)
                    {
                        fclose(f);
                        free(buf.name);
                        free_struct(&items, &count);
                        free(items);
                        return ERR_MEMORY_ALLOCATION;
                    }
                    strcpy(items[j].name, buf.name);
                    items[j].mass = buf.mass;
                    items[j].volume = buf.volume;
                    free(buf.name);
                }
            }
    for (i = 0; i <= count; i++)
    {
        printf("%s\n", items[i].name);
        printf("%lf\n", items[i].mass);
        printf("%lf\n", items[i].volume);
    }
    fclose(f);
    free_struct(&items, &count);
    free(items);
    return EXIT_SUCCESS;
}

int print_array(char *filename)
{
    struct object *items = NULL;
    FILE *f;
    long count = 0, i;
    int flag;

    f = fopen(filename, "r");
    if (f == NULL)
        return ERR_OPEN_FILE;
    flag = input_array(f, &items, &count);
    if (flag != EXIT_SUCCESS)
    {
        fclose(f);
        return flag;
    }
    for (i = 0; i <= count; i++)
    {
        printf("%s\n", items[i].name);
        printf("%lf\n", items[i].mass);
        printf("%lf\n", items[i].volume);
    }
    fclose(f);
    free_struct(&items, &count);
    free(items);
    return EXIT_SUCCESS;
}

int find_in_array(char *filename, char *substr)
{
    struct object *items = NULL;
    FILE *f;
    long count = 0, i, cnt_found = 0;
    int flag;
    size_t string_length;

    f = fopen(filename, "r");
    if (f == NULL)
        return ERR_OPEN_FILE;
    flag = input_array(f, &items, &count);
    if (flag != EXIT_SUCCESS)
    {
        fclose(f);
        return flag;
    }
    string_length = strlen(substr);
    for (i = 0; i <= count; i++)
        if (strncmp(substr, items[i].name, string_length) == 0)
        {
            printf("%s\n", items[i].name);
            printf("%lf\n", items[i].mass);
            printf("%lf\n", items[i].volume);
            cnt_found += 1;
        }
    fclose(f);
    free_struct(&items, &count);
    free(items);
    if (cnt_found == 0)
        return ERR_BAD_DATA;
    else
        return EXIT_SUCCESS;
}

int input_array(FILE *f, struct object *items[], long *count)
{
    int flag = EXIT_SUCCESS;
    long i, num = count_structs(f);

    rewind(f);
    *items = calloc(num, sizeof(struct object));
    if (items == NULL)
        return ERR_MEMORY_ALLOCATION;
    flag = read_struct(f, &(*items)[*count]);
    if (flag == ERR_BAD_DATA || (*items)[*count].mass <= 0.0 || (*items)[*count].volume <= 0.0)
    {
        free((*items)[*count].name);
        free(*items);
        return ERR_BAD_DATA;
    }
    for (i = 1; i < num; i++)
    {
        *count += 1;
        flag = read_struct(f, &(*items)[*count]);
        if (flag == ERR_BAD_DATA || (*items)[*count].mass <= 0.0 || (*items)[*count].volume <= 0.0)
        {
            free_struct(items, count);
            free(*items);
            return ERR_BAD_DATA;
        }
    }
    return EXIT_SUCCESS;
}

int read_struct(FILE *f, struct object *tmp_item)
{
    size_t len = 0;
    long read;
    double m, v;

    read = getline_new(&(tmp_item->name), &len, f);
    if (read <= 0)
    {
        if (read == 0 && feof(f) != 0)
        {
            free(tmp_item->name);
            return EXIT_SUCCESS;
        }
        else
        {
            free(tmp_item->name);
            return ERR_BAD_DATA;
        }
    }
    if (fscanf(f, "%lf%*1[\n]", &m) != 1)
    {
        free(tmp_item->name);
        return ERR_BAD_DATA;
    }
    if (fscanf(f, "%lf%*1[\n]", &v) != 1)
    {
        free(tmp_item->name);
        return ERR_BAD_DATA;
    }
    tmp_item->mass = m;
    tmp_item->volume = v;
    return EXIT_SUCCESS;
}

int getline_new(char **lineptr, size_t *n, FILE *file)
{
    size_t max_l = 16, new_max_l = max_l;
    char *flag;
    char *ptr = NULL;
    size_t len;

    if (ferror(file))
        return -1;
    if (feof(file))
        return -1;
    *lineptr = (char*)calloc(max_l, sizeof(char));
    if (*lineptr == NULL)
    {
        return -1;
    }
    if (fgets(*lineptr, max_l, file) == NULL && feof(file) == 0)
    {
        free(*lineptr);
        if (feof(file) == 0)
            return 0;
        else
            return -1;
    }
    ptr = strchr(*lineptr, '\n');
    if (ptr != NULL)
        *ptr = '\0';
    len = strlen(*lineptr);
    if (ptr == NULL && len == max_l)
    {
        while (ptr == NULL && len == new_max_l - 1)
        {
            new_max_l *= 2;
            flag = (char*)realloc(*lineptr, new_max_l);
            if (flag == NULL)
            {
                free(*lineptr);
                return -1;
            }
            if (fgets((*lineptr + len), max_l + 1, file) == NULL)
            {
                free(*lineptr);
                return -1;
            }
            max_l *= 2;
            ptr = strchr(*lineptr, '\n');
            if (ptr != NULL)
                *ptr = '\0';
            len = strlen(*lineptr);
        }
    }
    flag = (char*)realloc(*lineptr, len + 1);
    if (flag == NULL)
    {
        free(*lineptr);
        return -1;
    }
    *n = len;
    return len;
}

void free_struct(struct object *items[], long *count)
{
    for (long i = 0; i <= *count; i++)
        free((*items)[i].name);
}

long count_structs(FILE *f)
{
    long count = 0;
    int buf;
    for (long i = 0; (buf = fgetc(f)) != EOF; i++)
        if (buf == '\n')
            count += 1;
    count /= 3;
    return count;
}

