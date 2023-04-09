#include <check.h>

#include "check_main.h"
#include "items.h"

int main(void)
{
    SRunner *runner = srunner_create(item_utils_suite());
    srunner_add_suite(runner, items_suite());
    srunner_add_suite(runner, tools_suite());
    srunner_add_suite(runner, item_io_suite());

    srunner_run_all(runner, CK_VERBOSE);

    int failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return failed;
}

void assert_item_eq(item_t a, item_t b)
{
    ck_assert_str_eq(a.name, b.name);
    ck_assert_double_eq_tol(a.weight, b.weight, EPS);
    ck_assert_double_eq_tol(a.volume, b.volume, EPS);
}

void assert_items_arr_eq(item_t *a, item_t *b, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        assert_item_eq(a[i], b[i]);
    }
}
