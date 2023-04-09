#include <check.h>

#include "check_main.h"
#include "matrix.h"
#include "matrix_operations.h"

#define EPS 1e-5

//
// matrix_addition positives
//

START_TEST(matrix_addition_pos_1x1)
{
    matrix_t *a = matrix_create(1, 1);
    matrix_t *b = matrix_create(1, 1);

    a->data[0][0] = 3;
    b->data[0][0] = 4;

    matrix_t *expect = matrix_create(1, 1);
    expect->data[0][0] = 7;

    matrix_t *got = matrix_addition(a, b);

    ck_assert_uint_eq(expect->rows, got->rows);
    ck_assert_uint_eq(expect->columns, got->columns);
    for (size_t i = 0; i < got->rows; i++)
    {
        for (size_t j = 0; j < got->columns; j++)
        {
            ck_assert_double_eq_tol(got->data[i][j], expect->data[i][j], EPS);
        }
    }

    matrix_free(&a);
    matrix_free(&b);
    matrix_free(&expect);
    matrix_free(&got);
}
END_TEST

START_TEST(matrix_addition_pos_2x3_second_matrix_zeros)
{
    matrix_t *a = matrix_create(2, 3);
    matrix_t *b = matrix_create(2, 3);

    a->data[0][0] = 1; a->data[0][1] = 2; a->data[0][2] = 3;
    a->data[1][0] = 4; a->data[1][1] = 5; a->data[1][2] = 6;

    b->data[0][0] = 0; b->data[0][1] = 0; b->data[0][2] = 0;
    b->data[1][0] = 0; b->data[1][1] = 0; b->data[1][2] = 0;

    matrix_t *expect = matrix_create(2, 3);

    expect->data[0][0] = 1; expect->data[0][1] = 2; expect->data[0][2] = 3;
    expect->data[1][0] = 4; expect->data[1][1] = 5; expect->data[1][2] = 6;

    matrix_t *got = matrix_addition(a, b);

    ck_assert_uint_eq(expect->rows, got->rows);
    ck_assert_uint_eq(expect->columns, got->columns);
    for (size_t i = 0; i < got->rows; i++)
    {
        for (size_t j = 0; j < got->columns; j++)
        {
            ck_assert_double_eq_tol(got->data[i][j], expect->data[i][j], EPS);
        }
    }

    matrix_free(&a);
    matrix_free(&b);
    matrix_free(&expect);
    matrix_free(&got);
}
END_TEST

START_TEST(matrix_addition_pos_2x3_usual)
{
    matrix_t *a = matrix_create(2, 3);
    matrix_t *b = matrix_create(2, 3);

    a->data[0][0] = 1; a->data[0][1] = 3; a->data[0][2] = 5;
    a->data[1][0] = 7; a->data[1][1] = 9; a->data[1][2] = 11;

    b->data[0][0] = 2; b->data[0][1] = 4; b->data[0][2] = 6;
    b->data[1][0] = 8; b->data[1][1] = 10; b->data[1][2] = 12;

    matrix_t *expect = matrix_create(2, 3);

    expect->data[0][0] = 3; expect->data[0][1] = 7; expect->data[0][2] = 11;
    expect->data[1][0] = 15; expect->data[1][1] = 19; expect->data[1][2] = 23;

    matrix_t *got = matrix_addition(a, b);

    ck_assert_uint_eq(expect->rows, got->rows);
    ck_assert_uint_eq(expect->columns, got->columns);
    for (size_t i = 0; i < got->rows; i++)
    {
        for (size_t j = 0; j < got->columns; j++)
        {
            ck_assert_double_eq_tol(got->data[i][j], expect->data[i][j], EPS);
        }
    }

    matrix_free(&a);
    matrix_free(&b);
    matrix_free(&expect);
    matrix_free(&got);
}
END_TEST

START_TEST(matrix_addition_pos_2x1_second_matrix_negative_numbers)
{
    matrix_t *a = matrix_create(2, 1);
    matrix_t *b = matrix_create(2, 1);

    a->data[0][0] = 3;
    a->data[1][0] = 4;

    b->data[0][0] = -4;
    b->data[1][0] = -3;

    matrix_t *expect = matrix_create(2, 1);

    expect->data[0][0] = -1;
    expect->data[1][0] = 1;

    matrix_t *got = matrix_addition(a, b);

    ck_assert_uint_eq(expect->rows, got->rows);
    ck_assert_uint_eq(expect->columns, got->columns);
    for (size_t i = 0; i < got->rows; i++)
    {
        for (size_t j = 0; j < got->columns; j++)
        {
            ck_assert_double_eq_tol(got->data[i][j], expect->data[i][j], EPS);
        }
    }

    matrix_free(&a);
    matrix_free(&b);
    matrix_free(&expect);
    matrix_free(&got);
}
END_TEST


//
// matrix_addition negatives
//

