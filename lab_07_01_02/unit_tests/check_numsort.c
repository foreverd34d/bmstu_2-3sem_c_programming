#include <check.h>
#include <stdlib.h>
#include "../inc/numsort.h"
#include "../inc/check_main.h"

//
// comp positives
//

START_TEST(comp_int_a_gt_b)
{
    int a = 10;
    int b = 9;

    void *x = &a;
    void *y = &b;

    ck_assert_int_gt(comp_int(x, y), 0);
}
END_TEST

START_TEST(comp_int_a_lt_b)
{
    int a = -11;
    int b = 10;

    void *x = &a;
    void *y = &b;

    ck_assert_int_lt(comp_int(x, y), 0);
}
END_TEST

START_TEST(comp_int_a_eq_b)
{
    int a = 1;
    int b = 1;

    void *x = &a;
    void *y = &b;

    ck_assert_int_eq(comp_int(x, y), 0);
}
END_TEST


//
// swap positives
//

START_TEST(swap_test)
{
    int a, old_a;
    int b, old_b;

    old_a = a = 10;
    old_b = b = 10;

    swap(&a, &b, sizeof(int));

    ck_assert_int_eq(a, old_a);
    ck_assert_int_eq(b, old_b);
}
END_TEST


//
// mysort positives
//

START_TEST(mysort_usual_arr)
{
    int a[] = { 4, 2, 5, 1, 3 };
    int sorted[] = { 1, 2, 3, 4, 5 };

    mysort(a, sizeof(a)/sizeof(a[0]), sizeof(int), comp_int);

    ck_assert_mem_eq(a, sorted, sizeof(a));
}
END_TEST

START_TEST(mysort_single_el)
{
    int a[] = { 1 };
    int sorted[] = { 1 };

    mysort(a, sizeof(a)/sizeof(a[0]), sizeof(int), comp_int);

    ck_assert_mem_eq(a, sorted, sizeof(a));
}
END_TEST

START_TEST(mysort_sorted_arr)
{
    int a[] = { 1, 2, 3, 4, 5, 6 };
    int sorted[] = { 1, 2, 3, 4, 5, 6 };

    mysort(a, sizeof(a)/sizeof(a[0]), sizeof(int), comp_int);

    ck_assert_mem_eq(a, sorted, sizeof(a));
}
END_TEST

START_TEST(mysort_reversed_order_arr)
{
    int a[] = { 6, 5, 4, 3, 2, 1 };
    int sorted[] = { 1, 2, 3, 4, 5, 6 };

    mysort(a, sizeof(a)/sizeof(a[0]), sizeof(int), comp_int);

    ck_assert_mem_eq(a, sorted, sizeof(a));
}
END_TEST

START_TEST(mysort_all_elements_equal)
{
    int a[] = { 1, 1, 1, 1, 1, 1 };
    int sorted[] = { 1, 1, 1, 1, 1, 1 };

    mysort(a, sizeof(a)/sizeof(a[0]), sizeof(int), comp_int);

    ck_assert_mem_eq(a, sorted, sizeof(a));
}
END_TEST

START_TEST(mysort_dynamic_array)
{
    int len = 4;

    int *a = malloc(sizeof(int) * len);
    a[0] = 0;
    a[1] = 1;
    a[2] = 0;
    a[3] = 1;

    int *sorted = malloc(sizeof(int) * len);
    sorted[0] = 0;
    sorted[1] = 0;
    sorted[2] = 1;
    sorted[3] = 1;

    mysort(a, len, sizeof(int), comp_int);

    ck_assert_mem_eq(a, sorted, len * sizeof(int));
    free(sorted);
    free(a);
}
END_TEST

START_TEST(mysort_two_elements)
{
    int a[] = { 2, 1 };
    int sorted[] = { 1, 2 };

    mysort(a, sizeof(a)/sizeof(*a), sizeof(int), comp_int);

    ck_assert_mem_eq(a, sorted, sizeof(a));
}
END_TEST

START_TEST(mysort_empty_array)
{
    int len = 0;
    int *a = malloc(sizeof(int) * len);
    int *sorted = malloc(sizeof(int) * len);

    mysort(a, len, sizeof(int), comp_int);

    ck_assert_mem_eq(a, sorted, sizeof(int) * len);

    free(a);
    free(sorted);
}


Suite *numsort_suite(void)
{
    Suite *s = suite_create("numsort");

    TCase *tc_comp = tcase_create("comp positives");
    tcase_add_test(tc_comp, comp_int_a_eq_b);
    tcase_add_test(tc_comp, comp_int_a_gt_b);
    tcase_add_test(tc_comp, comp_int_a_lt_b);

    TCase *tc_swap = tcase_create("swap positives");
    tcase_add_test(tc_swap, swap_test);

    TCase *tc_sort = tcase_create("sort positives");
    tcase_add_test(tc_sort, mysort_usual_arr);
    tcase_add_test(tc_sort, mysort_single_el);
    tcase_add_test(tc_sort, mysort_reversed_order_arr);
    tcase_add_test(tc_sort, mysort_sorted_arr);
    tcase_add_test(tc_sort, mysort_all_elements_equal);
    tcase_add_test(tc_sort, mysort_two_elements);
    tcase_add_test(tc_sort, mysort_dynamic_array);
    tcase_add_test(tc_sort, mysort_empty_array);

    suite_add_tcase(s, tc_comp);
    suite_add_tcase(s, tc_swap);
    suite_add_tcase(s, tc_sort);

    return s;
}
