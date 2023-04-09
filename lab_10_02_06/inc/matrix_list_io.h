#ifndef MATRIX_LIST_IO_H
#define MATRIX_LIST_IO_H

#include "matrix_list.h"
#include <stdbool.h>
#include <stdio.h>

mlist_t *read_mlist_file(FILE *f);
void print_mlist_file(FILE *f, mlist_t *matrix);

#endif // !MATRIX_LIST_IO_H
