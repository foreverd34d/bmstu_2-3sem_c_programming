#include <check.h>
#include <stddef.h>
#include <stdlib.h>
#include "../inc/numkey.h"
#include "../inc/check_main.h"

//
// get_neg_ind positives
//

START_TEST(get_neg_ind_usual)
{
    int arr[] = { 3, 2, 1, 0, -1, 10, -10, 0, 5 };
    size_t expect = 4;
    size_t got = get_neg_ind(arr, arr + sizeof(arr)/sizeof(*arr));
    ck_assert_uint_eq(expect, got);
}
END_TEST

START_TEST(get_neg_ind_neg_in_beg)
{
    int arr[] = { -1, 2, 3, 4, 0, -1, 2 };
    size_t expect = 0;
    size_t got = get_neg_ind(arr, arr + sizeof(arr)/sizeof(*arr));
    ck_assert_uint_eq(expect, got);
}
END_TEST

START_TEST(get_neg_ind_neg_in_end)
{
    int arr[] = { 3, 2, 1, 0, 1, -1 };
    size_t expect = 5;
    size_t got = get_neg_ind(arr, arr + sizeof(arr)/sizeof(*arr));
    ck_assert_uint_eq(expect, got);
}
END_TEST

START_TEST(get_neg_ind_no_neg)
{
    int arr[] = { 1, 2, 3, 4, 5, 6 };
    size_t expect = sizeof(arr)/sizeof(*arr);
    size_t got = get_neg_ind(arr, arr + sizeof(arr)/sizeof(*arr));
    ck_assert_uint_eq(expect, got);
}
END_TEST

START_TEST(get_neg_ind_all_neg)
{
    int arr[] = { -1, -2, -3, -4, -5 };
    size_t expect = 0;
    size_t got = get_neg_ind(arr, arr + sizeof(arr)/sizeof(*arr));
    ck_assert_uint_eq(expect, got);
}
END_TEST


//
// key negatives
//

START_TEST(key_neg_pb_src_eq_null)
{
    int buf[] = { 1, 2, 3 };

    int *arr_e = buf + sizeof(buf)/sizeof(*buf);
    int *got = NULL, *got_e = NULL;

    int err = key(NULL, arr_e, &got, &got_e);

    ck_assert_int_eq(err, ERR_KEY_ARGS);
}
END_TEST

START_TEST(key_neg_pe_src_eq_null)
{
    int buf[] = { 1, 2, 3 };

    int *arr = buf;
    int *got = NULL, *got_e = NULL;

    int err = key(arr, NULL, &got, &got_e);

    ck_assert_int_eq(err, ERR_KEY_ARGS);
}
END_TEST

START_TEST(key_neg_pb_dst_eq_null)
{
    int buf[] = { 1, 2, 3 };

    int *arr = buf, *arr_e = buf + sizeof(buf)/sizeof(*buf);
    int *got_e = NULL;

    int err = key(arr, arr_e, NULL, &got_e);

    ck_assert_int_eq(err, ERR_KEY_ARGS);
}
END_TEST

START_TEST(key_neg_pe_dst_eq_null)
{
    int buf[] = { 1, 2, 3 };

    int *arr = buf, *arr_e = buf + sizeof(buf)/sizeof(*buf);
    int *got = NULL;

    int err = key(arr, arr_e, &got, NULL);

    ck_assert_int_eq(err, ERR_KEY_ARGS);
}
END_TEST

START_TEST(key_neg_pb_src_eq_pe_src)
{
    int buf[] = { 1, 2, 3 };

    int *arr = buf;
    int *got = NULL, *got_e = NULL;

    int err = key(arr, arr, &got, &got_e);

    ck_assert_int_eq(err, ERR_KEY_ARGS);
}
END_TEST

START_TEST(key_neg_pb_src_gt_pe_src)
{
    int buf[] = { 1, 2, 3 };

    int *arr = buf, *arr_e = buf + sizeof(buf)/sizeof(*buf);
    int *got = NULL, *got_e = NULL;

    int err = key(arr_e, arr, &got, &got_e);

    ck_assert_int_eq(err, ERR_KEY_ARGS);
}
END_TEST

START_TEST(key_neg_pb_dst_eq_pb_src)
{
    int buf[] = { 1, 2, 3 };

    int *arr = buf, *arr_e = buf + sizeof(buf)/sizeof(*buf);
    int *got_e = NULL;

    int err = key(arr, arr_e, &arr, &got_e);

    ck_assert_int_eq(err, ERR_KEY_ARGS);
}
END_TEST

START_TEST(key_neg_pe_dst_eq_pe_src)
{
    int buf[] = { 1, 2, 3 };

    int *arr = buf, *arr_e = buf + sizeof(buf)/sizeof(*buf);
    int *got = NULL;

    int err = key(arr, arr_e, &got, &arr_e);

    ck_assert_int_eq(err, ERR_KEY_ARGS);
}
END_TEST

START_TEST(key_neg_negative_num_in_beg)
{
    int buf[] = { -1, 0, 1, -2, 2, 3 };

    int *arr = buf, *arr_e = buf + sizeof(buf)/sizeof(*buf);
    int *got = NULL, *got_e = NULL;

    int err = key(arr, arr_e, &got, &got_e);

    ck_assert_int_eq(err, ERR_KEY_NO_RESULT);
}
END_TEST

