#include "matrix_list_io.h"
#include "list.h"
#include "matrix_list.h"
#include <stdbool.h>

static bool read_elements_file(FILE *f, mlist_t *mtr, size_t rows, size_t cols)
{
    bool succeed = true;
    size_t elements_read = 0;

    for (size_t i = 0; succeed && i < rows; i++)
    {
        long val;
        for (size_t j = 0; succeed && j < cols && fscanf(f, "%ld", &val) == 1; j++)
        {
            if (val < 0)
            {
                succeed = false;
            }
            else if (val != 0)
            {
                succeed = mlist_append_new_element(mtr, i, j, val);
            }
            elements_read++;
        }
    }

    // Check if there's a lack of numbers
    if (elements_read != rows * cols)
    {
        succeed = false;
    }

    return succeed;
}

mlist_t *read_mlist_file(FILE *f)
{
    mlist_t *new = NULL;
    bool succeed = true;
    long rows_read, cols_read;

    if (fscanf(f, "%ld%ld", &rows_read, &cols_read) == 2 && rows_read > 0 && cols_read > 0)
    {
        new = mlist_create();
        if (new)
        {
            succeed = read_elements_file(f, new, rows_read, cols_read);
        }
    }

    if (!succeed)
    {
        mlist_free(new);
        new = NULL;
    }

    return new;
}

void print_mlist_file(FILE *f, mlist_t *matrix)
{
    for (node_t *cur = mlist_get_head(matrix); cur; cur = node_get_next(cur))
    {
        mnode_t *node = node_get_data(cur);
        fprintf(f, "%zu %zu %lu ", mnode_get_row(node), mnode_get_col(node), mnode_get_val(node));
    }
    fprintf(f, "\n");
}
