#include <check.h>
#include <stdlib.h>
#include "bst.h"
#include "test_utils.h"

/* test bst creation */
START_TEST(test_create_bst)
	{
		bst_t *bst = NULL;
		bst = create_bst();
		ck_assert_ptr_ne(bst, NULL);
		destroy_bst(bst->root, no_op);
		ck_assert_ptr_eq(bst->root, NULL);
		free(bst);
		
	}
END_TEST

/* test bst insertion */
START_TEST(test_insert_bst)
	{
		bst_t *bst = NULL;
		bst = create_bst();
		ck_assert_ptr_ne(bst, NULL);
		bst->root = insert_bst(bst->root, 2, (void *)"Data 2");
		insert_bst(bst->root, 1, (void *)"Data 1");
		insert_bst(bst->root, 3, (void *)"Data 3");
		ck_assert_int_eq(bst->root->key, 2);
		destroy_bst(bst->root, no_op);
		free(bst);
	}
END_TEST

/* test bst searching */
START_TEST(test_search_bst)
	{
		bst_t *bst = NULL;
		bst_node_t *searched = NULL;
		bst = create_bst();
		ck_assert_ptr_ne(bst, NULL);
		bst->root = insert_bst(bst->root, 1, (void *)10);
		insert_bst(bst->root, 2, (void *)11);
		insert_bst(bst->root, 3,(void *) 12);
		searched = search_bst(bst->root, 1);
		ck_assert_ptr_ne(searched, NULL);
		ck_assert_ptr_eq(searched->data, (void *)10);
		searched = search_bst(bst->root, 3);
		ck_assert_ptr_ne(searched, NULL);
		ck_assert_ptr_eq(searched->data, (void *)12);
		destroy_bst(bst->root, no_op);
		free(bst);
	}
END_TEST

/* test bst deletion */
START_TEST(test_delete_bst_node)
	{
		bst_t *bst = NULL;
		bst_node_t *searched = NULL;
		bst = create_bst();
		ck_assert_ptr_ne(bst, NULL);
		bst->root = insert_bst(bst->root, 1, (void *)10);
		bst->root = insert_bst(bst->root, 2, (void *)11);
		bst->root = insert_bst(bst->root, 3, (void *)12);
		bst->root = delete_bst_node(bst->root, 1, no_op);
		searched = search_bst(bst->root, 1);
		ck_assert_ptr_eq(searched, NULL);
		ck_assert_ptr_ne(bst->root, NULL);
		destroy_bst(bst->root, no_op);
		free(bst);
	}
END_TEST

Suite *bst_st(void)
{
	Suite *s = suite_create("Binary Search Tree");

	TCase *tc = tcase_create("BST Core");

	tcase_add_test(tc, test_create_bst);
    tcase_add_test(tc, test_insert_bst);
    tcase_add_test(tc, test_search_bst);
    tcase_add_test(tc, test_delete_bst_node);

	suite_add_tcase(s, tc);
	return s;
}
