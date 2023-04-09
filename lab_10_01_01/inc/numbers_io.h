#ifndef NUMBERS_IO_H
#define NUMBERS_IO_H

#include "list.h"
#include <stdio.h>
#include <stdbool.h>

node_t *read_num_list_file(FILE *f);
void print_num_list_file(FILE *f, node_t *list_head);
int numbers_comparator(const void *a, const void *b);
bool read_int_str(int *value, const char *str);

#endif // !NUMBERS_IO_H
