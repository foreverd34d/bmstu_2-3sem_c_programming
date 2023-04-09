#ifndef NUMIO_H
#define NUMIO_H

#include <stdio.h>
#include "../inc/errcodes.h"

#define ERR_FILE_OPEN   10
#define ERR_FILE_READ   11
#define ERR_FILE_EMPTY  12

int read_numbers_file(int **dest_b, int **dest_e, FILE *from);
int get_numbers_amount(FILE *f);
void get_numbers_file(int *dest_b, int *dest_e, FILE *from);
void print_numbers_file(int *src_b, int *src_e, FILE *dest);

#endif // !NUMIO_H
