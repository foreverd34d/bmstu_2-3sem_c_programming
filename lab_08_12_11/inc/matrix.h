#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

#define MATRIX_EL_FMT "%lf"

typedef double matrix_el_t;

typedef struct matrix
{
    matrix_el_t **data;
    size_t rows;
    size_t columns;
} matrix_t;

matrix_t *matrix_create(size_t rows, size_t columns);
void matrix_free(matrix_t **matrix);

#endif // !MATRIX_H
