#include "check_main.h"
#include "list.h"
#include <check.h>
#include <stdlib.h>

//
// node_create tests
//

START_TEST(node_create_nonnull)
{
    int dummy;
    node_t *node = node_create(&dummy);

    ck_assert_ptr_nonnull(node);
    ck_assert_ptr_eq(&dummy, node_get_data(node));

    list_free(node, NULL);
}
END_TEST

START_TEST(node_create_null)
{
    void *ptr = NULL;
    node_t *node = node_create(ptr);

    ck_assert_ptr_nonnull(node);
    ck_assert_ptr_eq(ptr, node_get_data(node));

    list_free(node, NULL);
}
END_TEST


//
// list_free tests
//

START_TEST(list_free_nonnull_single)
{
    int *ptr = malloc(sizeof(int));
    *ptr = 1;

    node_t *node = node_create(ptr);

    list_free(node, free);
}
END_TEST

START_TEST(list_free_nonnull)
{
    node_t *head = NULL;
    for (size_t i = 0; i < 4; i++)
    {
        int *ptr = malloc(sizeof(int));
        *ptr = i;
        node_t *node_new = node_create(ptr);
        append(&head, &node_new);
    }

    list_free(head, free);
}
END_TEST

START_TEST(list_free_null_head)
{
    node_t *head = NULL;

    list_free(head, free);
}
END_TEST

START_TEST(list_free_null_data_free)
{
    node_t *head = NULL;
    int dummy;
    for (size_t i = 0; i < 4; i++)
    {
        node_t *node_new = node_create(&dummy);
        append(&head, &node_new);
    }

    list_free(head, NULL);
}
END_TEST


//
// node_get_data tests
//

START_TEST(node_get_data_nonnull)
{
    int dummy;
    node_t *node = node_create(&dummy);

    ck_assert_ptr_nonnull(node);
    ck_assert_ptr_eq(&dummy, node_get_data(node));

    list_free(node, NULL);
}
END_TEST

START_TEST(node_get_data_null)
{
    node_t *node = NULL;

    ck_assert_ptr_eq(NULL, node_get_data(node));
}
END_TEST


//
// node_get_next tests
//

START_TEST(node_get_next_nonnull)
{
    int dummy;
    node_t *head = node_create(&dummy);
    node_t *next = node_create(&dummy);
    node_t *next_ptr = next;

    append(&head, &next_ptr);

    ck_assert_ptr_nonnull(head);
    ck_assert_ptr_nonnull(next);
    ck_assert_ptr_eq(next, node_get_next(head));

    list_free(head, NULL);
}
END_TEST

START_TEST(node_get_next_null_next)
{
    int dummy;
    node_t *head = node_create(&dummy);
    node_t *next = NULL;
    node_t *next_ptr = next;
    append(&head, &next_ptr);

    ck_assert_ptr_nonnull(head);
    ck_assert_ptr_null(next);
    ck_assert_ptr_eq(next, node_get_next(head));

    list_free(head, NULL);
}
END_TEST


START_TEST(node_get_next_null_head)
{
    node_t *head = NULL;

    ck_assert_ptr_eq(NULL, node_get_next(head));
}
END_TEST


//
// list_len tests
//

START_TEST(list_len_usual)
{
    node_t *head = NULL;
    size_t len = 4;
    for (size_t i = 0; i < len; i++)
    {
        node_t *node_new = node_create(&len);
        append(&head, &node_new);
    }

    ck_assert_uint_eq(len, list_len(head));

    list_free(head, NULL);
}
END_TEST

START_TEST(list_len_one)
{
    node_t *head = NULL;
    size_t len = 1;
    for (size_t i = 0; i < len; i++)
    {
        node_t *node_new = node_create(&len);
        append(&head, &node_new);
    }

    ck_assert_uint_eq(len, list_len(head));

    list_free(head, NULL);
}
END_TEST

START_TEST(list_len_zero)
{
    node_t *head = NULL;
    size_t len = 0;
    for (size_t i = 0; i < len; i++)
    {
        node_t *node_new = node_create(&len);
        append(&head, &node_new);
    }

    ck_assert_uint_eq(len, list_len(head));

    list_free(head, NULL);
}
END_TEST


