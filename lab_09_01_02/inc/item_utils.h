#ifndef ITEM_UTILS_H
#define ITEM_UTILS_H

#include "items.h"

void sort_by_density(item_t *items, int len);
double get_density(item_t item);
void swap_items(item_t *a, item_t *b);
int filter_by_prefix(item_t **items_dst, size_t items_dst_len, const item_t *items_src, size_t items_src_len, const char *prefix);

#endif // !ITEM_UTILS_H
