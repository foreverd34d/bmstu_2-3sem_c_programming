#ifndef ITEM_IO_H
#define ITEM_IO_H

#include <stdio.h>
#include "items.h"

int read_items_file(item_t **dest, FILE *from);
size_t get_lines_amount(FILE *f);
void print_items_file(const item_t *items, int len, FILE *to);

#endif // !ITEM_IO_H
