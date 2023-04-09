#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/numio.h"
#include "../inc/check_main.h"

//
// get_numbers_amount positives
//

START_TEST(get_numbers_amount_empty_file)
{
    FILE *f = fopen("unit_tests/data/empty.txt", "r");
    int amount = get_numbers_amount(f);
    fclose(f);
    ck_assert_int_eq(0, amount);
}
END_TEST

START_TEST(get_numbers_amount_invalid_file)
{
    FILE *f = fopen("unit_tests/data/invalid.txt", "r");
    int amount = get_numbers_amount(f);
    fclose(f);
    ck_assert_int_eq(-1, amount);
}
END_TEST

START_TEST(get_numbers_amount_usual)
{
    FILE *f = fopen("unit_tests/data/10_num.txt", "r");
    int amount = get_numbers_amount(f);
    fclose(f);
    ck_assert_int_eq(10, amount);
}
END_TEST


//
// get_numbers_file positives
//

START_TEST(get_numbers_file_usual)
{
    FILE *f = fopen("unit_tests/data/10_num.txt", "r");
    int amount = get_numbers_amount(f);

    int expect[] = { 57, 98, 29, 72, 49, 56, 7, 32, 62, 47 };
    int *arr = malloc(amount * sizeof(int));
    int *arr_e = arr + amount;

    get_numbers_file(arr, arr_e, f);
    fclose(f);

    ck_assert_mem_eq(arr, expect, sizeof(expect));
    free(arr);
}
END_TEST

START_TEST(get_numbers_file_single_number)
{
    FILE *f = fopen("unit_tests/data/single.txt", "r");
    int amount = get_numbers_amount(f);

    int expect[] = { 727 };
    int *arr = malloc(amount * sizeof(int));
    int *arr_e = arr + amount;

    get_numbers_file(arr, arr_e, f);
    fclose(f);

    ck_assert_mem_eq(arr, expect, sizeof(expect));
    free(arr);
}
END_TEST


//
// read_numbers_file negatives
//

START_TEST(read_numbers_file_neg_empty_file)
{
    FILE *f = fopen("unit_tests/data/empty.txt", "r");
    int *arr, *arr_e;

    int err = read_numbers_file(&arr, &arr_e, f);
    fclose(f);

    ck_assert_int_eq(err, ERR_FILE_EMPTY);
}
END_TEST

START_TEST(read_numbers_file_neg_invalid_file)
{
    FILE *f = fopen("unit_tests/data/invalid.txt", "r");
    int *arr, *arr_e;

    int err = read_numbers_file(&arr, &arr_e, f);
    fclose(f);

    ck_assert_int_eq(err, ERR_FILE_READ);
}
END_TEST

START_TEST(read_numbers_file_neg_only_spaces)
{
    FILE *f = fopen("unit_tests/data/spaces.txt", "r");
    int *arr, *arr_e;

    int err = read_numbers_file(&arr, &arr_e, f);
    fclose(f);

    ck_assert_int_eq(err, ERR_FILE_EMPTY);
}
END_TEST

//
// read_numbers_file positives
//

START_TEST(read_numbers_file_pos_usual)
{
    FILE *f = fopen("unit_tests/data/10_num.txt", "r");

    int expect[] = { 57, 98, 29, 72, 49, 56, 7, 32, 62, 47 };
    int *arr, *arr_e;

    int err = read_numbers_file(&arr, &arr_e, f);
    fclose(f);

    ck_assert_int_eq(err, RET_SUCCESS);
    ck_assert_mem_eq(arr, expect, sizeof(expect));
    free(arr);
}
END_TEST

START_TEST(read_numbers_file_pos_single_number)
{
    FILE *f = fopen("unit_tests/data/single.txt", "r");

    int expect[] = { 727 };
    int *arr, *arr_e;

    int err = read_numbers_file(&arr, &arr_e, f);
    fclose(f);

    ck_assert_int_eq(err, RET_SUCCESS);
    ck_assert_mem_eq(arr, expect, sizeof(expect));
    free(arr);
}
END_TEST


//
// print_numbers_file positives
//

START_TEST(print_numbers_file_empty)
{
    int arr[1];
    int len = 0;
    int *arr_e = arr + len;

    FILE *f = fopen("unit_tests/data/print_empty.txt", "w");
    print_numbers_file(arr, arr_e, f);
    fclose(f);

    int *dest = NULL, *dest_e = NULL;

    f = fopen("unit_tests/data/print_empty.txt", "r");
    int err = read_numbers_file(&dest, &dest_e, f);
    fclose(f);

    ck_assert_int_eq(err, ERR_FILE_EMPTY);
    free(dest);
}
END_TEST

START_TEST(print_numbers_file_single)
{
    int arr[] = { 333 };
    int len = sizeof(arr)/sizeof(*arr);
    int *arr_e = arr + len;

    FILE *f = fopen("unit_tests/data/print_single.txt", "w");
    print_numbers_file(arr, arr_e, f);
    fclose(f);

    int *dest = NULL, *dest_e = NULL;
    int expect[] = { 333 };

    f = fopen("unit_tests/data/print_single.txt", "r");
    int err = read_numbers_file(&dest, &dest_e, f);
    fclose(f);

    ck_assert_int_eq(err, RET_SUCCESS);
    ck_assert_mem_eq(dest, expect, sizeof(expect));
    free(dest);
}
END_TEST


Suite *numio_suite(void)
{
    Suite *s = suite_create("numio");

    TCase *tc_get_numbers_amount = tcase_create("get_numbers_amount positives");
    tcase_add_test(tc_get_numbers_amount, get_numbers_amount_empty_file);
    tcase_add_test(tc_get_numbers_amount, get_numbers_amount_invalid_file);
    tcase_add_test(tc_get_numbers_amount, get_numbers_amount_usual);

    TCase *tc_get_numbers_file = tcase_create("get_numbers_file positives");
    tcase_add_test(tc_get_numbers_file, get_numbers_file_usual);
    tcase_add_test(tc_get_numbers_file, get_numbers_file_single_number);

    TCase *tc_read_numbers_file_neg = tcase_create("read_numbers_file negatives");
    tcase_add_test(tc_read_numbers_file_neg, read_numbers_file_neg_empty_file);
    tcase_add_test(tc_read_numbers_file_neg, read_numbers_file_neg_invalid_file);
    tcase_add_test(tc_read_numbers_file_neg, read_numbers_file_neg_only_spaces);

    TCase *tc_read_numbers_file_pos = tcase_create("read_numbers_file posititves");
    tcase_add_test(tc_read_numbers_file_pos, read_numbers_file_pos_usual);
    tcase_add_test(tc_read_numbers_file_pos, read_numbers_file_pos_single_number);

    TCase *tc_print_numbers_file = tcase_create("print_numbers_file");
    tcase_add_test(tc_print_numbers_file, print_numbers_file_single);
    tcase_add_test(tc_print_numbers_file, print_numbers_file_empty);

    suite_add_tcase(s, tc_get_numbers_amount);
    suite_add_tcase(s, tc_get_numbers_file);
    suite_add_tcase(s, tc_read_numbers_file_neg);
    suite_add_tcase(s, tc_read_numbers_file_pos);
    suite_add_tcase(s, tc_print_numbers_file);

    return s;
}