//
// find tests
//

int ptr_comp(const void *a, const void *b)
{
    return (char *) a - (char *) b;
}

int int_cmp(const void *a, const void *b)
{
    const int x = * (int *) a;
    const int y = * (int *) b;
    return x - y;
}

START_TEST(find_middle)
{
    size_t len = 4;
    int nums[4] = { 1, 2, 3, 4 };

    node_t *head = NULL;
    for (size_t i = 0; i < len; i++)
    {
        node_t *new = node_create(nums + i);
        append(&head, &new);
    }

    ck_assert_ptr_eq(nums + 1, node_get_data(find(head, nums + 1, int_cmp)));

    list_free(head, NULL);
}
END_TEST

START_TEST(find_beg)
{
    size_t len = 4;
    int nums[4] = { 1, 2, 3, 4 };

    node_t *head = NULL;
    for (size_t i = 0; i < len; i++)
    {
        node_t *new = node_create(nums + i);
        append(&head, &new);
    }

    ck_assert_ptr_eq(nums, node_get_data(find(head, nums, int_cmp)));

    list_free(head, NULL);
}
END_TEST

START_TEST(find_end)
{
    size_t len = 4;
    int nums[4] = { 1, 2, 3, 4 };

    node_t *head = NULL;
    for (size_t i = 0; i < len; i++)
    {
        node_t *new = node_create(nums + i);
        append(&head, &new);
    }

    ck_assert_ptr_eq(nums + 3, node_get_data(find(head, nums + 3, int_cmp)));

    list_free(head, NULL);
}
END_TEST

START_TEST(find_single_el)
{
    size_t len = 1;
    int nums[1] = { 1 };

    node_t *head = NULL;
    for (size_t i = 0; i < len; i++)
    {
        node_t *new = node_create(nums + i);
        append(&head, &new);
    }

    ck_assert_ptr_eq(nums, node_get_data(find(head, nums, int_cmp)));

    list_free(head, NULL);
}
END_TEST

START_TEST(find_no_result)
{
    size_t len = 4;
    int nums[4] = { 1, 2, 3, 4 };

    node_t *head = NULL;
    for (size_t i = 0; i < len - 1; i++)
    {
        node_t *new = node_create(nums + i);
        append(&head, &new);
    }

    ck_assert_ptr_null(node_get_data(find(head, nums + len - 1, int_cmp)));

    list_free(head, NULL);
}
END_TEST

START_TEST(find_null_head)
{
    node_t *head = NULL;

    ck_assert_ptr_eq(NULL, node_get_data(find(head, NULL, int_cmp)));
}
END_TEST


//
// pop_front tests
//

START_TEST(pop_front_usual)
{
    size_t len = 4;
    int nums[4] = { 1, 2, 3, 4 };

    node_t *head = NULL;
    for (size_t i = 0; i < len; i++)
    {
        node_t *new = node_create(nums + i);
        append(&head, &new);
    }

    int *head_data = pop_front(&head);

    ck_assert_ptr_eq(nums, head_data);
    ck_assert_ptr_eq(nums + 1, node_get_data(head));

    list_free(head, NULL);
}
END_TEST

START_TEST(pop_front_single_el)
{
    int dummy;
    node_t *head = node_create(&dummy);

    void *head_data = pop_front(&head);

    ck_assert_ptr_eq(&dummy, head_data);
    ck_assert_ptr_null(head);
}
END_TEST

START_TEST(pop_front_null_head)
{
    node_t *head = NULL;
    void *head_data = pop_front(&head);
    ck_assert_ptr_null(head_data);
}
END_TEST


//
// append tests
//

START_TEST(append_two_lists)
{
    node_t *head_a = NULL;
    size_t len = 4;
    int nums[4] = { 1, 2, 3, 4 };

    size_t i = 0;
    for (; i < len / 2; i++)
    {
        node_t *new = node_create(nums + i);
        append(&head_a, &new);
    }

    node_t *head_b = NULL;
    for (; i < len; i++)
    {
        node_t *new = node_create(nums + i);
        append(&head_b, &new);
    }

    append(&head_a, &head_b);

    ck_assert_ptr_nonnull(head_a);
    ck_assert_ptr_null(head_b);

    ck_assert_uint_eq(len, list_len(head_a));

    i = 0;
    for (node_t *cur = head_a; cur; cur = node_get_next(cur), i++)
    {
        ck_assert_ptr_eq(node_get_data(cur), nums + i);
    }

    list_free(head_a, NULL);
}
END_TEST

