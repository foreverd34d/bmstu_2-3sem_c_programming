#include <check.h>

#include "check_main.h"
#include "item_utils.h"
#include "items.h"

#define EPS 1e-5

//
// sort_by_density tests
//

START_TEST(sort_by_density_usual)
{
    item_t data[3] = {
        { "a", 100, 100 },
        { "b", 1, 100 },
        { "c", 100, 1 },
    };

    item_t expect[3] = {
        { "b", 1, 100 },
        { "a", 100, 100 },
        { "c", 100, 1 },
    };

    sort_by_density(data, 3);

    assert_items_arr_eq(data, expect, 3);
}
END_TEST

START_TEST(sort_by_density_sorted)
{
    item_t data[3] = {
        { "a", 1, 100 },
        { "b", 100, 100 },
        { "c", 100, 1 },
    };

    item_t expect[3] = {
        { "a", 1, 100 },
        { "b", 100, 100 },
        { "c", 100, 1 },
    };

    sort_by_density(data, 3);

    assert_items_arr_eq(data, expect, 3);
}
END_TEST

START_TEST(sort_by_density_reversed)
{
    item_t data[3] = {
        { "a", 100, 1 },
        { "b", 100, 100 },
        { "c", 1, 100 },
    };

    item_t expect[3] = {
        { "c", 1, 100 },
        { "b", 100, 100 },
        { "a", 100, 1 },
    };

    sort_by_density(data, 3);

    assert_items_arr_eq(data, expect, 3);
}
END_TEST

START_TEST(sort_by_density_single_el)
{
    item_t data[1] = { { "a", 100, 100 } };
    item_t expect[1] = { { "a", 100, 100 } };

    sort_by_density(data, 1);

    assert_items_arr_eq(data, expect, 1);
}
END_TEST

START_TEST(sort_by_density_empty_array)
{
    item_t *data = NULL;

    sort_by_density(data, 0);

    ck_assert_ptr_null(data);
}
END_TEST


//
// get_density tests
//

START_TEST(get_density_equal)
{
    item_t a = { .weight = 100, .volume = 100 };
    double result = get_density(a);
    ck_assert_double_eq_tol(result, 1, EPS);
}
END_TEST


//
// swap_items tests
//

START_TEST(swap_items_usual)
{
    item_t a = { "a", 1, 2 };
    item_t b = { "b", 3, 4 };

    item_t a_old = a, b_old = b;

    swap_items(&a, &b);

    assert_item_eq(a, b_old);
    assert_item_eq(b, a_old);
}
END_TEST

START_TEST(swap_items_same_var)
{
    item_t a = { "a", 1, 1 };
    item_t a_old = a;

    swap_items(&a, &a);

    assert_item_eq(a, a_old);
}
END_TEST


//
// filter_by_prefix tests
//

// positives

START_TEST(filter_by_prefix_pos_usual)
{
    item_t data[4] = {
        { "obj1", 1, 1 },
        { "obj2", 2, 2 },
        { "obj10", 3, 3 },
        { "obj20", 4, 4 },
    };

    item_t expect[2] = {
        { "obj1", 1, 1 },
        { "obj10", 3, 3 },
    };

    item_t *got = NULL;
    int got_len = 0;
    got_len = filter_by_prefix(&got, got_len, data, 4, "obj1");

    ck_assert_int_eq(got_len, 2);
    assert_items_arr_eq(got, expect, got_len);

    items_free(&got, got_len);
}
END_TEST

START_TEST(filter_by_prefix_pos_all_elements)
{
    item_t data[4] = {
        { "obj1", 1, 1 },
        { "obj2", 2, 2 },
        { "obj10", 3, 3 },
        { "obj20", 4, 4 },
    };

    item_t expect[4] = {
        { "obj1", 1, 1 },
        { "obj2", 2, 2 },
        { "obj10", 3, 3 },
        { "obj20", 4, 4 },
    };

    item_t *got = NULL;
    int got_len = 0;
    got_len = filter_by_prefix(&got, got_len, data, 4, "obj");

    ck_assert_int_eq(got_len, 4);
    assert_items_arr_eq(got, expect, got_len);

    items_free(&got, got_len);
}
END_TEST

