#include "check_main.h"
#include "list.h"
#include "matrix_list.h"
#include "matrix_list_io.h"
#include <check.h>

START_TEST(read_mlist_file_pos_1x1)
{
    mlist_t *expect = mlist_create();
    mlist_append_new_element(expect, 0, 0, 727);

    FILE *f = fopen(DATADIR_PREFIX "/1x1.txt", "r");
    mlist_t *got = read_mlist_file(f);
    fclose(f);

    ck_assert_ptr_nonnull(got);
    ck_assert_uint_eq(mlist_get_rows(expect), mlist_get_rows(got));
    ck_assert_uint_eq(mlist_get_cols(expect), mlist_get_cols(got));
    ck_assert_uint_eq(mnode_get_val(node_get_data(mlist_get_head(expect))),
        mnode_get_val(node_get_data(mlist_get_head(got))));

    mlist_free(expect);
    mlist_free(got);
}
END_TEST

START_TEST(read_mlist_file_pos_all_zeros)
{
    FILE *f = fopen(DATADIR_PREFIX "/zeros.txt", "r");
    mlist_t *got = read_mlist_file(f);
    fclose(f);

    ck_assert_ptr_nonnull(got);

    mlist_free(got);
}
END_TEST

START_TEST(read_mlist_file_neg_incorrect_size)
{
    FILE *f = fopen(DATADIR_PREFIX"/inc_size.txt", "r");
    mlist_t *got = read_mlist_file(f);
    fclose(f);

    ck_assert_ptr_null(got);
}
END_TEST

START_TEST(read_mlist_file_neg_not_enough_elements)
{
    FILE *f = fopen(DATADIR_PREFIX"/not_enough.txt", "r");
    mlist_t *got = read_mlist_file(f);
    fclose(f);

    ck_assert_ptr_null(got);
}
END_TEST

START_TEST(read_mlist_file_neg_symbol)
{
    FILE *f = fopen(DATADIR_PREFIX"/symbol.txt", "r");
    mlist_t *got = read_mlist_file(f);
    fclose(f);

    ck_assert_ptr_null(got);
}
END_TEST

START_TEST(print_mlist_file_usual)
{
    mlist_t *list = mlist_create();
    mlist_append_new_element(list, 0, 0, 1);
    mlist_append_new_element(list, 1, 1, 1);

    FILE *f = fopen(DATADIR_PREFIX"/print_usual.txt", "w");
    print_mlist_file(f, list);
    fclose(f);

    ck_assert_ptr_nonnull(list);

    mlist_free(list);
}
END_TEST

Suite *matrix_list_io_suite(void)
{
    Suite *s = suite_create("matrix_list_io");

    TCase *tc_read_pos = tcase_create("read_mlist_file positives");
    tcase_add_test(tc_read_pos, read_mlist_file_pos_1x1);
    tcase_add_test(tc_read_pos, read_mlist_file_pos_all_zeros);

    TCase *tc_read_neg = tcase_create("read_mlist_file negatives");
    tcase_add_test(tc_read_neg, read_mlist_file_neg_incorrect_size);
    tcase_add_test(tc_read_neg, read_mlist_file_neg_not_enough_elements);
    tcase_add_test(tc_read_neg, read_mlist_file_neg_symbol);

    TCase *tc_print = tcase_create("print_mlist_file positives");
    tcase_add_test(tc_print, print_mlist_file_usual);

    suite_add_tcase(s, tc_read_pos);
    suite_add_tcase(s, tc_read_neg);
    suite_add_tcase(s, tc_print);

    return s;
}