START_TEST(append_first_list_null)
{
    int dummy;
    node_t *head_a = NULL;
    node_t *head_b = node_create(&dummy);

    append(&head_a, &head_b);

    ck_assert_ptr_nonnull(head_a);
    ck_assert_ptr_null(head_b);
    ck_assert_uint_eq(1, list_len(head_a));
    ck_assert_ptr_eq(&dummy, node_get_data(head_a));

    list_free(head_a, NULL);
}
END_TEST

START_TEST(append_second_head_null)
{
    int dummy;
    node_t *head_a = node_create(&dummy);
    node_t *head_b = NULL;

    append(&head_a, &head_b);

    ck_assert_ptr_nonnull(head_a);
    ck_assert_ptr_null(head_b);
    ck_assert_uint_eq(1, list_len(head_a));
    ck_assert_ptr_eq(&dummy, node_get_data(head_a));

    list_free(head_a, NULL);
}
END_TEST

START_TEST(append_two_heads_null)
{
    node_t *head_a = NULL;
    node_t *head_b = NULL;

    append(&head_a, &head_b);

    ck_assert_ptr_null(head_a);
    ck_assert_ptr_null(head_b);
}
END_TEST


Suite *list_suite(void)
{
    Suite *s = suite_create("list");

    TCase *tc_node_create = tcase_create("node_create");
    tcase_add_test(tc_node_create, node_create_nonnull);
    tcase_add_test(tc_node_create, node_create_null);

    TCase *tc_list_free = tcase_create("list_free");
    tcase_add_test(tc_list_free, list_free_nonnull);
    tcase_add_test(tc_list_free, list_free_nonnull_single);
    tcase_add_test(tc_list_free, list_free_null_data_free);
    tcase_add_test(tc_list_free, list_free_null_head);

    TCase *tc_node_get_next = tcase_create("node_get_next");
    tcase_add_test(tc_node_get_next, node_get_next_nonnull);
    tcase_add_test(tc_node_get_next, node_get_next_null_head);
    tcase_add_test(tc_node_get_next, node_get_next_null_next);

    TCase *tc_node_get_data = tcase_create("node_get_data");
    tcase_add_test(tc_node_get_data, node_get_data_nonnull);
    tcase_add_test(tc_node_get_data, node_get_data_null);

    TCase *tc_list_len = tcase_create("list_len");
    tcase_add_test(tc_list_len, list_len_one);
    tcase_add_test(tc_list_len, list_len_usual);
    tcase_add_test(tc_list_len, list_len_zero);

    TCase *tc_find = tcase_create("find");
    tcase_add_test(tc_find, find_beg);
    tcase_add_test(tc_find, find_end);
    tcase_add_test(tc_find, find_middle);
    tcase_add_test(tc_find, find_no_result);
    tcase_add_test(tc_find, find_null_head);
    tcase_add_test(tc_find, find_single_el);

    TCase *tc_pop_front = tcase_create("pop_front");
    tcase_add_test(tc_pop_front, pop_front_null_head);
    tcase_add_test(tc_pop_front, pop_front_single_el);
    tcase_add_test(tc_pop_front, pop_front_usual);

    TCase *tc_append = tcase_create("append");
    tcase_add_test(tc_append, append_first_list_null);
    tcase_add_test(tc_append, append_second_head_null);
    tcase_add_test(tc_append, append_two_heads_null);
    tcase_add_test(tc_append, append_two_lists);

    suite_add_tcase(s, tc_node_create);
    suite_add_tcase(s, tc_list_free);
    suite_add_tcase(s, tc_node_get_data);
    suite_add_tcase(s, tc_node_get_next);
    suite_add_tcase(s, tc_list_len);
    suite_add_tcase(s, tc_find);
    suite_add_tcase(s, tc_pop_front);
    suite_add_tcase(s, tc_append);

    return s;
}
