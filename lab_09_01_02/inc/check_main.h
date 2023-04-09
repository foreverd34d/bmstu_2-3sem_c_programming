#ifndef CHECK_MAIN_H
#define CHECK_MAIN_H

#include <check.h>
#include "items.h"

#define EPS 1e-5
#define DATADIR_PREFIX "unit_tests/data"

void assert_item_eq(item_t a, item_t b);
void assert_items_arr_eq(item_t *a, item_t *b, size_t len);

Suite *item_utils_suite(void);
Suite *items_suite(void);
Suite *tools_suite(void);
Suite *item_io_suite(void);

#endif // !CHECK_MAIN_H
