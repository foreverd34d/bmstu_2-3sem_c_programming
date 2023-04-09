#include "check_main.h"
#include "matrix_list.h"
#include <check.h>
#include <stdbool.h>

START_TEST(mnode_create_usual)
{
    size_t row = 1;
    size_t col = 2;
    unsigned long val = 3;

    mnode_t *node = mnode_create(row, col, val);

    ck_assert_ptr_nonnull(node);
    ck_assert_uint_eq(row, mnode_get_row(node));
    ck_assert_uint_eq(col, mnode_get_col(node));
    ck_assert_uint_eq(val, mnode_get_val(node));

    mnode_free(node);
}
END_TEST

START_TEST(mlist_create_nonnull)
{
    mlist_t *list = mlist_create();

    ck_assert_ptr_nonnull(list);
    ck_assert_ptr_null(mlist_get_head(list));

    mlist_free(list);
}
END_TEST

START_TEST(mnode_free_nonnull)
{
    mnode_t *node = mnode_create(1, 2, 3);
    mnode_free(node);
}
END_TEST

START_TEST(mnode_free_null)
{
    mnode_t *node = NULL;
    mnode_free(node);
}
END_TEST

START_TEST(mlist_free_nonnull)
{
    mlist_t *list = mlist_create();
    mlist_free(list);
}
END_TEST

START_TEST(mlist_free_null)
{
    mlist_t *list = NULL;
    mlist_free(list);
}
END_TEST

START_TEST(mnode_get_row_null)
{
    ck_assert_uint_eq(0, mnode_get_row(NULL));
}
END_TEST

START_TEST(mnode_get_col_null)
{
    ck_assert_uint_eq(0, mnode_get_col(NULL));
}
END_TEST

START_TEST(mnode_get_val_null)
{
    ck_assert_uint_eq(0, mnode_get_val(NULL));
}
END_TEST

START_TEST(mlist_get_rows_full_matrix)
{
    mlist_t *list = mlist_create();

    mlist_append_new_element(list, 0, 0, 1);
    mlist_append_new_element(list, 0, 1, 2);
    mlist_append_new_element(list, 1, 0, 3);
    mlist_append_new_element(list, 1, 1, 4);

    ck_assert_uint_eq(2, mlist_get_rows(list));

    mlist_free(list);
}
END_TEST

START_TEST(mlist_get_rows_sparse_matrix)
{
    mlist_t *list = mlist_create();

    mlist_append_new_element(list, 0, 0, 1);
    mlist_append_new_element(list, 10, 5555, 1);
    mlist_append_new_element(list, 227, 1000, 1);

    ck_assert_uint_eq(228, mlist_get_rows(list));

    mlist_free(list);
}

START_TEST(mlist_get_rows_null)
{
    ck_assert_uint_eq(0, mlist_get_rows(NULL));
}
END_TEST

START_TEST(mlist_get_cols_full_matrix)
{
    mlist_t *list = mlist_create();

    mlist_append_new_element(list, 0, 0, 1);
    mlist_append_new_element(list, 0, 1, 2);
    mlist_append_new_element(list, 1, 0, 3);
    mlist_append_new_element(list, 1, 1, 4);

    ck_assert_uint_eq(2, mlist_get_cols(list));

    mlist_free(list);
}
END_TEST

START_TEST(mlist_get_cols_sparse_matrix)
{
    mlist_t *list = mlist_create();

    mlist_append_new_element(list, 0, 0, 1);
    mlist_append_new_element(list, 10, 5555, 1);
    mlist_append_new_element(list, 228, 1000, 1);

    ck_assert_uint_eq(5556, mlist_get_cols(list));

    mlist_free(list);
}

START_TEST(mlist_get_cols_null)
{
    ck_assert_uint_eq(0, mlist_get_cols(NULL));
}
END_TEST

START_TEST(mlist_get_head_null)
{
    ck_assert_ptr_null(mlist_get_head(NULL));
}
END_TEST

START_TEST(mlist_find_value_nonzero)
{
    size_t row = 1;
    size_t col = 2;
    unsigned long val = 3;

    mlist_t *list = mlist_create();
    mlist_append_new_element(list, row, col, val);

    ck_assert_uint_eq(val, mlist_find_value(list, row, col));

    mlist_free(list);
}
END_TEST

START_TEST(mlist_find_value_zero)
{
    size_t row = 1;
    size_t col = 2;
    unsigned long val = 3;

    mlist_t *list = mlist_create();
    mlist_append_new_element(list, row - 1, col, val);

    ck_assert_uint_eq(0, mlist_find_value(list, row, col));

    mlist_free(list);
}
END_TEST

START_TEST(mlist_find_max_row_usual)
{
    size_t row = 1;
    size_t col = 1;
    unsigned long val = 3;

    mlist_t *list = mlist_create();
    mlist_append_new_element(list, row - 1, col - 1, val - 1);
    mlist_append_new_element(list, row, col, val);
    mlist_append_new_element(list, row + 1, col + 1, val - 1);

    ck_assert_int_eq(row, mlist_find_max_row(list));

    mlist_free(list);
}
END_TEST

START_TEST(mlist_find_max_row_all_elements_equal)
{
    unsigned long val = 3;

    mlist_t *list = mlist_create();
    mlist_append_new_element(list, 0, 0, val);
    mlist_append_new_element(list, 0, 1, val);
    mlist_append_new_element(list, 0, 2, val);

    ck_assert_int_eq(-1, mlist_find_max_row(list));

    mlist_free(list);
}
END_TEST

