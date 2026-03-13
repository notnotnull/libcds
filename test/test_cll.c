#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "cll.h"
#include "test_utils.h"

const char *alphabet = "ABCDEFGHIJKLMMOPQRSTUVWXYZ";
const char *hello = "Hello World";
const char *position = "Position Insert";
const char *aliens = "Aliens";
const char *five = "5 times";

/* test circular linked list creation */
START_TEST(test_cll_create)
	{
		cll_t *cll = cll_create();
		ck_assert_ptr_ne(cll, NULL);
		cll_destroy(&cll, no_op);
		ck_assert_ptr_eq(cll, NULL);
	}
END_TEST

/* test circular linked list front insertion */
START_TEST(test_cll_insert_front)
	{
		cll_t *cll = cll_create();
		ck_assert_ptr_ne(cll, NULL);

		for (int i = 0; i < 6; i++) {
			cll_insert_front(cll, (void *)five);
		}

		/* Front Inserts */
		cll_insert_front(cll, (void *)alphabet);
		ck_assert_str_eq(cll->head->data, alphabet);
		ck_assert_str_eq(cll->tail->data, five);

		cll_insert_front(cll, (void *)hello);
		ck_assert_str_eq(cll->head->data, hello);
		ck_assert_str_eq(cll->tail->data, five);

		cll_insert_front(cll, (void *)aliens);
		ck_assert_str_eq(cll->head->data, aliens);
		ck_assert_str_eq(cll->tail->data, five);

		cll_insert_at_pos(cll, 1, (void *)position);
		ck_assert_str_eq(cll->head->next->data, position);

		cll_destroy(&cll, no_op);
	}
END_TEST

/* test circular linked list rear insertion */
START_TEST(test_cll_insert_rear)
	{
		cll_t *cll = cll_create();
		ck_assert_ptr_ne(cll, NULL);

		for (int i = 0; i < 6; i++) {
			cll_insert_front(cll, (void *)five);
		}

		/* Rear Inserts */
		cll_insert_rear(cll, (void *)alphabet);
		ck_assert_str_eq(cll->head->data, five);
		ck_assert_str_eq(cll->tail->data, alphabet);

		cll_insert_rear(cll, (void *)hello);
		ck_assert_str_eq(cll->head->data, five);
		ck_assert_str_eq(cll->tail->data, hello);

		cll_insert_rear(cll, (void *)aliens);
		ck_assert_str_eq(cll->head->data, five);
		ck_assert_str_eq(cll->tail->data, aliens);

		cll_insert_at_pos(cll, 2, (void *)position);
		ck_assert_str_eq(cll->head->next->next->data, position);

		cll_destroy(&cll, no_op);
	}
END_TEST

/* test circular linked list search for data */
START_TEST(test_cll_search)
	{
		cll_t *cll = cll_create();
		cll_node_t *search = NULL;
		ck_assert_ptr_ne(cll, NULL);

		/* Insert some stuff */
		cll_insert_front(cll, (void *)alphabet);
		cll_insert_front(cll, (void *)hello);
		cll_insert_front(cll, (void *)"Strings are character arrays");
		cll_insert_front(cll, (void *)aliens);
		//cll_display_strings(cll);

		/* Search for stuff */
		search = cll_search(cll, (void *)aliens, compare_alphanumeric);
		ck_assert_ptr_ne(search, NULL);
		cll_destroy(&cll, no_op);
	}
END_TEST

/* test circular linked list integer sorting */
START_TEST(test_sort_cll_int)
	{
		cll_t *cll = cll_create();
		ck_assert_ptr_ne(cll, NULL);

		/* Alphnumeric Inserts */
		cll_sorted_insert(cll, &cll->head, (void *)88, compare_int_desc);
		cll_sorted_insert(cll, &cll->head, (void *)25, compare_int_desc);
		cll_sorted_insert(cll, &cll->head, (void *)18, compare_int_desc);
		cll_sorted_insert(cll, &cll->head, (void *)7, compare_int_desc);
		cll_sorted_insert(cll, &cll->head, (void *)56, compare_int_desc);
		// cll_display_ints(cll);
		ck_assert_ptr_eq(cll->head->data, (void *)7);

		cll_destroy(&cll, no_op);
	}
END_TEST

/* test circular linked list alphanumeric sorting */
START_TEST(test_sort_cll)
	{
		cll_t *cll = cll_create();
		ck_assert_ptr_ne(cll, NULL);

		/* Alphnumeric Inserts */	
		cll_sorted_insert(cll, &cll->head, (void *)aliens, compare_alphanumeric);
		cll_sorted_insert(cll, &cll->head, (void *)five, compare_alphanumeric);
		cll_sorted_insert(cll, &cll->head, (void *)alphabet, compare_alphanumeric);
		cll_sorted_insert(cll, &cll->head, (void *)hello, compare_alphanumeric);
		cll_sorted_insert(cll, &cll->head, (void *)alphabet, compare_alphanumeric);
		// cll_display_strings(cll);
		ck_assert_str_eq(cll->head->data, five);

		cll_destroy(&cll, no_op);
	}
END_TEST

/* test circular linked list emptying */
START_TEST(test_cll_empty)
	{
		cll_t *cll = cll_create();
		ck_assert_ptr_ne(cll, NULL);

		for (int i = 0; i < 6; i++) {
			cll_insert_front(cll, (void *)five);
		}

		/* Rear Inserts */
		cll_insert_rear(cll, (void *)1);
		cll_insert_rear(cll, (void *)2);
		cll_insert_rear(cll, (void *)3);
		cll_insert_rear(cll, (void *)4);

		cll_empty(cll, no_op);
		ck_assert_ptr_eq(cll->head, NULL);
		cll_destroy(&cll, no_op);
	}
END_TEST

/* test circular linked list node deletion */
START_TEST(test_cll_delete_node)
	{
		int rc;
		cll_node_t *search = NULL;
		cll_t *cll = cll_create();
		ck_assert_ptr_ne(cll, NULL);

		for (int i = 0; i < 6; i++) {
			cll_insert_front(cll, (void *)five);
		}

		/* Rear Inserts */
		rc = cll_insert_rear(cll, (void *)1);
		rc = cll_insert_rear(cll, (void *)2);
		rc = cll_insert_rear(cll, (void *)3);
		rc = cll_insert_rear(cll, (void *)4);

		rc = cll_delete_node(cll, (void *)2, no_op);
		ck_assert_int_eq(rc, 0);
		search = cll_search(cll, (void *)2, compare_int_desc);
		ck_assert_ptr_eq(search, NULL);
		cll_destroy(&cll, no_op);
	}
END_TEST


Suite *cll_st(void)
{
	Suite *s = suite_create("Circularly Linked List");

	TCase *tc = tcase_create("CLL Core");

	tcase_add_test(tc, test_cll_create);
    tcase_add_test(tc, test_cll_insert_front);
    tcase_add_test(tc, test_cll_insert_rear);
    tcase_add_test(tc, test_cll_search);
    tcase_add_test(tc, test_sort_cll_int);
    tcase_add_test(tc, test_sort_cll);
    tcase_add_test(tc, test_cll_empty);
    tcase_add_test(tc, test_cll_delete_node);

	suite_add_tcase(s, tc);
	return s;
}
