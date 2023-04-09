#include <stdlib.h>
#include <check.h>

#include "check_main.h"
#include "error_codes.h"
#include "items.h"

//
// items_free tests
//

START_TEST(items_free_nonnull)
{
    size_t items_len = 2;
    item_t *data = calloc(items_len, sizeof(item_t));
    data[0].name = strdup("a"); data[0].weight = 1; data[0].volume = 1;
    data[1].name = strdup("b"); data[1].weight = 1; data[1].volume = 1;

    items_free(&data, items_len);

    ck_assert_ptr_null(data);
}
END_TEST

START_TEST(items_free_null)
{
    item_t *data = NULL;

    items_free(&data, 0);

    ck_assert_ptr_null(data);
}
END_TEST

START_TEST(items_free_one_item_uninit)
{
    size_t items_len = 3;
    item_t *data = calloc(items_len, sizeof(item_t));
    data[0].name = strdup("a"); data[0].weight = 1; data[0].volume = 1;
    data[1].name = strdup("b"); data[1].weight = 2; data[1].volume = 2;

    items_free(&data, items_len);

    ck_assert_ptr_null(data);
}
END_TEST


//
// item_duplicate tests
//

START_TEST(item_duplicate_usual)
{
    item_t a;
    a.name = strdup("a");
    a.weight = 1;
    a.volume = 1;

    item_t got;
    int rc = item_duplicate(&got, a);

    ck_assert_int_eq(rc, OK);
    assert_item_eq(a, got);
    ck_assert_ptr_ne(a.name, got.name);

    free(a.name);
    free(got.name);
}
END_TEST

Suite *items_suite(void)
{
    Suite *s = suite_create("items");

    TCase *tc_item_duplicate = tcase_create("item_duplicate pos");
    tcase_add_test(tc_item_duplicate, item_duplicate_usual);

    TCase *tc_items_free = tcase_create("items_free pos");
    tcase_add_test(tc_items_free, items_free_nonnull);
    tcase_add_test(tc_items_free, items_free_null);
    tcase_add_test(tc_items_free, items_free_one_item_uninit);

    suite_add_tcase(s, tc_items_free);
    suite_add_tcase(s, tc_item_duplicate);
    
    return s;
}
