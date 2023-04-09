#include <check.h>

#include "check_main.h"
#include "error_codes.h"
#include "matrix.h"
#include "matrix_io.h"

#define EPS 1e-5

//
// read_matrix_file posititves
//

START_TEST(read_matrix_file_pos_1x1)
{
    matrix_t *expect = matrix_create(1, 1);
    expect->data[0][0] = 727;

    FILE *f = fopen("unit_tests/data/1x1.txt", "r");

    matrix_t *got = NULL;
    err_t return_code = read_matrix_file(&got, f);

    ck_assert_int_eq(return_code, OK);
    ck_assert_uint_eq(expect->rows, got->rows);
    ck_assert_uint_eq(expect->columns, got->columns);
    for (size_t i = 0; i < got->rows; i++)
    {
        for (size_t j = 0; j < got->columns; j++)
        {
            ck_assert_double_eq_tol(got->data[i][j], expect->data[i][j], EPS);
        }
    }

    matrix_free(&expect);
    matrix_free(&got);
    fclose(f);
}
END_TEST

START_TEST(read_matrix_file_pos_3x1)
{
    matrix_t *expect = matrix_create(3, 1);
    expect->data[0][0] = 1;
    expect->data[1][0] = 0;
    expect->data[2][0] = -1;

    FILE *f = fopen("unit_tests/data/3x1.txt", "r");

    matrix_t *got = NULL;
    err_t return_code = read_matrix_file(&got, f);

    ck_assert_int_eq(return_code, OK);
    ck_assert_uint_eq(expect->rows, got->rows);
    ck_assert_uint_eq(expect->columns, got->columns);
    for (size_t i = 0; i < got->rows; i++)
    {
        for (size_t j = 0; j < got->columns; j++)
        {
            ck_assert_double_eq_tol(got->data[i][j], expect->data[i][j], EPS);
        }
    }

    matrix_free(&expect);
    matrix_free(&got);
    fclose(f);
}
END_TEST

START_TEST(read_matrix_file_pos_1x3)
{
    matrix_t *expect = matrix_create(1, 3);
    expect->data[0][0] = 1;
    expect->data[0][1] = 0;
    expect->data[0][2] = -1;

    FILE *f = fopen("unit_tests/data/1x3.txt", "r");

    matrix_t *got = NULL;
    err_t return_code = read_matrix_file(&got, f);

    ck_assert_int_eq(return_code, OK);
    ck_assert_uint_eq(expect->rows, got->rows);
    ck_assert_uint_eq(expect->columns, got->columns);
    for (size_t i = 0; i < got->rows; i++)
    {
        for (size_t j = 0; j < got->columns; j++)
        {
            ck_assert_double_eq_tol(got->data[i][j], expect->data[i][j], EPS);
        }
    }

    matrix_free(&expect);
    matrix_free(&got);
    fclose(f);
}
END_TEST

START_TEST(read_matrix_file_pos_2x2)
{
    matrix_t *expect = matrix_create(2, 2);
    expect->data[0][0] = 1;
    expect->data[0][1] = 2;
    expect->data[1][0] = 3;
    expect->data[1][1] = 4;

    FILE *f = fopen("unit_tests/data/2x2.txt", "r");

    matrix_t *got = NULL;
    err_t return_code = read_matrix_file(&got, f);

    ck_assert_int_eq(return_code, OK);
    ck_assert_uint_eq(expect->rows, got->rows);
    ck_assert_uint_eq(expect->columns, got->columns);
    for (size_t i = 0; i < got->rows; i++)
    {
        for (size_t j = 0; j < got->columns; j++)
        {
            ck_assert_double_eq_tol(got->data[i][j], expect->data[i][j], EPS);
        }
    }

    matrix_free(&expect);
    matrix_free(&got);
    fclose(f);
}
END_TEST


//
// read_matrix_file negatives
//

START_TEST(read_matrix_file_neg_empty_file)
{
    FILE *f = fopen("unit_tests/data/empty.txt", "r");

    matrix_t *got = NULL;
    err_t return_code = read_matrix_file(&got, f);

    ck_assert_int_eq(return_code, ERR_FILE_READ);
    fclose(f);
}
END_TEST

START_TEST(read_matrix_file_neg_zero_size)
{
    FILE *f = fopen("unit_tests/data/zero_sizes.txt", "r");

    matrix_t *got = NULL;
    err_t return_code = read_matrix_file(&got, f);

    ck_assert_int_eq(return_code, ERR_FILE_READ);
    fclose(f);
}
END_TEST

START_TEST(read_matrix_file_neg_negative_size)
{
    FILE *f = fopen("unit_tests/data/neg_sizes.txt", "r");

    matrix_t *got = NULL;
    err_t return_code = read_matrix_file(&got, f);

    ck_assert_int_eq(return_code, ERR_FILE_READ);
    fclose(f);
}
END_TEST

START_TEST(read_matrix_file_neg_too_many_elements)
{
    FILE *f = fopen("unit_tests/data/elements_overflow.txt", "r");

    matrix_t *got = NULL;
    err_t return_code = read_matrix_file(&got, f);

    ck_assert_int_eq(return_code, ERR_FILE_READ);
    fclose(f);
}
END_TEST

START_TEST(read_matrix_file_neg_not_enough_elements)
{
    FILE *f = fopen("unit_tests/data/elements_lack.txt", "r");

    matrix_t *got = NULL;
    err_t return_code = read_matrix_file(&got, f);

    ck_assert_int_eq(return_code, ERR_FILE_READ);
    fclose(f);
}
END_TEST

