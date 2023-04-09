#include <stdlib.h>

#include "matrix.h"

matrix_t *matrix_create(size_t rows, size_t columns)
{
    matrix_t *matrix = NULL;
    if (rows > 0 && columns > 0)
    {
        matrix = malloc(sizeof(matrix_t));
        matrix_el_t **temp_data = calloc(1, rows * sizeof(matrix_el_t *) + rows * columns * sizeof(matrix_el_t));

        if (matrix != NULL && temp_data != NULL)
        {
            for (size_t i = 0; i < rows; i++)
            {
                temp_data[i] = (matrix_el_t *) ((char *)temp_data + rows * sizeof(matrix_el_t *) +
                    i * columns * sizeof(matrix_el_t));
            }
            matrix->data = temp_data;
            matrix->rows = rows;
            matrix->columns = columns;
        }
        else
        {
            free(matrix);
            free(temp_data);
            matrix = NULL;
        }
    }

    return matrix;
}

void matrix_free(matrix_t **matrix_ptr)
{
    if (*matrix_ptr != NULL)
    {
        free((*matrix_ptr)->data);
    }
    free(*matrix_ptr);
    *matrix_ptr = NULL;
}
