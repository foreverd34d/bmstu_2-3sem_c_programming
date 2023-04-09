#include "check_main.h"
#include "list.h"
#include "numbers_io.h"
#include <check.h>
#include <stdbool.h>
#include <stdlib.h>

//
// read_int_list_file 
//

START_TEST(read_num_list_file_usual)
{
    FILE *f = fopen(DATADIR_PREFIX"/read_usual.txt", "r");

    int data[] = { 1, 2, 20, -10 };
    size_t len = sizeof(data) / sizeof(*data);
    node_t *expect = NULL;

    for (size_t i = 0; i < len; i++)
    {
        node_t *new = node_create(data + i);
        append(&expect, &new);
    }

    node_t *got = read_num_list_file(f);
    fclose(f);

    ck_assert_ptr_nonnull(got);
    ck_assert_uint_eq(list_len(got), list_len(expect));
    
    node_t *got_cur = got;
    node_t *expect_cur = expect;
    for (; got_cur && expect_cur; got_cur = node_get_next(got_cur), expect_cur = node_get_next(expect_cur))
    {
        ck_assert_int_eq(0, numbers_comparator(node_get_data(got_cur), node_get_data(expect_cur)));
    }

    list_free(got, free);
    list_free(expect, NULL);
}
END_TEST

START_TEST(read_num_list_file_single_num)
{
    FILE *f = fopen(DATADIR_PREFIX"/single.txt", "r");

    int data[] = { 727 };
    size_t len = sizeof(data) / sizeof(*data);
    node_t *expect = NULL;

    for (size_t i = 0; i < len; i++)
    {
        node_t *new = node_create(data + i);
        append(&expect, &new);
    }

    node_t *got = read_num_list_file(f);
    fclose(f);

    ck_assert_ptr_nonnull(got);
    ck_assert_uint_eq(list_len(got), list_len(expect));
    
    node_t *got_cur = got;
    node_t *expect_cur = expect;
    for (; got_cur && expect_cur; got_cur = node_get_next(got_cur), expect_cur = node_get_next(expect_cur))
    {
        ck_assert_int_eq(0, numbers_comparator(node_get_data(got_cur), node_get_data(expect_cur)));
    }

    list_free(got, free);
    list_free(expect, NULL);
}
END_TEST

START_TEST(read_num_list_file_spaces)
{
    FILE *f = fopen(DATADIR_PREFIX"/spaces.txt", "r");

    node_t *got = read_num_list_file(f);
    fclose(f);

    ck_assert_ptr_null(got);
}
END_TEST

START_TEST(read_num_list_file_symbol_in_mid)
{
    FILE *f = fopen(DATADIR_PREFIX"/symbol.txt", "r");

    node_t *got = read_num_list_file(f);
    fclose(f);

    ck_assert_ptr_null(got);
}
END_TEST


//
// print_num_list_file tests
//

START_TEST(print_num_list_file_usual)
{
    char *filename = DATADIR_PREFIX"/print_num_usual.txt";

    int data[] = { 1, 2, 20, -10 };
    size_t len = sizeof(data) / sizeof(*data);
    node_t *expect = NULL;

    for (size_t i = 0; i < len; i++)
    {
        node_t *new = node_create(data + i);
        append(&expect, &new);
    }

    FILE *f = fopen(filename, "w");
    print_num_list_file(f, expect);
    fclose(f);

    f = fopen(filename, "r");
    node_t *got = read_num_list_file(f);
    fclose(f);

    ck_assert_ptr_nonnull(got);
    ck_assert_uint_eq(list_len(got), list_len(expect));
    
    node_t *got_cur = got;
    node_t *expect_cur = expect;
    for (; got_cur && expect_cur; got_cur = node_get_next(got_cur), expect_cur = node_get_next(expect_cur))
    {
        ck_assert_int_eq(0, numbers_comparator(node_get_data(got_cur), node_get_data(expect_cur)));
    }

    list_free(got, free);
    list_free(expect, NULL);
}
END_TEST

START_TEST(print_num_list_file_single_el)
{
    char *filename = DATADIR_PREFIX"/print_num_single.txt";

    int data[] = { 420 };
    size_t len = sizeof(data) / sizeof(*data);
    node_t *expect = NULL;

    for (size_t i = 0; i < len; i++)
    {
        node_t *new = node_create(data + i);
        append(&expect, &new);
    }

    FILE *f = fopen(filename, "w");
    print_num_list_file(f, expect);
    fclose(f);

    f = fopen(filename, "r");
    node_t *got = read_num_list_file(f);
    fclose(f);

    ck_assert_ptr_nonnull(got);
    ck_assert_uint_eq(list_len(got), list_len(expect));
    
    node_t *got_cur = got;
    node_t *expect_cur = expect;
    for (; got_cur && expect_cur; got_cur = node_get_next(got_cur), expect_cur = node_get_next(expect_cur))
    {
        ck_assert_int_eq(0, numbers_comparator(node_get_data(got_cur), node_get_data(expect_cur)));
    }

    list_free(got, free);
    list_free(expect, NULL);
}
END_TEST

