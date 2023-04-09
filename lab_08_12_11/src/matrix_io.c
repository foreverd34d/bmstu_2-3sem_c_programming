#include <stdio.h>

#include "error_codes.h"
#include "matrix.h"
#include "matrix_io.h"

err_t read_matrix_file(matrix_t **dst_matrix_ptr, FILE *src_file)
{
    err_t err = OK;
    long rows_read, columns_read;
    matrix_t *matrix = NULL;

    if (fscanf(src_file, "%ld%ld", &rows_read, &columns_read) == 2 && rows_read > 0 && columns_read > 0)
    {
        size_t rows = rows_read;
        size_t columns = columns_read;

        matrix = matrix_create(rows, columns);
        if (matrix != NULL)
        {
            matrix->rows = rows;
            matrix->columns = columns;

            size_t numbers_read = 0;
            matrix_el_t number_current;

            for (size_t i = 0; i < rows; i++)
            {
                for (size_t j = 0; j < columns && fscanf(src_file, MATRIX_EL_FMT, &number_current) == 1; j++)
                {
                    matrix->data[i][j] = number_current;
                    numbers_read++;
                }
            }

            // Check if there're unread numbers or if there's a lack of numbers
            fscanf(src_file, MATRIX_EL_FMT, &number_current);
            if (!feof(src_file) || numbers_read != rows * columns)
            {
                err = ERR_FILE_READ;
            }
        }
        else
        {
            err = ERR_MEM;
        }
    }
    else
    {
        err = ERR_FILE_READ;
    }

    if (!err)
    {
        matrix_free(dst_matrix_ptr);
        *dst_matrix_ptr = matrix;
    }
    else
    {
        matrix_free(&matrix);
    }

    return err;
}

void print_matrix_file(const matrix_t *matrix, FILE *dest_file)
{
    fprintf(dest_file, "%zu %zu\n", matrix->rows, matrix->columns);
    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->columns; j++)
        {
            fprintf(dest_file, MATRIX_EL_FMT " ", matrix->data[i][j]);
        }
        fprintf(dest_file, "\n");
    }
}
