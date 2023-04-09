#include <check.h>

#include "check_main.h"
#include "matrix.h"

//
// matrix_create positives
//

START_TEST(create_matrix_pos_1x1)
{
    size_t rows = 1;
    size_t columns = 1;
    matrix_t *matrix = matrix_create(rows, columns);

    ck_assert_ptr_nonnull(matrix);
    ck_assert_ptr_nonnull(matrix->data);
    ck_assert_uint_eq(matrix->rows, rows);
    ck_assert_uint_eq(matrix->columns, columns);

    matrix_free(&matrix);
}
END_TEST

START_TEST(create_matrix_pos_10x10)
{
    size_t rows = 10;
    size_t columns = 10;
    matrix_t *matrix = matrix_create(rows, columns);

    ck_assert_ptr_nonnull(matrix);
    ck_assert_ptr_nonnull(matrix->data);
    ck_assert_uint_eq(matrix->rows, rows);
    ck_assert_uint_eq(matrix->columns, columns);

    matrix_free(&matrix);
}
END_TEST


//
// matrix_create negatives
//

START_TEST(create_matrix_neg_zero_size)
{
    matrix_t *matrix = matrix_create(0, 0);
    ck_assert_ptr_null(matrix);
}
END_TEST


//
// matrix_free positives
//

START_TEST(free_matrix_allocated)
{
    matrix_t *matrix = matrix_create(3, 3);

    matrix_free(&matrix);

    ck_assert_ptr_null(matrix);
}
END_TEST

START_TEST(free_matrix_null)
{
    matrix_t *matrix = NULL;

    matrix_free(&matrix);

    ck_assert_ptr_null(matrix);
}
END_TEST


Suite *matrix_suite(void)
{
    Suite *s = suite_create("matrix");

    TCase *tc_create_matrix_pos = tcase_create("matrix_create posititves");
    tcase_add_test(tc_create_matrix_pos, create_matrix_pos_1x1);
    tcase_add_test(tc_create_matrix_pos, create_matrix_pos_10x10);

    TCase *tc_create_matrix_neg = tcase_create("matrix_create negatives");
    tcase_add_test(tc_create_matrix_neg, create_matrix_neg_zero_size);

    TCase *tc_free_matrix = tcase_create("matrix_free positives");
    tcase_add_test(tc_free_matrix, free_matrix_allocated);
    tcase_add_test(tc_free_matrix, free_matrix_null);

    suite_add_tcase(s, tc_create_matrix_pos);
    suite_add_tcase(s, tc_create_matrix_neg);
    suite_add_tcase(s, tc_free_matrix);

    return s;
}
