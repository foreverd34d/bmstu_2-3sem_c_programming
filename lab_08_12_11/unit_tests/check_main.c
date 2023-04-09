#include <check.h>

#include "check_main.h"

int main(void)
{
    SRunner *runner = srunner_create(matrix_operations_suite());
    srunner_add_suite(runner, matrix_suite());
    srunner_add_suite(runner, matrix_io_suite());

    srunner_run_all(runner, CK_VERBOSE);

    int failed = srunner_ntests_failed(runner);

    srunner_free(runner);
    return failed;
}
