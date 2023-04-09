#include "check_main.h"
#include <check.h>

int main(void)
{
    SRunner *r = srunner_create(list_suite());
    srunner_add_suite(r, matrix_list_suite());
    srunner_add_suite(r, matrix_list_io_suite());
    srunner_add_suite(r, matrix_list_oper_suite());

    srunner_run_all(r, CK_VERBOSE);

    int failed = srunner_ntests_failed(r);

    srunner_free(r);

    return failed;
}
