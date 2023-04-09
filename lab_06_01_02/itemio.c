#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "items.h"

int read_items(item_t *dest, FILE *from)
{
    int read_fields = 0;
    int err = 0;
    item_t item;
    for (char buffer[NAMEMAX + 2]; !err && fgets(buffer, NAMEMAX + 2, from); read_fields++)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        int cur_field = read_fields % 3;
        if (read_fields > STRUCTMAX * 3)
        {
            err = 1;
        }
        else if (cur_field == 0)
        {
            int buflen = strlen(buffer);
            if (buflen <= 0 || buflen > NAMEMAX || is_empty(buffer))
            {
                err = 1;
            }
            else
            {
                strcpy(item.name, buffer);
            }
        }
        else
        {
            double num;
            if (read_pos_double(&num, buffer) != 0)
            {
                err = 1;
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
                    dest[read_fields / 3] = item;
                }
            }
        }
    }

    if (err || read_fields % 3 != 0)
    {
        read_fields = -1;
    }

    return read_fields / 3;
}

void print_items(const item_t *items, int len)
{
    for (const item_t *item = items; item < items + len; item++)
    {
        printf("%s\n%lf\n%lf\n", item->name, item->weight, item->volume);
    }
}
