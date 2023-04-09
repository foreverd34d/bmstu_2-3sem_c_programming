#ifndef CHECK_MAIN_H
#define CHECK_MAIN_H

#include <check.h>

#define DATADIR_PREFIX "unit_tests/data"

Suite *list_suite(void);
Suite *matrix_list_suite(void);
Suite *matrix_list_io_suite(void);
Suite *matrix_list_oper_suite(void);

#endif // !CHECK_MAIN_
