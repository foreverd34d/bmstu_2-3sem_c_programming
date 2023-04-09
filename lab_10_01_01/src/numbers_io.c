#include "numbers_io.h"
#include "list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

node_t *read_num_list_file(FILE *f)
{
    node_t *result = NULL;

    int num;
    bool mem_err = false;

    while (fscanf(f, "%d", &num) == 1 && !mem_err)
    {
        int *value = malloc(sizeof(int));
        node_t *new = node_create(value);

        if (!value || !new)
        {
            free(value);
            list_free(new, NULL);
            mem_err = true;
        }
        else
        {
            *value = num;
            append(&result, &new);
        }
    }

    if (mem_err || !feof(f))
    {
        list_free(result, free);
        result = NULL;
    }

    return result;
}

void print_num_list_file(FILE *f, node_t *list_head)
{
    for (; list_head; list_head = node_get_next(list_head))
    {
        fprintf(f, "%d\n", *((int *)node_get_data(list_head)));
    }
}

int numbers_comparator(const void *a, const void *b)
{
    return *((int *)a) - *((int *)b);
}

bool read_int_str(int *value, const char *str)
{
    bool succeed = false;
    char *after = NULL;

    int value_read = strtol(str, &after, 10);

    if (!*after && (isdigit(str[0]) || isdigit(str[1])))
    {
        *value = value_read;
        succeed = true;
    }

    return succeed;
}
