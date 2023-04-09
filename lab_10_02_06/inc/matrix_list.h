#ifndef MATRIX_LIST_H
#define MATRIX_LIST_H

#include "list.h"
#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

typedef struct matrix_node mnode_t;
typedef struct matrix_list mlist_t;

mnode_t *mnode_create(size_t row, size_t col, unsigned long val);
mlist_t *mlist_create(void);

void mnode_free(mnode_t *node);
void mlist_free(mlist_t *list);

unsigned long mlist_find_value(const mlist_t *list, size_t row, size_t col);
ssize_t mlist_find_max_row(mlist_t *list);
bool mlist_rm_row(mlist_t *list, size_t row);

int mnode_row_comparator(const void *a, const void *b);
bool mlist_append_new_element(mlist_t *list, size_t row, size_t col, unsigned long val);

size_t mnode_get_row(const mnode_t *node);
size_t mnode_get_col(const mnode_t *node);
unsigned long mnode_get_val(const mnode_t *node);

size_t mlist_get_rows(const mlist_t *list);
size_t mlist_get_cols(const mlist_t *list);
node_t *mlist_get_head(const mlist_t *list);
size_t mlist_get_nonnull_len(const mlist_t *list);

#endif // !MATRIX_LIST_H
