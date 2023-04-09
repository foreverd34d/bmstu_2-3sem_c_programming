#ifndef MATRIX_LIST_OPER_H
#define MATRIX_LIST_OPER_H

#include "matrix_list.h"

mlist_t *matrix_addition(const mlist_t *mtr_a, const mlist_t *mtr_b);
mlist_t *matrix_multiplication(const mlist_t *mtr_a, const mlist_t *mtr_b);
bool matrix_rm_max_row(mlist_t *mtr);

#endif // !MATRIX_LIST_OPER_H
