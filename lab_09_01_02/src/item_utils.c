#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "error_codes.h"
#include "items.h"
#include "item_utils.h"
#include "tools.h"

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

static bool duplicate_filtered(item_t *items_dst, size_t *items_dst_len, const item_t *items_src, size_t items_src_len, const char *prefix)
{
    bool copy_all = false;
    bool mem_err = false;

    if (strcmp(prefix, "ALL") == 0)
    {
        copy_all = true;
    }

    for (size_t i = 0; !mem_err && i < items_src_len; i++)
    {
        if (copy_all || starts_with(items_src[i].name, prefix))
        {
            item_t new_item;
            if (item_duplicate(&new_item, items_src[i]) != OK)
            {
                mem_err = true;
            }
            else
            {
                items_dst[(*items_dst_len)++] = new_item;
            }
        }
    }

    return mem_err;
}

int filter_by_prefix(item_t **items_dst, size_t items_dst_len, const item_t *items_src, size_t items_src_len, const char *prefix)
{
    int items_new_len = 0;
    bool mem_err = false;

    item_t *items_new = calloc(items_src_len, sizeof(item_t));
    if (items_new == NULL)
    {
        mem_err = true;
    }
    else
    {
        size_t new_len = 0;
        mem_err = duplicate_filtered(items_new, &new_len, items_src, items_src_len, prefix);
        items_new_len = new_len;
    }

    if (mem_err)
    {
        items_free(&items_new, items_src_len);
        items_new_len = -1;
    }
    else
    {
        items_free(items_dst, items_dst_len);
        *items_dst = items_new;
    }

    return items_new_len;
}
