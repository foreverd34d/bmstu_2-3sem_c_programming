#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "matrix.h"

#define ERR_MATRIX_INCOMPATIBLE 20

matrix_t *matrix_addition(const matrix_t *matrix_a, const matrix_t *matrix_b);
matrix_t *matrix_multiplication(const matrix_t *matrix_a, const matrix_t *matrix_b);

matrix_el_t matrix_determinant(const matrix_t *matrix);
matrix_t *matrix_minor(const matrix_t *matrix, size_t row, size_t column);

#endif // !MATRIX_OPERATIONS_H
