#include <math.h>
#include <stdbool.h>

#include "matrix.h"
#include "matrix_operations.h"

matrix_t *matrix_addition(const matrix_t *matrix_a, const matrix_t *matrix_b)
{
    matrix_t *matrix_result = NULL;
    if (matrix_a->rows == matrix_b->rows && matrix_a->columns == matrix_b->columns)
    {
        matrix_result = matrix_create(matrix_a->rows, matrix_a->columns);
    }

    if (matrix_result != NULL)
    {
        for (size_t i = 0; i < matrix_a->rows; i++)
        {
            for (size_t j = 0; j < matrix_a->columns; j++)
            {
                matrix_result->data[i][j] = matrix_a->data[i][j] + matrix_b->data[i][j];
            }
        }
    }

    return matrix_result;
}

matrix_t *matrix_multiplication(const matrix_t *matrix_a, const matrix_t *matrix_b)
{
    matrix_t *matrix_result = NULL;
    if (matrix_a->columns == matrix_b->rows)
    {
        matrix_result = matrix_create(matrix_a->rows, matrix_b->columns);
    }

    if (matrix_result != NULL)
    {
        for (size_t i = 0; i < matrix_a->rows; i++)
        {
            for (size_t j = 0; j < matrix_b->columns; j++)
            {
                for (size_t s = 0; s < matrix_a->columns; s++)
                {
                    matrix_result->data[i][j] += matrix_a->data[i][s] * matrix_b->data[s][j];
                }
            }
        }
    }

    return matrix_result;
}

matrix_el_t matrix_determinant(const matrix_t *matrix)
{
    if (matrix->rows == 1)
    {
        return matrix->data[0][0];
    }
    else if (matrix->rows == 2)
    {
        return matrix->data[0][0] * matrix->data[1][1] - matrix->data[0][1] * matrix->data[1][0];
    }
    else
    {
        bool mem_error = false;
        matrix_el_t determinant = 0;
        for (size_t k = 0; !mem_error && k < matrix->rows; k++)
        {
            matrix_t *submatrix = matrix_minor(matrix, 0, k);
            if (submatrix != NULL)
            {
                determinant += pow(-1, k + 2) * matrix->data[0][k] * matrix_determinant(submatrix);
                matrix_free(&submatrix);
            }
        }
        return determinant;
    }
}

matrix_t *matrix_minor(const matrix_t *matrix, size_t row, size_t column)
{
    matrix_t *minor = matrix_create(matrix->rows - 1, matrix->rows - 1);
    if (minor != NULL)
    {
        size_t row_offset = 0;
        size_t column_offset = 0;
        for (size_t i = 0; i < matrix->rows - 1; i++)
        {
            if (i == row)
            {
                row_offset = 1;
            }

            column_offset = 0;
            for (size_t j = 0; j < matrix->rows - 1; j++)
            {
                if (j == column)
                {
                    column_offset = 1;
                }

                minor->data[i][j] = matrix->data[i + row_offset][j + column_offset];
            }
        }
    }
    return minor;
}