START_TEST(matrix_addition_neg_incompatible)
{
    matrix_t *a = matrix_create(2, 3);
    matrix_t *b = matrix_create(3, 3);

    matrix_t *got = matrix_addition(a, b);

    ck_assert_ptr_null(got);

    matrix_free(&a);
    matrix_free(&b);
}
END_TEST


//
// matrix_multiplication positives
//

START_TEST(multipty_matrices_pos_1x1)
{
    matrix_t *a = matrix_create(1, 1);
    matrix_t *b = matrix_create(1, 1);

    a->data[0][0] = 3;

    b->data[0][0] = 4;

    matrix_t *expect = matrix_create(1, 1);

    expect->data[0][0] = 12;

    matrix_t *got = matrix_multiplication(a, b);

    ck_assert_uint_eq(expect->rows, got->rows);
    ck_assert_uint_eq(expect->columns, got->columns);
    for (size_t i = 0; i < got->rows; i++)
    {
        for (size_t j = 0; j < got->columns; j++)
        {
            ck_assert_double_eq_tol(got->data[i][j], expect->data[i][j], EPS);
        }
    }

    matrix_free(&a);
    matrix_free(&b);
    matrix_free(&expect);
    matrix_free(&got);
}
END_TEST

START_TEST(multipty_matrices_pos_2x3_and_3x1)
{
    matrix_t *a = matrix_create(2, 3);
    matrix_t *b = matrix_create(3, 1);

    a->data[0][0] = 1; a->data[0][1] = 2; a->data[0][2] = 3;
    a->data[1][0] = 4; a->data[1][1] = 5; a->data[1][2] = 6;

    b->data[0][0] = 3;
    b->data[1][0] = 2;
    b->data[2][0] = -1;

    matrix_t *expect = matrix_create(2, 1);

    expect->data[0][0] = 4;
    expect->data[1][0] = 16;

    matrix_t *got = matrix_multiplication(a, b);

    ck_assert_uint_eq(expect->rows, got->rows);
    ck_assert_uint_eq(expect->columns, got->columns);
    for (size_t i = 0; i < got->rows; i++)
    {
        for (size_t j = 0; j < got->columns; j++)
        {
            ck_assert_double_eq_tol(got->data[i][j], expect->data[i][j], EPS);
        }
    }

    matrix_free(&a);
    matrix_free(&b);
    matrix_free(&expect);
    matrix_free(&got);
}
END_TEST

//
// matrix_multiplication negatives
//

START_TEST(matrix_multiplication_neg_incompatible)
{
    matrix_t *a = matrix_create(2, 3);
    matrix_t *b = matrix_create(4, 3);

    matrix_t *got = matrix_multiplication(a, b);

    ck_assert_ptr_null(got);

    matrix_free(&a);
    matrix_free(&b);
}
END_TEST


//
// matrix_minor positives
//

START_TEST(matrix_minor_pos_2x2_first_el)
{
    matrix_t *a = matrix_create(2, 2);

    a->data[0][0] = 1; a->data[0][1] = 2;
    a->data[1][0] = 3; a->data[1][1] = 4;

    matrix_t *expect = matrix_create(1, 1);

    expect->data[0][0] = 4;

    matrix_t *got = matrix_minor(a, 0, 0);

    ck_assert_uint_eq(expect->rows, got->rows);
    ck_assert_uint_eq(expect->columns, got->columns);
    for (size_t i = 0; i < got->rows; i++)
    {
        for (size_t j = 0; j < got->columns; j++)
        {
            ck_assert_double_eq_tol(got->data[i][j], expect->data[i][j], EPS);
        }
    }

    matrix_free(&a);
    matrix_free(&expect);
    matrix_free(&got);
}
END_TEST

START_TEST(matrix_minor_pos_3x3_middle_el)
{
    matrix_t *a = matrix_create(3, 3);

    a->data[0][0] = 1; a->data[0][1] = 2; a->data[0][2] = 3;
    a->data[1][0] = 4; a->data[1][1] = 5; a->data[1][2] = 6;
    a->data[2][0] = 7; a->data[2][1] = 8; a->data[2][2] = 9;

    matrix_t *expect = matrix_create(2, 2);

    expect->data[0][0] = 1; expect->data[0][1] = 3;
    expect->data[1][0] = 7; expect->data[1][1] = 9;

    matrix_t *got = matrix_minor(a, 1, 1);

    ck_assert_uint_eq(expect->rows, got->rows);
    ck_assert_uint_eq(expect->columns, got->columns);
    for (size_t i = 0; i < got->rows; i++)
    {
        for (size_t j = 0; j < got->columns; j++)
        {
            ck_assert_double_eq_tol(got->data[i][j], expect->data[i][j], EPS);
        }
    }

    matrix_free(&a);
    matrix_free(&expect);
    matrix_free(&got);
}
END_TEST


//
// matrix_determinant positives
//

START_TEST(matrix_determinant_2x2)
{
    matrix_t *a = matrix_create(2, 2);

    a->data[0][0] = 1; a->data[0][1] = 2;
    a->data[1][0] = 3; a->data[1][1] = 4;

    matrix_el_t expect = -2;
    matrix_el_t got = matrix_determinant(a);

    ck_assert_double_eq_tol(got, expect, EPS);

    matrix_free(&a);
}
END_TEST

