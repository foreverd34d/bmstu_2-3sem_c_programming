#include <check.h>
#include <stdbool.h>

#include "check_main.h"
#include "tools.h"

//
// read_pos_double tests
//

// positives

START_TEST(read_pos_double_pos_usual)
{
    char *data = "123e-1";
    double expect = 123e-1;

    double got;
    int rc = read_pos_double(&got, data);

    ck_assert_int_eq(rc, 0);
    ck_assert_double_eq_tol(expect, got, EPS);
}
END_TEST

// negatives

START_TEST(read_pos_double_neg_space_str)
{
    char *data = "\n    \t";
    double got;
    int rc = read_pos_double(&got, data);
    ck_assert_int_eq(rc, 1);
}
END_TEST

START_TEST(read_pos_double_neg_no_double_in_str)
{
    char *data = "   abd";
    double got;
    int rc = read_pos_double(&got, data);
    ck_assert_int_eq(rc, 1);
}
END_TEST

START_TEST(read_pos_double_neg_symbols_after_double)
{
    char *data = "123.321   abd";
    double got;
    int rc = read_pos_double(&got, data);
    ck_assert_int_eq(rc, 1);
}
END_TEST

START_TEST(read_pos_double_neg_double_lt_zero)
{
    char *data = "-5.33";
    double got;
    int rc = read_pos_double(&got, data);
    ck_assert_int_eq(rc, 2);
}
END_TEST


//
// is_empty tests
//

START_TEST(is_empty_nonempty)
{
    char *str = "  \t \n a \n \t";
    bool result = is_empty(str);
    ck_assert_int_eq(result, false);
}
END_TEST

START_TEST(is_empty_spaces)
{
    char *str = "   \t \n \t \n \v ";
    bool result = is_empty(str);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(is_empty_empty)
{
    char *str = "";
    bool result = is_empty(str);
    ck_assert_int_eq(result, true);
}
END_TEST


//
// starts_with tests
//

START_TEST(starts_with_partitial_overlap)
{
    char *haystack = "foo";
    char *needle = "fo";
    bool result = starts_with(haystack, needle);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(starts_with_full_overlap)
{
    char *haystack = "foo";
    char *needle = "foo";
    bool result = starts_with(haystack, needle);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(starts_with_needle_gt_haystack)
{
    char *haystack = "foo";
    char *needle = "foobar";
    bool result = starts_with(haystack, needle);
    ck_assert_int_eq(result, false);
}
END_TEST

START_TEST(starts_with_no_overlap)
{
    char *haystack = "foo";
    char *needle = "bar";
    bool result = starts_with(haystack, needle);
    ck_assert_int_eq(result, false);
}
END_TEST


Suite *tools_suite(void)
{
    Suite *s = suite_create("tools");

    TCase *tc_read_pos_double_pos = tcase_create("read_pos_double pos");
    tcase_add_test(tc_read_pos_double_pos, read_pos_double_pos_usual);

    TCase *tc_read_pos_double_neg = tcase_create("read_pos_double neg");
    tcase_add_test(tc_read_pos_double_neg, read_pos_double_neg_double_lt_zero);
    tcase_add_test(tc_read_pos_double_neg, read_pos_double_neg_no_double_in_str);
    tcase_add_test(tc_read_pos_double_neg, read_pos_double_neg_space_str);
    tcase_add_test(tc_read_pos_double_neg, read_pos_double_neg_symbols_after_double);

    TCase *tc_is_empty = tcase_create("is_empty pos");
    tcase_add_test(tc_is_empty, is_empty_empty);
    tcase_add_test(tc_is_empty, is_empty_nonempty);
    tcase_add_test(tc_is_empty, is_empty_spaces);

    TCase *tc_starts_with = tcase_create("starts_with pos");
    tcase_add_test(tc_starts_with, starts_with_full_overlap);
    tcase_add_test(tc_starts_with, starts_with_no_overlap);
    tcase_add_test(tc_starts_with, starts_with_needle_gt_haystack);
    tcase_add_test(tc_starts_with, starts_with_partitial_overlap);

    suite_add_tcase(s, tc_read_pos_double_pos);
    suite_add_tcase(s, tc_read_pos_double_neg);
    suite_add_tcase(s, tc_starts_with);
    suite_add_tcase(s, tc_is_empty);

    return s;
}
