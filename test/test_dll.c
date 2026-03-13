#include <stdlib.h>
#include <check.h>
#include "dll.h"
#include "test_utils.h"

const char *test = "Test Sentence";
const char *goodbye = "Goodbye World";
const char *important = "C Unit testing is important";
const char *lizard = "Lizard People";
const char *four = "4 times";

/* test doubly linked list creation */
START_TEST(test_dll_create)
	{
		dll_t *dll = NULL;
		dll = dll_create();
		ck_assert_ptr_ne(dll, NULL);
		free(dll);
	}
END_TEST

/* test doubly linked list destruction */
START_TEST(test_dll_destroy)
	{
		dll_t *dll = NULL;
		dll = dll_create();
		ck_assert_ptr_ne(dll, NULL);
		
		dll_destroy(&dll, no_op);
		ck_assert_ptr_eq(dll, NULL);
	}
END_TEST

/* test doubly linked list front insertion */
START_TEST(test_dll_insert_front)
	{
		int rc;
		dll_t *dll = NULL;
		dll = dll_create();
		ck_assert_ptr_ne(dll, NULL);
		
		rc = dll_insert_front(dll, (void *)"Test Data Front");
		ck_assert_int_eq(rc, 0);
		ck_assert_int_eq(dll->nodes, 1);
		ck_assert_ptr_ne(dll->head, NULL);
		ck_assert_ptr_ne(dll->tail, NULL);
		ck_assert_ptr_eq(dll->head->data, (void *)"Test Data Front");

		dll_destroy(&dll, no_op);
	}
END_TEST

/* test doubly linked list rear insertion */
START_TEST(test_dll_insert_rear)
	{
		dll_t *dll = NULL;
		dll = dll_create();
		ck_assert_ptr_ne(dll, NULL);
		
		dll_insert_front(dll, (void *)"Test Data Front");
		dll_insert_front(dll, (void *)"Test Data Front New");
		dll_insert_rear(dll, (void *)"Test Data Rear");
		ck_assert_int_eq(dll->nodes, 3);
		ck_assert_ptr_ne(dll->head, NULL);
		ck_assert_ptr_ne(dll->tail, NULL);
		ck_assert_ptr_eq(dll->tail->data, (void *)"Test Data Rear");
		// dll_display_strings(dll);
		dll_destroy(&dll, no_op);
	}
END_TEST

/* test doubly linked list position insertion */
START_TEST(test_dll_insert_at_pos)
	{
		dll_t *dll = NULL;
		dll = dll_create();
		ck_assert_ptr_ne(dll, NULL);
		
		dll_insert_front(dll, (void *)"Test Data Front");
		dll_insert_front(dll, (void *)"Test Data Front 2");
		dll_insert_front(dll, (void *)"Test Data Front 3");
		dll_insert_rear(dll, (void *)"Test Data Rear");
		dll_insert_at_pos(dll, 0, (void *)"Test Data Pos");
		dll_insert_at_pos(dll, 3, (void *)"Test Data Pos 2");
		ck_assert_int_eq(dll->nodes, 6);
		ck_assert_ptr_eq(dll->tail->data, (void *)"Test Data Rear");
		ck_assert_ptr_eq(dll->head->next->next->next->data, (void *)"Test Data Pos 2");

		dll_destroy(&dll, no_op);
	}
END_TEST

/* test doubly linked list node front deletion */
START_TEST(test_dll_delete_front)
	{
		dll_t *dll = NULL;
		dll = dll_create();
		ck_assert_ptr_ne(dll, NULL);
		
		dll_insert_front(dll, (void *)1);
		dll_insert_front(dll, (void *)2);
		dll_insert_front(dll, (void *)3);
		dll_delete_front(dll);
		ck_assert_int_eq(dll->nodes, 2);
		ck_assert_ptr_eq(dll->head->data, (void *)2);

		dll_destroy(&dll, no_op);
	}
END_TEST

/* test doubly linked list node rear deletion */
START_TEST(test_dll_delete_rear)
	{
		dll_t *dll = NULL;
		dll = dll_create();
		ck_assert_ptr_ne(dll, NULL);
		
		dll_insert_front(dll, (void *)1);
		dll_insert_front(dll, (void *)2);
		dll_insert_front(dll, (void *)3);
		dll_delete_rear(dll);
		ck_assert_int_eq(dll->nodes, 2);
		ck_assert_ptr_eq(dll->tail->data, (void *)2);

		dll_destroy(&dll, no_op);
	}
END_TEST

/* test doubly linked list node position deletion */
START_TEST(test_dll_delete_at_pos)
	{
		dll_t *dll = NULL;
		dll = dll_create();
		ck_assert_ptr_ne(dll, NULL);
		
		dll_insert_front(dll, (void *)1);
		dll_insert_front(dll, (void *)2);
		dll_insert_front(dll, (void *)3);
		dll_delete_at_pos(dll, 1);
		ck_assert_int_eq(dll->nodes, 2);
		ck_assert_ptr_eq(dll->tail->data, (void *)1);

		dll_destroy(&dll, no_op);
	}
END_TEST

/* test doubly linked list search */
START_TEST(test_dll_search)
	{
		dll_t *dll = NULL;
		dll_node_t *node = NULL;
		dll = dll_create();
		ck_assert_ptr_ne(dll, NULL);
		
		dll_insert_front(dll, (void *)1);
		dll_insert_front(dll, (void *)2);
		dll_insert_front(dll, (void *)3);
		node = dll_search(dll, (void *)1);
		ck_assert_ptr_eq(node->data, (void *)1);

		dll_destroy(&dll, no_op);
	}
END_TEST

/* test doubly linked list insertion sorting */
START_TEST(test_sort_dll)
	{
		dll_t *dll = NULL;
		dll = dll_create();
		ck_assert_ptr_ne(dll, NULL);
		dll_insertion_sort(dll, &dll->head, (void *)test, compare_alphanumeric);
		dll_insertion_sort(dll, &dll->head, (void *)goodbye, compare_alphanumeric);
		dll_insertion_sort(dll, &dll->head, (void *)important, compare_alphanumeric);
		dll_insertion_sort(dll, &dll->head, (void *)four, compare_alphanumeric);
		ck_assert_str_eq(dll->head->data, four);
		ck_assert_str_eq(dll->tail->data, test);
		// dll_display_strings(dll);
		dll_destroy(&dll, no_op);
	}
END_TEST

Suite *dll_st(void)
{
	Suite *s = suite_create("Doubly Linked List");

	TCase *tc = tcase_create("DLL Core");

	tcase_add_test(tc, test_dll_create);
	tcase_add_test(tc, test_dll_destroy);
	tcase_add_test(tc, test_dll_insert_front);
	tcase_add_test(tc, test_dll_insert_rear);
	tcase_add_test(tc, test_dll_insert_at_pos);
	tcase_add_test(tc, test_dll_delete_front);
	tcase_add_test(tc, test_dll_delete_rear);
	tcase_add_test(tc, test_dll_delete_at_pos);
	tcase_add_test(tc, test_dll_search);
	tcase_add_test(tc, test_sort_dll);

	suite_add_tcase(s, tc);
	return s;
}
