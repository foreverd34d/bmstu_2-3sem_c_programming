#include <check.h>
#include <stdio.h>

#include "check_main.h"
#include "error_codes.h"
#include "item_io.h"
#include "items.h"

//
// get_lines_amount tests
//

START_TEST(get_lines_amount_usual)
{
    FILE *f = fopen(DATADIR_PREFIX"/10_lines.txt", "r");

    size_t n = get_lines_amount(f);
    fclose(f);

    ck_assert_uint_eq(n, 10);
}
END_TEST

START_TEST(get_lines_amount_one_line)
{
    FILE *f = fopen(DATADIR_PREFIX"/1_line.txt", "r");

    size_t n = get_lines_amount(f);
    fclose(f);

    ck_assert_uint_eq(n, 1);
}
END_TEST

START_TEST(get_lines_amount_no_lines)
{
    FILE *f = fopen(DATADIR_PREFIX"/0_lines.txt", "r");

    size_t n = get_lines_amount(f);
    fclose(f);

    ck_assert_uint_eq(n, 0);
}
END_TEST


//
// read_items_file tests
//

// positives

START_TEST(read_items_file_pos_one_struct)
{
    item_t expect[1] = { { "123456789012345678901234567890", 1e100, 1 } };

    FILE *f = fopen(DATADIR_PREFIX"/one_struct.txt", "r");

    item_t *got = NULL;
    int len = read_items_file(&got, f);
    fclose(f);

    ck_assert_int_eq(len, 1);
    assert_items_arr_eq(expect, got, len);

    items_free(&got, len);
}
END_TEST

START_TEST(read_items_file_pos_three_structs)
{
    item_t expect[3] = {
        { "a", 1, 1 },
        { "b", 2, 2 },
        { "c", 3, 3 },
    };

    FILE *f = fopen(DATADIR_PREFIX"/three_structs.txt", "r");

    item_t *got = NULL;
    int len = read_items_file(&got, f);
    fclose(f);

    ck_assert_int_eq(len, 3);
    assert_items_arr_eq(expect, got, len);

    items_free(&got, len);
}
END_TEST

// negatives

START_TEST(read_items_file_neg_spaces)
{
    FILE *f = fopen(DATADIR_PREFIX"/spaces.txt", "r");

    item_t *got = NULL;
    int len = read_items_file(&got, f);
    fclose(f);

    ck_assert_int_eq(len, -1);
}
END_TEST

START_TEST(read_items_file_neg_not_enough_fields)
{
    FILE *f = fopen(DATADIR_PREFIX"/not_enough_fields.txt", "r");

    item_t *got = NULL;
    int len = read_items_file(&got, f);
    fclose(f);

    ck_assert_int_eq(len, -1);
}
END_TEST

START_TEST(read_items_file_neg_skipped_name)
{
    FILE *f = fopen(DATADIR_PREFIX"/skipped_name.txt", "r");

    item_t *got = NULL;
    int len = read_items_file(&got, f);
    fclose(f);

    ck_assert_int_eq(len, -1);
}
END_TEST

START_TEST(read_items_file_neg_incorrect_weight)
{
    FILE *f = fopen(DATADIR_PREFIX"/incorrect_weight.txt", "r");

    item_t *got = NULL;
    int len = read_items_file(&got, f);
    fclose(f);

    ck_assert_int_eq(len, -1);
}
END_TEST

START_TEST(read_items_file_neg_incorrect_volume)
{
    FILE *f = fopen(DATADIR_PREFIX"/incorrect_volume.txt", "r");

    item_t *got = NULL;
    int len = read_items_file(&got, f);
    fclose(f);

    ck_assert_int_eq(len, -1);
}
END_TEST

START_TEST(read_items_file_neg_negative_volume)
{
    FILE *f = fopen(DATADIR_PREFIX"/negative_volume.txt", "r");

    item_t *got = NULL;
    int len = read_items_file(&got, f);
    fclose(f);

    ck_assert_int_eq(len, -1);
}
END_TEST


//
// print_items_file tests
//

START_TEST(print_items_file_single_struct)
{
    item_t expect[1] = { { "hello", 11, 22 } };

    const char *filename = DATADIR_PREFIX"/print_items_single.txt";
    FILE *f = fopen(filename, "w");

    print_items_file(expect, 1, f);
    fclose(f);

    f = fopen(filename, "r");

    item_t *got = NULL;
    int got_len = read_items_file(&got, f);
    fclose(f);

    ck_assert_int_eq(got_len, 1);
    assert_items_arr_eq(expect, got, got_len);
    items_free(&got, got_len);
}
END_TEST


Suite *item_io_suite(void)
{
    Suite *s = suite_create("item_io");

    TCase *tc_get_lines_amount = tcase_create("get_lines_amount pos");
    tcase_add_test(tc_get_lines_amount, get_lines_amount_usual);
    tcase_add_test(tc_get_lines_amount, get_lines_amount_one_line);
    tcase_add_test(tc_get_lines_amount, get_lines_amount_no_lines);

    TCase *tc_read_items_file_pos = tcase_create("read_items_file pos");
    tcase_add_test(tc_read_items_file_pos, read_items_file_pos_one_struct);
    tcase_add_test(tc_read_items_file_pos, read_items_file_pos_three_structs);

    TCase *tc_read_items_file_neg = tcase_create("read_items_file neg");
    tcase_add_test(tc_read_items_file_neg, read_items_file_neg_spaces);
    tcase_add_test(tc_read_items_file_neg, read_items_file_neg_skipped_name);
    tcase_add_test(tc_read_items_file_neg, read_items_file_neg_not_enough_fields);
    tcase_add_test(tc_read_items_file_neg, read_items_file_neg_incorrect_weight);
    tcase_add_test(tc_read_items_file_neg, read_items_file_neg_incorrect_volume);
    tcase_add_test(tc_read_items_file_neg, read_items_file_neg_negative_volume);

    TCase *tc_print_items_file = tcase_create("print_items_file pos");
    tcase_add_test(tc_print_items_file, print_items_file_single_struct);

    suite_add_tcase(s, tc_get_lines_amount);
    suite_add_tcase(s, tc_read_items_file_pos);
    suite_add_tcase(s, tc_read_items_file_neg);
    suite_add_tcase(s, tc_print_items_file);

    return s;
}
