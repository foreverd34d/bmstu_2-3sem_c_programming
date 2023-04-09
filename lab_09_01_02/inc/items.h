#ifndef ITEMS_H
#define ITEMS_H

#include <stdbool.h>
#include <stddef.h>

typedef struct item_t
{
    char *name;
    double weight;
    double volume;
} item_t;

int item_duplicate(item_t *dst, item_t src);
void items_free(item_t **items, size_t len);

bool item_set_name(item_t *item, const char *name);

#endif // !ITEMS_H
