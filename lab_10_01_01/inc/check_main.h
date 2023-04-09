#ifndef CHECK_MAIN_H
#define CHECK_MAIN_H

#include <check.h>

#define DATADIR_PREFIX "unit_tests/data"

Suite *list_suite(void);
Suite *numbers_io_suite(void);

#endif // !CHECK_MAIN_
