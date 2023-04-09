#include <check.h>
#include "../inc/check_main.h"

int main(void)
{
    SRunner *runner = srunner_create(numsort_suite());
    srunner_add_suite(runner, numkey_suite());
    srunner_add_suite(runner, numio_suite());

    srunner_run_all(runner, CK_VERBOSE);

    int failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return failed;
}