START_TEST(mlist_rm_row_first_row)
{
    size_t row = 1;
    size_t col = 1;
    unsigned long val = 3;

    mlist_t *list = mlist_create();
    mlist_append_new_element(list, row - 1, col - 1, val - 1);
    mlist_append_new_element(list, row, col, val);
    mlist_append_new_element(list, row + 1, col + 1, val + 1);

    ck_assert_uint_eq(true, mlist_rm_row(list, row - 1));
    ck_assert_uint_eq(0, mlist_find_value(list, row - 1, col - 1));

    mlist_free(list);
}
END_TEST

START_TEST(mlist_rm_row_middle_row)
{
    size_t row = 1;
    size_t col = 1;
    unsigned long val = 3;

    mlist_t *list = mlist_create();
    mlist_append_new_element(list, row - 1, col - 1, val - 1);
    mlist_append_new_element(list, row, col, val);
    mlist_append_new_element(list, row + 1, col + 1, val + 1);

    ck_assert_uint_eq(true, mlist_rm_row(list, row));
    ck_assert_uint_eq(0, mlist_find_value(list, row, col));

    mlist_free(list);
}
END_TEST

START_TEST(mnode_row_comparator_row_ne_elem_row)
{
    size_t row = 1;
    size_t col = 1;
    unsigned long val = 3;

    mnode_t *node = mnode_create(row, col, val);

    size_t row_before = row - 1;
    ck_assert_int_ne(0, mnode_row_comparator(node, &row_before));

    mnode_free(node);
}
END_TEST


START_TEST(mnode_row_comparator_row_eq_elem_row)
{
    size_t row = 1;
    size_t col = 1;
    unsigned long val = 3;

    mnode_t *node = mnode_create(row, col, val);

    ck_assert_int_eq(0, mnode_row_comparator(node, &row));

    mnode_free(node);
}
END_TEST

START_TEST(mlist_append_new_element_usual)
{
    size_t row = 1;
    size_t col = 1;
    unsigned long val = 3;

    mlist_t *list = mlist_create();

    ck_assert_uint_eq(true, mlist_append_new_element(list, row, col, val));
    ck_assert_uint_eq(val, mlist_find_value(list, row, col));

    mlist_free(list);
}
END_TEST

Suite *matrix_list_suite(void)
{
    Suite *s = suite_create("matrix_list");

    TCase *tc_mnode_create = tcase_create("mnode_create");
    tcase_add_test(tc_mnode_create, mnode_create_usual);

    TCase *tc_mlist_create = tcase_create("mlist_create");
    tcase_add_test(tc_mlist_create, mlist_create_nonnull);

    TCase *tc_mnode_free = tcase_create("mnode_free");
    tcase_add_test(tc_mnode_free, mnode_free_nonnull);
    tcase_add_test(tc_mnode_free, mnode_free_null);

    TCase *tc_mlist_free = tcase_create("mlist_free");
    tcase_add_test(tc_mlist_free, mlist_free_nonnull);
    tcase_add_test(tc_mlist_free, mlist_free_null);

    TCase *tc_getters = tcase_create("getters");
    tcase_add_test(tc_getters, mnode_get_row_null);
    tcase_add_test(tc_getters, mnode_get_col_null);
    tcase_add_test(tc_getters, mnode_get_val_null);
    tcase_add_test(tc_getters, mlist_get_rows_full_matrix);
    tcase_add_test(tc_getters, mlist_get_rows_sparse_matrix);
    tcase_add_test(tc_getters, mlist_get_rows_null);
    tcase_add_test(tc_getters, mlist_get_cols_full_matrix);
    tcase_add_test(tc_getters, mlist_get_cols_sparse_matrix);
    tcase_add_test(tc_getters, mlist_get_cols_null);
    tcase_add_test(tc_getters, mlist_get_head_null);

    TCase *tc_find = tcase_create("mlist_find_value");
    tcase_add_test(tc_find, mlist_find_value_nonzero);
    tcase_add_test(tc_find, mlist_find_value_zero);

    TCase *tc_maxrow = tcase_create("mlist_find_max_row");
    tcase_add_test(tc_maxrow, mlist_find_max_row_usual);
    tcase_add_test(tc_maxrow, mlist_find_max_row_all_elements_equal);

    TCase *tc_rm = tcase_create("mlist_rm_row");
    tcase_add_test(tc_rm, mlist_rm_row_middle_row);
    tcase_add_test(tc_rm, mlist_rm_row_first_row);

    TCase *tc_rowcmp = tcase_create("mnode_row_comparator");
    tcase_add_test(tc_rowcmp, mnode_row_comparator_row_eq_elem_row);
    tcase_add_test(tc_rowcmp, mnode_row_comparator_row_ne_elem_row);

    TCase *tc_append = tcase_create("mlist_append_new_element");
    tcase_add_test(tc_append, mlist_append_new_element_usual);

    suite_add_tcase(s, tc_mnode_create);
    suite_add_tcase(s, tc_mlist_create);
    suite_add_tcase(s, tc_mnode_free);
    suite_add_tcase(s, tc_mlist_free);
    suite_add_tcase(s, tc_getters);
    suite_add_tcase(s, tc_find);
    suite_add_tcase(s, tc_maxrow);
    suite_add_tcase(s, tc_rm);
    suite_add_tcase(s, tc_rowcmp);
    suite_add_tcase(s, tc_append);

    return s;
}
