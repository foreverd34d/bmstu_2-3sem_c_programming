#ifndef MATRIXIO_H
#define MATRIXIO_H

#include <stddef.h>
#include <stdio.h>

#include "error_codes.h"
#include "matrix.h"

#define ERR_FILE_OPEN 10
#define ERR_FILE_READ 11

err_t read_matrix_file(matrix_t **dst_matrix_ptr, FILE *src_file);
void print_matrix_file(const matrix_t *matrix, FILE *dest_file);

#endif // !MATRIXIO_H