START_TEST(read_matrix_file_neg_symbols)
{
    FILE *f = fopen("unit_tests/data/symbols.txt", "r");

    matrix_t *got = NULL;
    err_t return_code = read_matrix_file(&got, f);

    ck_assert_int_eq(return_code, ERR_FILE_READ);
    fclose(f);
}
END_TEST


//
// print_matrix_file positives
//

START_TEST(print_matrix_file_2x3)
{
    size_t rows = 2;
    size_t columns = 3;
    char *filename = "unit_tests/data/print_matrix_file_2x3.txt";

    matrix_t *expect = matrix_create(rows, columns);
    expect->data[0][0] = 1; expect->data[0][1] = 2; expect->data[0][2] = 3;
    expect->data[1][0] = 4; expect->data[1][1] = 5; expect->data[1][2] = 6;

    FILE *f = fopen(filename, "w");
    print_matrix_file(expect, f);
    fclose(f);

    matrix_t *got = NULL;
    f = fopen(filename, "r");
    err_t return_code = read_matrix_file(&got, f);

    ck_assert_int_eq(return_code, OK);
    ck_assert_uint_eq(expect->rows, got->rows);
    ck_assert_uint_eq(expect->columns, got->columns);
    for (size_t i = 0; i < got->rows; i++)
    {
        for (size_t j = 0; j < got->columns; j++)
        {
            ck_assert_double_eq_tol(got->data[i][j], expect->data[i][j], EPS);
        }
    }

    matrix_free(&got);
    matrix_free(&expect);
    fclose(f);
}
END_TEST

START_TEST(print_matrix_file_1x1)
{
    size_t rows = 1;
    size_t columns = 1;
    char *filename = "unit_tests/data/print_matrix_file_1x1.txt";

    matrix_t *expect = matrix_create(rows, columns);
    expect->data[0][0] = 333;

    FILE *f = fopen(filename, "w");
    print_matrix_file(expect, f);
    fclose(f);


    matrix_t *got = NULL;
    f = fopen(filename, "r");
    err_t return_code = read_matrix_file(&got, f);

    ck_assert_int_eq(return_code, OK);
    ck_assert_uint_eq(expect->rows, got->rows);
    ck_assert_uint_eq(expect->columns, got->columns);
    for (size_t i = 0; i < got->rows; i++)
    {
        for (size_t j = 0; j < got->columns; j++)
        {
            ck_assert_double_eq_tol(got->data[i][j], expect->data[i][j], EPS);
        }
    }

    matrix_free(&got);
    matrix_free(&expect);
    fclose(f);
}
END_TEST

START_TEST(print_matrix_file_1x3)
{
    size_t rows = 1;
    size_t columns = 3;
    char *filename = "unit_tests/data/print_matrix_file_1x3.txt";

    matrix_t *expect = matrix_create(rows, columns);
    expect->data[0][0] = -1; expect->data[0][1] = 0; expect->data[0][2] = 1;

    FILE *f = fopen(filename, "w");
    print_matrix_file(expect, f);
    fclose(f);

    matrix_t *got = NULL;
    f = fopen(filename, "r");
    err_t return_code = read_matrix_file(&got, f);

    ck_assert_int_eq(return_code, OK);
    ck_assert_uint_eq(expect->rows, got->rows);
    ck_assert_uint_eq(expect->columns, got->columns);
    for (size_t i = 0; i < got->rows; i++)
    {
        for (size_t j = 0; j < got->columns; j++)
        {
            ck_assert_double_eq_tol(got->data[i][j], expect->data[i][j], EPS);
        }
    }

    matrix_free(&got);
    matrix_free(&expect);
    fclose(f);
}
END_TEST


Suite *matrix_io_suite(void)
{
    Suite *s = suite_create("matrix_io");

    TCase *tc_read_matrix_file_pos = tcase_create("read_matrix_file positives");
    tcase_add_test(tc_read_matrix_file_pos, read_matrix_file_pos_1x1);
    tcase_add_test(tc_read_matrix_file_pos, read_matrix_file_pos_1x3);
    tcase_add_test(tc_read_matrix_file_pos, read_matrix_file_pos_3x1);
    tcase_add_test(tc_read_matrix_file_pos, read_matrix_file_pos_2x2);

    TCase *tc_read_matrix_file_neg = tcase_create("read_matrix_file negatives");
    tcase_add_test(tc_read_matrix_file_neg, read_matrix_file_neg_empty_file);
    tcase_add_test(tc_read_matrix_file_neg, read_matrix_file_neg_zero_size);
    tcase_add_test(tc_read_matrix_file_neg, read_matrix_file_neg_negative_size);
    tcase_add_test(tc_read_matrix_file_neg, read_matrix_file_neg_not_enough_elements);
    tcase_add_test(tc_read_matrix_file_neg, read_matrix_file_neg_too_many_elements);
    tcase_add_test(tc_read_matrix_file_neg, read_matrix_file_neg_symbols);

    TCase *tc_print_matrix_file = tcase_create("print_matrix_file positives");
    tcase_add_test(tc_read_matrix_file_pos, print_matrix_file_1x1);
    tcase_add_test(tc_read_matrix_file_pos, print_matrix_file_1x3);
    tcase_add_test(tc_read_matrix_file_pos, print_matrix_file_2x3);

    suite_add_tcase(s, tc_read_matrix_file_pos);
    suite_add_tcase(s, tc_read_matrix_file_neg);
    suite_add_tcase(s, tc_print_matrix_file);

    return s;
}
