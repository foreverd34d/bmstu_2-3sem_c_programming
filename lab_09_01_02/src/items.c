#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "error_codes.h"
#include "items.h"
#include "tools.h"

int item_duplicate(item_t *dst, item_t src)
{
    int err = OK;
    char *name = strdup(src.name);
    if (name == NULL)
    {
        err = ERR_MEM;
    }
    else
    {
        dst->name = name;
        dst->volume = src.volume;
        dst->weight = src.weight;
    }
    return err;
}

void items_free(item_t **items, size_t len)
{
    if (*items != NULL)
    {
        for (item_t *item = *items; item < *items + len; item++)
        {
            free(item->name);
        }
    }
    free(*items);
    *items = NULL;
}

bool item_set_name(item_t *item, const char *name)
{
    bool succeed = true;
    if (!name || !item || strlen(name) <= 0 || is_empty(name))
    {
        succeed = false;
    }
    else
    {
        char *new_name = strdup(name);
        if (name == NULL)
        {
            succeed = false;
        }
        else
        {
            free(item->name);
            item->name = new_name;
        }
    }
    return succeed;
}
