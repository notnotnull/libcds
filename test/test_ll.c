
#include <stdlib.h>
#include <check.h>
#include "../src/ll.h"
#include "test_utils.h"

/* test linked list creation */
START_TEST(test_ll_create)
	{
		linked_list_t *ll = NULL;
		ll = ll_create();
		ck_assert_ptr_ne(ll, NULL);
		free(ll);
	}
END_TEST

/* test linked list destruction */
START_TEST(test_ll_destroy)
	{
		linked_list_t *ll = NULL;
		ll = ll_create();
		ck_assert_ptr_ne(ll, NULL);
		
		ll_destroy(&ll, no_op);
		ck_assert_ptr_eq(ll, NULL);
	}
END_TEST

/* test linked list insertion */
START_TEST(test_ll_insert_front)
	{
		int rc;
		linked_list_t *ll = NULL;
		ll = ll_create();
		ck_assert_ptr_ne(ll, NULL);
		
		rc = ll_insert_front(ll, (void *)"Test Data Front");
		ck_assert_int_eq(rc, 0);
		ck_assert_int_eq(ll->nodes, 1);
		ck_assert_ptr_ne(ll->head, NULL);
		ck_assert_ptr_eq(ll->head->data, (void *)"Test Data Front");

		ll_destroy(&ll, no_op);
	}
END_TEST

/* test linked list insertion */
START_TEST(test_ll_insert_rear)
	{
		int rc;
		linked_list_t *ll = NULL;
		ll = ll_create();
		ck_assert_ptr_ne(ll, NULL);

		rc = ll_insert_front(ll, (void *)"Test Data Front");
		ck_assert_int_eq(rc, 0);
		ck_assert_int_eq(ll->nodes, 1);
		ck_assert_ptr_ne(ll->head, NULL);
		ck_assert_ptr_eq(ll->head->data, (void *)"Test Data Front");
		
		rc = ll_insert_rear(ll, (void *)"Test Data Rear");
		ck_assert_int_eq(rc, 0);
		ck_assert_int_eq(ll->nodes, 2);
		ck_assert_ptr_ne(ll->head, NULL);
		ck_assert_ptr_eq(ll->head->next->data, (void *)"Test Data Rear");

		ll_destroy(&ll, no_op);
	}
END_TEST

/* test linked list insertion at position */
START_TEST(test_ll_insert_at_pos)
	{
		linked_list_t *ll = NULL;
		ll = ll_create();
		ck_assert_ptr_ne(ll, NULL);

		ll_insert_at_pos(ll, 0, (void *)1);
		ll_insert_at_pos(ll, 0, (void *)2);
		ll_insert_at_pos(ll, 0, (void *)3);
		ll_insert_at_pos(ll, 1, (void *)4);
		ck_assert_ptr_eq(ll->head->next->data, (void *)4);
		// ll_display_ints(ll);

		ll_destroy(&ll, no_op);
	}
END_TEST

/* test linked list searching */
START_TEST(test_ll_search)
	{
		linked_list_t *ll = NULL;
		ll = ll_create();
		ck_assert_ptr_ne(ll, NULL);

		ll_insert_front(ll, (void *)1);
		ll_insert_rear(ll, (void *)2);
		ll_insert_rear(ll, (void *)3);

		ll_node_t *node = ll_search(ll, (void *)3);
		ck_assert_ptr_eq(node->data, (void *)3);

		ll_destroy(&ll, no_op);
	}
END_TEST

/* test linked list insertion sorting - Int Descending */
START_TEST(test_ll_insertion_sort)
	{
		linked_list_t *ll = NULL;
		ll = ll_create();
		ck_assert_ptr_ne(ll, NULL);

		ll_insertion_sort(ll, (void *)2, compare_int_desc);
		ll_insertion_sort(ll, (void *)3, compare_int_desc);
		ll_insertion_sort(ll, (void *)1, compare_int_desc);
		
		// ll_display_ints(ll);
		ck_assert_ptr_eq(ll->head->data, (void *)1);
		ll_destroy(&ll, no_op);
	}
END_TEST

/* test linked list node deletion */
START_TEST(test_ll_delete_node)
	{
		int rc;
		linked_list_t *ll = NULL;
		ll_node_t *search = NULL;
		ll = ll_create();
		ll_insert_front(ll, (void *)1);
		rc = ll_delete_node(ll, (void *)1);
		ck_assert_int_eq(rc, 0);
		search = ll_search(ll, (void *)1);
		ck_assert_ptr_eq(search, NULL);
		// ll_display_ints(ll);
		ll_destroy(&ll, no_op);
		
	}
END_TEST

Suite *ll_st(void)
{
	Suite *s = suite_create("Linked List");

	TCase *tc = tcase_create("LL Core");

	tcase_add_test(tc, test_ll_create);
	tcase_add_test(tc, test_ll_destroy);
	tcase_add_test(tc, test_ll_insert_rear);
	tcase_add_test(tc, test_ll_insert_at_pos);
	tcase_add_test(tc, test_ll_search);
	tcase_add_test(tc, test_ll_insertion_sort);
	tcase_add_test(tc, test_ll_delete_node);

	suite_add_tcase(s, tc);
	return s;
}
