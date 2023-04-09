#include "matrix_list_oper.h"
#include "list.h"
#include "matrix_list.h"
#include <stdbool.h>

static size_t max(size_t a, size_t b)
{
    return a > b ? a : b;
}

mlist_t *matrix_addition(const mlist_t *mtr_a, const mlist_t *mtr_b)
{
    mlist_t *result = NULL;
    size_t rows_a = max(mlist_get_rows(mtr_a), mlist_get_rows(mtr_b));
    size_t cols_a = max(mlist_get_cols(mtr_a), mlist_get_cols(mtr_b));
    bool succeed = true;

    if (mtr_a && mtr_b)
    {
        result = mlist_create();
    }

    if (result)
    {
        for (size_t i = 0; succeed && i < rows_a; i++)
        {
            for (size_t j = 0; succeed && j < cols_a; j++)
            {
                unsigned long sum = mlist_find_value(mtr_a, i, j) + mlist_find_value(mtr_b, i, j);
                if (sum != 0)
                {
                    succeed = mlist_append_new_element(result, i, j, sum);
                }
            }
        }
    }

    if (!succeed)
    {
        mlist_free(result);
        result = NULL;
    }

    return result;
}

mlist_t *matrix_multiplication(const mlist_t *mtr_a, const mlist_t *mtr_b)
{
    mlist_t *result = NULL;

    size_t rows_a = mlist_get_rows(mtr_a);
    size_t cols_b = mlist_get_cols(mtr_b);
    size_t cols_a = mlist_get_cols(mtr_a);

    bool succeed = true;

    if (mtr_a && mtr_b)
    {
        result = mlist_create();
    }

    if (result)
    {
        for (size_t i = 0; succeed && i < rows_a; i++)
        {
            for (size_t j = 0; succeed && j < cols_b; j++)
            {
                unsigned long mul = 0;

                for (size_t k = 0; succeed && k < cols_a; k++)
                {
                    mul += mlist_find_value(mtr_a, i, k) * mlist_find_value(mtr_b, k, j);
                }

                if (mul != 0)
                {
                    succeed = mlist_append_new_element(result, i, j, mul);
                }
            }
        }
    }

    if (!succeed)
    {
        mlist_free(result);
        result = NULL;
    }

    return result;
}

bool matrix_rm_max_row(mlist_t *mtr)
{
    bool deleted = false;
    if (mtr && mlist_get_rows(mtr) > 1)
    {
        ssize_t max_row = mlist_find_max_row(mtr);
        if (max_row >= 0)
        {
            deleted = mlist_rm_row(mtr, max_row);
        }
    }
    return deleted;
}
