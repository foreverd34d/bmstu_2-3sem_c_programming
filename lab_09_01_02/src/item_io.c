#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "error_codes.h"
#include "item_io.h"
#include "items.h"
#include "tools.h"

static int fill_items(item_t **items, FILE *f)
{
    int read_fields = 0;
    bool err = false;

    item_t item;
    item.name = NULL;
    char *buffer = NULL;
    size_t bufsize = 0;

    for (; !err && getline(&buffer, &bufsize, f) != -1; read_fields++)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        int cur_field = read_fields % 3;

        if (cur_field == 0)
        {
            err = !item_set_name(&item, buffer);
        }
        else
        {
            double num;
            if (read_pos_double(&num, buffer) != 0)
            {
                err = true;
            }
            else
            {
                if (cur_field == 1)
                {
                    item.weight = num;
                }
                else
                {
                    item.volume = num;
                    (*items)[read_fields / 3] = item;
                    item.name = NULL;
                }
            }
        }

        if (err)
        {
            free(item.name);
        }
    }

    free(buffer);

    if (err)
    {
        read_fields = -1;
    }

    return read_fields;
}

int read_items_file(item_t **dest, FILE *from)
{
    int read_fields = 0;
    item_t *items = NULL;

    size_t lines = get_lines_amount(from);
    rewind(from);

    if (lines != 0 && lines % 3 == 0)
    {
        items = calloc(lines / 3, sizeof(item_t));
        if (items)
        {
            read_fields = fill_items(&items, from);
        }
    }

    int read_structs = -1;
    if (read_fields % 3 != 0 || read_fields == 0)
    {
        items_free(&items, lines / 3);
    }
    else
    {
        free(*dest);
        *dest = items;
        read_structs = read_fields / 3;
    }

    return read_structs;
}

size_t get_lines_amount(FILE *f)
{
    size_t lines = 0;
    char *buffer = NULL;
    size_t buffer_size = 0;

    while (getline(&buffer, &buffer_size, f) != -1)
    {
        lines++;
    }

    free(buffer);
    return lines;
}

void print_items_file(const item_t *items, int len, FILE *to)
{
    for (const item_t *item = items; item < items + len; item++)
    {
        fprintf(to, "%s\n%lf\n%lf\n", item->name, item->weight, item->volume);
    }
}
