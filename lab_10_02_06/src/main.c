#include "matrix_list.h"
#include "matrix_list_io.h"
#include "matrix_list_oper.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK          0
#define ERR_ARGS    1

#define ERR_MATRIX_READ     10
#define ERR_MATRIX_INCOP    11
#define ERR_MATRIX_NORES    12

typedef enum
{
    ERR,
    OUT,
    ADD,
    MUL,
    LIN
} action_t;

action_t read_action(FILE *f);

int action_add(void);
int action_multiply(void);
int action_print(void);
int action_rm_max_row(void);

int main(void)
{
    int error_code = OK;
    action_t action = read_action(stdin);

    switch (action)
    {
        case OUT:
            error_code = action_print();
            break;
        case ADD:
            error_code = action_add();
            break;
        case MUL:
            error_code = action_multiply();
            break;
        case LIN:
            error_code = action_rm_max_row();
            break;
        case ERR:
            error_code = ERR_ARGS;
            break;
    }

    return error_code;
}

action_t read_action(FILE *f)
{
    action_t action = ERR;
    char *buffer = NULL;
    size_t bufsize = 0;

    if (getline(&buffer, &bufsize, f) != -1)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        action = !strcmp(buffer, "out") ? OUT : !strcmp(buffer, "add") ? ADD : !strcmp(buffer, "mul") ? MUL : !strcmp(buffer, "lin") ? LIN : ERR;
    }

    free(buffer);

    return action;
}

static int add_or_multiply(mlist_t *(*func)(const mlist_t *, const mlist_t *))
{
    int err = OK;

    mlist_t *matrix_a = NULL;
    mlist_t *matrix_b = NULL;
    mlist_t *result = NULL;

    if (!(matrix_a = read_mlist_file(stdin)) || !(matrix_b = read_mlist_file(stdin)))
    {
        err = ERR_MATRIX_READ;
    }
    else
    {
        result = func(matrix_a, matrix_b);
        if (!result)
        {
            err = ERR_MATRIX_INCOP;
        }
        else if (!mlist_get_head(result))
        {
            err = ERR_MATRIX_NORES;
        }
    }

    if (!err)
    {
        print_mlist_file(stdout, result);
    }

    mlist_free(matrix_a);
    mlist_free(matrix_b);
    mlist_free(result);

    return err;
}

int action_add(void)
{
    return add_or_multiply(matrix_addition);
}

int action_multiply(void)
{
    return add_or_multiply(matrix_multiplication);
}

static int print_or_process(bool (*func)(mlist_t *))
{
    int err = OK;

    mlist_t *matrix = read_mlist_file(stdin);

    if (!matrix)
    {
        err = ERR_MATRIX_READ;
    }
    else if (func && !func(matrix))
    {
        err = ERR_MATRIX_NORES;
    }

    if (!mlist_get_head(matrix))
    {
        err = ERR_MATRIX_NORES;
    }

    if (!err)
    {
        print_mlist_file(stdout, matrix);
    }

    mlist_free(matrix);

    return err;
}

int action_print(void)
{
    return print_or_process(NULL);
}

int action_rm_max_row(void)
{
    return print_or_process(matrix_rm_max_row);
}