START_TEST(print_num_list_file_empty_list)
{
    char *filename = DATADIR_PREFIX"/print_num_empty.txt";

    node_t *expect = NULL;

    FILE *f = fopen(filename, "w");
    print_num_list_file(f, expect);
    fclose(f);

    f = fopen(filename, "r");
    node_t *got = read_num_list_file(f);
    fclose(f);

    ck_assert_ptr_null(expect);
    ck_assert_ptr_null(got);
}
END_TEST


//
// numbers_comparator tests
//

START_TEST(numbers_comparator_a_gt_b)
{
    int a = 1;
    int b = 0;

    int rc = numbers_comparator(&a, &b);

    ck_assert_int_lt(0, rc);
}
END_TEST

START_TEST(number_comparator_a_lt_b)
{
    int a = 0;
    int b = 10;

    int rc = numbers_comparator(&a, &b);

    ck_assert_int_gt(0, rc);
}
END_TEST

START_TEST(number_comparator_a_eq_b)
{
    int a = 10;
    int b = 10;

    int rc = numbers_comparator(&a, &b);

    ck_assert_int_eq(0, rc);
}
END_TEST


//
// read_int_str tests
//

START_TEST(read_int_str_pos_num)
{
    char *data = "727";
    int expect = 727;

    int got;
    bool rc = read_int_str(&got, data);

    ck_assert_int_eq(true, rc);
    ck_assert_int_eq(got, expect);
}
END_TEST

START_TEST(read_int_str_neg_num)
{
    char *data = "-727";
    int expect = -727;

    int got;
    bool rc = read_int_str(&got, data);

    ck_assert_int_eq(true, rc);
    ck_assert_int_eq(got, expect);
}
END_TEST

START_TEST(read_int_str_space_str)
{
    char *data = " \t\n\t  \t";
    int got;
    bool rc = read_int_str(&got, data);
    ck_assert_int_eq(false, rc);
}
END_TEST

START_TEST(read_int_str_no_int)
{
    char *data = " aboba ";
    int got;
    bool rc = read_int_str(&got, data);
    ck_assert_int_eq(false, rc);
}
END_TEST

START_TEST(read_int_str_symbols_after)
{
    char *data = "123  ";
    int got;
    bool rc = read_int_str(&got, data);
    ck_assert_int_eq(false, rc);
}
END_TEST

START_TEST(read_int_str_symbols_before)
{
    char *data = "  321";
    int got;
    bool rc = read_int_str(&got, data);
    ck_assert_int_eq(false, rc);
}
END_TEST


Suite *numbers_io_suite(void)
{
    Suite *s = suite_create("numbers_io");

    TCase *tc_read_file = tcase_create("read_num_list_file");
    tcase_add_test(tc_read_file, read_num_list_file_single_num);
    tcase_add_test(tc_read_file, read_num_list_file_spaces);
    tcase_add_test(tc_read_file, read_num_list_file_symbol_in_mid);
    tcase_add_test(tc_read_file, read_num_list_file_usual);

    TCase *tc_print_file = tcase_create("print_num_list_file");
    tcase_add_test(tc_print_file, print_num_list_file_empty_list);
    tcase_add_test(tc_print_file, print_num_list_file_single_el);
    tcase_add_test(tc_print_file, print_num_list_file_usual);

    TCase *tc_read_int_str = tcase_create("read_int_str");
    tcase_add_test(tc_read_int_str, read_int_str_neg_num);
    tcase_add_test(tc_read_int_str, read_int_str_no_int);
    tcase_add_test(tc_read_int_str, read_int_str_pos_num);
    tcase_add_test(tc_read_int_str, read_int_str_space_str);
    tcase_add_test(tc_read_int_str, read_int_str_symbols_after);
    tcase_add_test(tc_read_int_str, read_int_str_symbols_before);

    TCase *tc_comp = tcase_create("numbers_comparator");
    tcase_add_test(tc_comp, number_comparator_a_eq_b);
    tcase_add_test(tc_comp, number_comparator_a_lt_b);
    tcase_add_test(tc_comp, numbers_comparator_a_gt_b);

    suite_add_tcase(s, tc_read_file);
    suite_add_tcase(s, tc_print_file);
    suite_add_tcase(s, tc_read_int_str);
    suite_add_tcase(s, tc_comp);

    return s;
}