START_TEST(key_neg_all_negatives)
{
    int buf[] = { -1, -2, -3, -4, -5 };

    int *arr = buf, *arr_e = buf + sizeof(buf)/sizeof(*buf);
    int *got = NULL, *got_e = NULL;

    int err = key(arr, arr_e, &got, &got_e);

    ck_assert_int_eq(err, ERR_KEY_NO_RESULT);
}
END_TEST


//
// key positives
//

START_TEST(key_pos_usual)
{
    int buf[] = { 3, 2, 1, 0, -1, 10, -10, 0, 5 };
    int expect[] = { 3, 2, 1, 0 };

    int *arr = buf, *arr_e = buf + sizeof(buf)/sizeof(*buf);
    int *got = NULL, *got_e = NULL;

    int err = key(arr, arr_e, &got, &got_e);

    ck_assert_int_eq(err, RET_SUCCESS);
    ck_assert_uint_eq(sizeof(expect)/sizeof(*expect), got_e - got);
    ck_assert_mem_eq(expect, got, sizeof(expect));
    ck_assert_mem_eq(expect, got, (got_e - got) * sizeof(int));
    free(got);
}
END_TEST

START_TEST(key_pos_negative_num_last)
{
    int buf[] = { 3, 2, 1, 2, 3, 4, 0, -1 };
    int expect[] = { 3, 2, 1, 2, 3, 4, 0 };

    int *arr = buf, *arr_e = buf + sizeof(buf)/sizeof(*buf);
    int *got = NULL, *got_e = NULL;

    int err = key(arr, arr_e, &got, &got_e);

    ck_assert_int_eq(err, RET_SUCCESS);
    ck_assert_uint_eq(sizeof(expect)/sizeof(*expect), got_e - got);
    ck_assert_mem_eq(expect, got, sizeof(expect));
    ck_assert_mem_eq(expect, got, (got_e - got) * sizeof(int));
    free(got);
}
END_TEST

START_TEST(key_pos_no_negative_num)
{
    int buf[] = { 3, 2, 1, 2, 3, 4, 0 };
    int expect[] = { 3, 2, 1, 2, 3, 4, 0 };

    int *arr = buf, *arr_e = buf + sizeof(buf)/sizeof(*buf);
    int *got = NULL, *got_e = NULL;

    int err = key(arr, arr_e, &got, &got_e);

    ck_assert_int_eq(err, RET_SUCCESS);
    ck_assert_uint_eq(sizeof(expect)/sizeof(*expect), got_e - got);
    ck_assert_mem_eq(expect, got, sizeof(expect));
    ck_assert_mem_eq(expect, got, (got_e - got) * sizeof(int));
    free(got);
}
END_TEST

START_TEST(key_pos_single_el)
{
    int buf[] = { 1 };
    int expect[] = { 1 };

    int *arr = buf, *arr_e = buf + sizeof(buf)/sizeof(*buf);
    int *got = NULL, *got_e = NULL;

    int err = key(arr, arr_e, &got, &got_e);

    ck_assert_int_eq(err, RET_SUCCESS);
    ck_assert_uint_eq(sizeof(expect)/sizeof(*expect), got_e - got);
    ck_assert_mem_eq(expect, got, sizeof(expect));
    ck_assert_mem_eq(expect, got, (got_e - got) * sizeof(int));
    free(got);
}
END_TEST


Suite *numkey_suite(void)
{
    Suite *s = suite_create("numkey");

    TCase *tc_get_neg_ind_pos = tcase_create("get_neg_ind positives");
    tcase_add_test(tc_get_neg_ind_pos, get_neg_ind_usual);
    tcase_add_test(tc_get_neg_ind_pos, get_neg_ind_neg_in_beg);
    tcase_add_test(tc_get_neg_ind_pos, get_neg_ind_neg_in_end);
    tcase_add_test(tc_get_neg_ind_pos, get_neg_ind_no_neg);
    tcase_add_test(tc_get_neg_ind_pos, get_neg_ind_all_neg);

    TCase *tc_key_neg = tcase_create("key negatives");
    tcase_add_test(tc_key_neg, key_neg_pb_src_eq_null);
    tcase_add_test(tc_key_neg, key_neg_pe_src_eq_null);
    tcase_add_test(tc_key_neg, key_neg_pb_dst_eq_null);
    tcase_add_test(tc_key_neg, key_neg_pe_dst_eq_null);
    tcase_add_test(tc_key_neg, key_neg_pb_src_eq_pe_src);
    tcase_add_test(tc_key_neg, key_neg_pb_src_gt_pe_src);
    tcase_add_test(tc_key_neg, key_neg_pb_dst_eq_pb_src);
    tcase_add_test(tc_key_neg, key_neg_pe_dst_eq_pe_src);
    tcase_add_test(tc_key_neg, key_neg_negative_num_in_beg);
    tcase_add_test(tc_key_neg, key_neg_all_negatives);

    TCase *tc_key_pos = tcase_create("key positives");
    tcase_add_test(tc_key_pos, key_pos_usual);
    tcase_add_test(tc_key_pos, key_pos_negative_num_last);
    tcase_add_test(tc_key_pos, key_pos_no_negative_num);
    tcase_add_test(tc_key_pos, key_pos_single_el);

    suite_add_tcase(s, tc_get_neg_ind_pos);
    suite_add_tcase(s, tc_key_neg);
    suite_add_tcase(s, tc_key_pos);

    return s;
}
