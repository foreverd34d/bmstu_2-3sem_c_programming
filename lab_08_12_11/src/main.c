#include <stdio.h>
#include <string.h>

#include "error_codes.h"
#include "matrix.h"
#include "matrix_io.h"
#include "matrix_operations.h"

err_t action_determinant(const char *matrix_name, const char *result_name);
err_t action_binary_operation(const char *first_matrix_name, const char *second_matrix_name, const char *result_name,
matrix_t *(*operation)(const matrix_t *, const matrix_t *));

int main(int argc, char **argv)
{
    err_t err = OK;

    if (argc == 5)
    {
        if (strcmp(argv[1], "a") == 0)
        {
            err = action_binary_operation(argv[2], argv[3], argv[4], matrix_addition);
        }
        else if (strcmp(argv[1], "m") == 0)
        {
            err = action_binary_operation(argv[2], argv[3], argv[4], matrix_multiplication);
        }
        else
        {
            err = ERR_ARGS;
        }
    }
    else if (argc == 4 && strcmp(argv[1], "o") == 0)
    {
        err = action_determinant(argv[2], argv[3]);
    }
    else
    {
        err = ERR_ARGS;
    }

    return err;
}

err_t action_binary_operation(const char *first_matrix_name, const char *second_matrix_name, const char *result_name,
matrix_t *(*operation)(const matrix_t *, const matrix_t *))
{
    err_t err = OK;

    FILE *first_matrix_file = fopen(first_matrix_name, "r");
    FILE *second_matrix_file = fopen(second_matrix_name, "r");
    FILE *result_file = fopen(result_name, "w");

    if (first_matrix_file != NULL && second_matrix_file != NULL && result_file != NULL)
    {
        matrix_t *matrix_one = NULL;
        matrix_t *matrix_two = NULL;

        if (read_matrix_file(&matrix_one, first_matrix_file) == OK &&
            read_matrix_file(&matrix_two, second_matrix_file) == OK)
        {
            matrix_t *matrix_operation_result = operation(matrix_one, matrix_two);

            if (matrix_operation_result != NULL)
            {
                print_matrix_file(matrix_operation_result, result_file);
            }
            else
            {
                err = ERR_MATRIX_INCOMPATIBLE;
            }

            matrix_free(&matrix_operation_result);
        }
        else
        {
            err = ERR_FILE_READ;
        }

        matrix_free(&matrix_one);
        matrix_free(&matrix_two);
        fclose(first_matrix_file);
        fclose(second_matrix_file);
        fclose(result_file);
    }
    else
    {
        if (first_matrix_file != NULL)
        {
            fclose(first_matrix_file);
        }

        if (second_matrix_file != NULL)
        {
            fclose(second_matrix_file);
        }

        if (result_file != NULL)
        {
            fclose(result_file);
        }

        err = ERR_FILE_OPEN;
    }

    return err;
}

err_t action_determinant(const char *matrix_name, const char *result_name)
{
    err_t err = OK;

    FILE *matrix_file = fopen(matrix_name, "r");
    FILE *result_file = fopen(result_name, "w");

    if (matrix_file != NULL && result_file != NULL)
    {
        matrix_t *matrix = NULL;
        if (read_matrix_file(&matrix, matrix_file) != OK)
        {
            err = ERR_FILE_READ;
        }
        else if (matrix->rows != matrix->columns)
        {
            err = ERR_MATRIX_INCOMPATIBLE;
        }
        else
        {
            matrix_el_t determinant = matrix_determinant(matrix);
            fprintf(result_file, MATRIX_EL_FMT "\n", determinant);
        }

        fclose(matrix_file);
        fclose(result_file);
        matrix_free(&matrix);
    }
    else
    {
        if (matrix_file != NULL)
        {
            fclose(matrix_file);
        }

        if (result_file != NULL)
        {
            fclose(result_file);
        }

        err = ERR_FILE_OPEN;
    }

    return err;
}