START_TEST(matrix_determinant_1x1)
{
    matrix_t *a = matrix_create(1, 1);

    a->data[0][0] = 727.727;

    matrix_el_t expect = a->data[0][0];
    matrix_el_t got = matrix_determinant(a);

    ck_assert_double_eq_tol(got, expect, EPS);

    matrix_free(&a);
}
END_TEST

START_TEST(matrix_determinant_3x3)
{
    matrix_t *a = matrix_create(3, 3);

    a->data[0][0] = 1; a->data[0][1] = 2; a->data[0][2] = 3;
    a->data[1][0] = 4; a->data[1][1] = 5; a->data[1][2] = 6;
    a->data[2][0] = 7; a->data[2][1] = 8; a->data[2][2] = 9;

    matrix_el_t expect = 0;
    matrix_el_t got = matrix_determinant(a);

    ck_assert_double_eq_tol(got, expect, EPS);

    matrix_free(&a);
}
END_TEST

START_TEST(matrix_determinant_4x4)
{
    matrix_t *a = matrix_create(4, 4);

    a->data[0][0] = 1; a->data[0][1] = 2; a->data[0][2] = 3; a->data[0][3] = 123;
    a->data[1][0] = 4; a->data[1][1] = 5; a->data[1][2] = 8; a->data[1][3] = 321;
    a->data[2][0] = 7; a->data[2][1] = 8; a->data[2][2] = 9; a->data[2][3] = 1.1;
    a->data[3][0] = 90; a->data[3][1] = 8; a->data[3][2] = 7; a->data[3][3] = 101;

    matrix_el_t expect = 38327.9;
    matrix_el_t got = matrix_determinant(a);

    ck_assert_double_eq_tol(got, expect, EPS);

    matrix_free(&a);
}
END_TEST

START_TEST(matrix_determinant_identity_matrix)
{
    matrix_t *a = matrix_create(3, 3);

    a->data[0][0] = 1; a->data[0][1] = 0; a->data[0][2] = 0;
    a->data[1][0] = 0; a->data[1][1] = 1; a->data[1][2] = 0;
    a->data[2][0] = 0; a->data[2][1] = 0; a->data[2][2] = 1;

    matrix_el_t expect = 1;
    matrix_el_t got = matrix_determinant(a);

    ck_assert_double_eq_tol(got, expect, EPS);

    matrix_free(&a);
}
END_TEST


Suite *matrix_operations_suite(void)
{
    Suite *s = suite_create("matrix_operations");

    TCase *tc_matrix_addition_pos = tcase_create("matrix_addition positives");
    tcase_add_test(tc_matrix_addition_pos, matrix_addition_pos_1x1);
    tcase_add_test(tc_matrix_addition_pos, matrix_addition_pos_2x3_usual);
    tcase_add_test(tc_matrix_addition_pos, matrix_addition_pos_2x3_second_matrix_zeros);
    tcase_add_test(tc_matrix_addition_pos, matrix_addition_pos_2x1_second_matrix_negative_numbers);

    TCase *tc_matrix_addition_neg = tcase_create("matrix_addiction negatives");
    tcase_add_test(tc_matrix_addition_neg, matrix_addition_neg_incompatible);

    TCase *tc_matrix_multiplication_pos = tcase_create("matrix_multiplication positives");
    tcase_add_test(tc_matrix_multiplication_pos, multipty_matrices_pos_1x1);
    tcase_add_test(tc_matrix_multiplication_pos, multipty_matrices_pos_2x3_and_3x1);

    TCase *tc_matrix_multiplication_neg = tcase_create("matrix_multiplication negatives");
    tcase_add_test(tc_matrix_multiplication_neg, matrix_multiplication_neg_incompatible);

    TCase *tc_matrix_minor = tcase_create("matrix_minor positives");
    tcase_add_test(tc_matrix_minor, matrix_minor_pos_2x2_first_el);
    tcase_add_test(tc_matrix_minor, matrix_minor_pos_3x3_middle_el);

    TCase *tc_matrix_determinant = tcase_create("matrix_determinant positives");
    tcase_add_test(tc_matrix_determinant, matrix_determinant_1x1);
    tcase_add_test(tc_matrix_determinant, matrix_determinant_2x2);
    tcase_add_test(tc_matrix_determinant, matrix_determinant_3x3);
    tcase_add_test(tc_matrix_determinant, matrix_determinant_4x4);
    tcase_add_test(tc_matrix_determinant, matrix_determinant_identity_matrix);

    suite_add_tcase(s, tc_matrix_addition_pos);
    suite_add_tcase(s, tc_matrix_addition_neg);
    suite_add_tcase(s, tc_matrix_multiplication_pos);
    suite_add_tcase(s, tc_matrix_multiplication_neg);
    suite_add_tcase(s, tc_matrix_minor);
    suite_add_tcase(s, tc_matrix_determinant);

    return s;
}
