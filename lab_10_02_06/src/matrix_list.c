#include "matrix_list.h"
#include "list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>

struct matrix_node
{
    size_t row;
    size_t col;
    unsigned long val;
};

struct matrix_list
{
    node_t *head;
};

mnode_t *mnode_create(size_t row, size_t col, unsigned long val)
{
    mnode_t *new = malloc(sizeof(mnode_t));
    if (new)
    {
        new->row = row;
        new->col = col;
        new->val = val;
    }
    return new;
}

mlist_t *mlist_create(void)
{
    mlist_t *new = malloc(sizeof(mlist_t));
    if (new)
    {
        new->head = NULL;
    }
    return new;
}

void mlist_free(mlist_t *list)
{
    if (list)
    {
        list_free(list->head, (void (*)(void *)) mnode_free);
        free(list);
    }
}

void mnode_free(mnode_t *node)
{
    free(node);
}

unsigned long mlist_find_value(const mlist_t *list, size_t row, size_t col)
{
    unsigned long value = 0;
    for (node_t *node = list->head; !value && node; node = node_get_next(node))
    {
        mnode_t *elem = node_get_data(node);
        if (elem->row == row && elem->col == col)
        {
            value = elem->val;
        }
    }
    return value;
}

static node_t *mnode_list_create(size_t row, size_t col, unsigned long val)
{
    mnode_t *new_elem = mnode_create(row, col, val);
    node_t *new_node = node_create(new_elem);
    if (!new_elem || !new_node)
    {
        mnode_free(new_elem);
        list_free(new_node, NULL);
        new_node = NULL;
    }
    return new_node;
}

bool mlist_append_new_element(mlist_t *list, size_t row, size_t col, unsigned long val)
{
    bool succeed = true;
    node_t *new = mnode_list_create(row, col, val);
    if (!new)
    {
        succeed = false;
    }
    else
    {
        append(&list->head, &new);
    }
    return succeed;
}

ssize_t mlist_find_max_row(mlist_t *list)
{
    ssize_t max_row = -1;

    if (list)
    {
        mnode_t *head_elem = node_get_data(list->head);
        unsigned long min_val = mlist_get_nonnull_len(list) == mlist_get_rows(list) * mlist_get_cols(list) ? head_elem->val : 0;
        unsigned long max_val = head_elem->val;
        max_row = 0;

        for (node_t *node = list->head; node; node = node_get_next(node))
        {
            mnode_t *elem = node_get_data(node);
            if (elem->val > max_val)
            {
                max_row = elem->row;
                max_val = elem->val;
            }
            else if (elem->val < min_val)
            {
                min_val = elem->val;
            }
        }

        if (max_val == min_val)
        {
            max_row = -1;
        }
    }

    return max_row;
}

int mnode_row_comparator(const void *a, const void *b)
{
    const mnode_t *x = a;
    const size_t *y = b;
    return x->row - *y;
}

bool mlist_rm_row(mlist_t *list, size_t row)
{
    bool deleted = false;
    mnode_t *data = NULL;

    while ((data = list_pop_node(&list->head, find(list->head, &row, mnode_row_comparator))))
    {
        mnode_free(data);
        deleted += true;
    }

    return deleted;
}

size_t mnode_get_row(const mnode_t *node)
{
    return node ? node->row : 0;
}

size_t mnode_get_col(const mnode_t *node)
{
    return node ? node->col : 0;
}

unsigned long mnode_get_val(const mnode_t *node)
{
    return node ? node->val : 0;
}

size_t mlist_get_rows(const mlist_t *list)
{
    // return list ? list->rows : 0;
    size_t max_row = 0;
    if (list)
    {
        for (node_t *cur = list->head; cur; cur = node_get_next(cur))
        {
            size_t cur_row = mnode_get_row(node_get_data(cur));
            if (cur_row > max_row)
            {
                max_row = cur_row;
            }
        }
        max_row++;
    }
    return max_row;
}

size_t mlist_get_cols(const mlist_t *list)
{
    // return list ? list->cols : 0;
    size_t max_col = 0;
    if (list)
    {
        for (node_t *cur = list->head; cur; cur = node_get_next(cur))
        {
            size_t cur_col = mnode_get_col(node_get_data(cur));
            if (cur_col > max_col)
            {
                max_col = cur_col;
            }
        }
        max_col++;
    }
    return max_col;
}

node_t *mlist_get_head(const mlist_t *list)
{
    return list ? list->head : NULL;
}

size_t mlist_get_nonnull_len(const mlist_t *list)
{
    return list ? list_len(list->head) : 0;
}
