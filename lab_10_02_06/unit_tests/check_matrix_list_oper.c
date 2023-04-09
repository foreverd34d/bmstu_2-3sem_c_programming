#include "check_main.h"
#include "list.h"
#include "matrix_list.h"
#include "matrix_list_oper.h"
#include <check.h>
#include <stdbool.h>

START_TEST(matrix_addition_2x2)
{
    mlist_t *list_a = mlist_create();
    mlist_t *list_b = mlist_create();

    mlist_append_new_element(list_a, 0, 0, 1);
    mlist_append_new_element(list_a, 1, 1, 1);

    mlist_append_new_element(list_b, 0, 0, 2);
    mlist_append_new_element(list_b, 1, 0, 2);

    mlist_t *result = matrix_addition(list_a, list_b);

    ck_assert_ptr_nonnull(result);
    ck_assert_uint_eq(3, list_len(mlist_get_head(result)));
    ck_assert_uint_eq(3, mnode_get_val(node_get_data(mlist_get_head(result))));

    mlist_free(list_a);
    mlist_free(list_b);
    mlist_free(result);
}
END_TEST

START_TEST(matrix_addition_null)
{
    mlist_t *list_a = mlist_create();
    mlist_t *list_b = NULL;

    mlist_append_new_element(list_a, 0, 0, 1);
    mlist_append_new_element(list_a, 1, 1, 1);

    mlist_t *result = matrix_addition(list_a, list_b);

    ck_assert_ptr_null(result);

    mlist_free(list_a);
}
END_TEST

START_TEST(matrix_multiplication_3x3)
{
    mlist_t *list_a = mlist_create();
    mlist_t *list_b = mlist_create();

    mlist_append_new_element(list_a, 0, 0, 1);
    mlist_append_new_element(list_a, 1, 1, 1);
    mlist_append_new_element(list_a, 2, 2, 1);

    mlist_append_new_element(list_b, 0, 0, 4);
    mlist_append_new_element(list_b, 1, 0, 2);

    mlist_t *result = matrix_multiplication(list_a, list_b);

    ck_assert_ptr_nonnull(result);
    ck_assert_uint_eq(2, list_len(mlist_get_head(result)));
    ck_assert_uint_eq(4, mnode_get_val(node_get_data(mlist_get_head(result))));

    mlist_free(list_a);
    mlist_free(list_b);
    mlist_free(result);
}
END_TEST

START_TEST(matrix_multiplication_null)
{
    mlist_t *list_a = NULL;
    mlist_t *list_b = mlist_create();

    mlist_append_new_element(list_b, 0, 0, 1);
    mlist_append_new_element(list_b, 1, 1, 1);

    mlist_t *result = matrix_addition(list_a, list_b);

    ck_assert_ptr_null(result);

    mlist_free(list_b);
}
END_TEST

START_TEST(matrix_rm_max_row_middle_row)
{
    mlist_t *list = mlist_create();
    mlist_append_new_element(list, 0, 1, 50);
    mlist_append_new_element(list, 1, 2, 90);

    ck_assert_uint_eq(true, matrix_rm_max_row(list));
    ck_assert_uint_eq(1, mlist_get_rows(list));
    ck_assert_uint_eq(2, mlist_get_cols(list));

    ck_assert_uint_eq(50, mnode_get_val(node_get_data(mlist_get_head(list))));

    mlist_free(list);
}
END_TEST

START_TEST(matrix_rm_max_row_first_row)
{
    mlist_t *list = mlist_create();
    mlist_append_new_element(list, 0, 1, 90);
    mlist_append_new_element(list, 1, 2, 89);

    ck_assert_uint_eq(true, matrix_rm_max_row(list));
    ck_assert_uint_eq(2, mlist_get_rows(list));
    ck_assert_uint_eq(3, mlist_get_cols(list));

    ck_assert_uint_eq(89, mnode_get_val(node_get_data(mlist_get_head(list))));

    mlist_free(list);
}
END_TEST

START_TEST(matrix_rm_max_row_all_equal)
{
    size_t rows = 2;

    mlist_t *list = mlist_create();

    mlist_append_new_element(list, 0, 0, 10);
    mlist_append_new_element(list, 1, 0, 10);

    ck_assert_uint_eq(false, matrix_rm_max_row(list));
    ck_assert_uint_eq(rows, mlist_get_rows(list));

    mlist_free(list);
}
END_TEST

Suite *matrix_list_oper_suite(void)
{
    Suite *s = suite_create("matrix_list_oper");

    TCase *tc_add = tcase_create("matrix_addition");
    tcase_add_test(tc_add, matrix_addition_2x2);
    tcase_add_test(tc_add, matrix_addition_null);

    TCase *tc_mul = tcase_create("matrix_multiplication");
    tcase_add_test(tc_mul, matrix_multiplication_3x3);
    tcase_add_test(tc_mul, matrix_multiplication_null);

    TCase *tc_rm = tcase_create("matrix_rm_max_row");
    tcase_add_test(tc_rm, matrix_rm_max_row_first_row);
    tcase_add_test(tc_rm, matrix_rm_max_row_middle_row);
    tcase_add_test(tc_rm, matrix_rm_max_row_all_equal);

    suite_add_tcase(s, tc_add);
    suite_add_tcase(s, tc_mul);
    suite_add_tcase(s, tc_rm);

    return s;
}