START_TEST(filter_by_prefix_pos_no_elements)
{
    item_t data[4] = {
        { "obj1", 1, 1 },
        { "obj2", 2, 2 },
        { "obj10", 3, 3 },
        { "obj20", 4, 4 },
    };

    item_t *got = NULL;
    int got_len = 0;
    got_len = filter_by_prefix(&got, got_len, data, 4, "obd");

    ck_assert_int_eq(got_len, 0);

    items_free(&got, got_len);
}
END_TEST

START_TEST(filter_by_prefix_prefix_eq_name)
{
    item_t data[2] = {
        { "obj1", 1, 1 },
        { "obj2", 2, 2 },
    };

    item_t expect[1] = {
        { "obj1", 1, 1 },
    };

    item_t *got = NULL;
    int got_len = 0;
    got_len = filter_by_prefix(&got, got_len, data, 2, "obj1");

    ck_assert_int_eq(got_len, 1);
    assert_items_arr_eq(got, expect, got_len);

    items_free(&got, got_len);
}
END_TEST

START_TEST(filter_by_prefix_pos_ALL)
{
    item_t data[5] = {
        { "a", 100, 100 },
        { "b", 1, 100 },
        { "c", 100, 1 },
        { "All", 5, 5 },
        { "ALL", 6, 6 },
    };

    item_t expect[5] = {
        { "a", 100, 100 },
        { "b", 1, 100 },
        { "c", 100, 1 },
        { "All", 5, 5 },
        { "ALL", 6, 6 },
    };

    item_t *got = NULL;
    int got_len = 0;
    got_len = filter_by_prefix(&got, got_len, data, 5, "ALL");

    ck_assert_int_eq(got_len, 5);
    assert_items_arr_eq(got, expect, got_len);

    items_free(&got, got_len);
}
END_TEST

START_TEST(filter_by_prefix_pos_All)
{
    item_t data[5] = {
        { "a", 100, 100 },
        { "b", 1, 100 },
        { "c", 100, 1 },
        { "All", 5, 5 },
        { "ALL", 6, 6 },
    };

    item_t expect[1] = {
        { "All", 5, 5 },
    };

    item_t *got = NULL;
    int got_len = 0;
    got_len = filter_by_prefix(&got, got_len, data, 5, "All");

    ck_assert_int_eq(got_len, 1);
    assert_items_arr_eq(got, expect, got_len);

    items_free(&got, got_len);
}
END_TEST


Suite *item_utils_suite(void)
{
    Suite *s = suite_create("item_utils");

    TCase *tc_sort_by_density = tcase_create("sort_by_density pos");
    tcase_add_test(tc_sort_by_density, sort_by_density_usual);
    tcase_add_test(tc_sort_by_density, sort_by_density_sorted);
    tcase_add_test(tc_sort_by_density, sort_by_density_reversed);
    tcase_add_test(tc_sort_by_density, sort_by_density_single_el);
    tcase_add_test(tc_sort_by_density, sort_by_density_empty_array);

    TCase *tc_get_density = tcase_create("get_density pos");
    tcase_add_test(tc_get_density, get_density_equal);

    TCase *tc_swap_items = tcase_create("swap_items pos");
    tcase_add_test(tc_swap_items, swap_items_usual);
    tcase_add_test(tc_swap_items, swap_items_same_var);

    TCase *tc_filter_by_prefix = tcase_create("filter_by_prefix pos");
    tcase_add_test(tc_filter_by_prefix, filter_by_prefix_pos_usual);
    tcase_add_test(tc_filter_by_prefix, filter_by_prefix_pos_all_elements);
    tcase_add_test(tc_filter_by_prefix, filter_by_prefix_pos_no_elements);
    tcase_add_test(tc_filter_by_prefix, filter_by_prefix_pos_ALL);
    tcase_add_test(tc_filter_by_prefix, filter_by_prefix_pos_All);
    tcase_add_test(tc_filter_by_prefix, filter_by_prefix_prefix_eq_name);

    suite_add_tcase(s, tc_sort_by_density);
    suite_add_tcase(s, tc_get_density);
    suite_add_tcase(s, tc_swap_items);
    suite_add_tcase(s, tc_filter_by_prefix);

    return s;
}
