#include <string.h>
#include <stdbool.h>
#include "items.h"

void sort_by_density(item_t *items, int len)
{
    for (int i = 1; i < len; i++)
    {
        for (int j = i; j > 0 && get_density(items[j - 1]) > get_density(items[j]); j--)
        {
            swap_items(items + j - 1, items + j);
        }
    }
}

double get_density(item_t item)
{
    return item.weight / item.volume;
}

void swap_items(item_t *a, item_t *b)
{
    item_t buf = *a;
    *a = *b;
    *b = buf;
}

int filter_by_prefix(item_t *items, int len, const char *prefix)
{
    int newlen = len;
    if (strcmp(prefix, "ALL") != 0)
    {
        newlen = 0;
        for (item_t *item = items; item < items + len; item++)
        {
            if (starts_with(item->name, prefix))
            {
                items[newlen++] = *item;
            }
        }
    }
    return newlen;
}
