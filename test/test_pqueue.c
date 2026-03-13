#include <check.h>
#include "pqueue.h"

/* test pqueue creation */
START_TEST(test_create_pqueue)
	{
		pqueue_t *pq = NULL;
		pq = create_pqueue(16);
		ck_assert_ptr_ne(pq, NULL);
		destroy_pqueue(&pq);
		ck_assert_ptr_eq(pq, NULL);
	}
END_TEST

/* test enqpueue */
START_TEST(test_enpqueue)
	{
		pqueue_t *pq = NULL;
		int rc;
		pq = create_pqueue(16);
		ck_assert_ptr_ne(pq, NULL);
		enpqueue(pq, (void *)55, 3);
		enpqueue(pq, (void *)56, 2);
		rc = enpqueue(pq, (void *)57, 1);
		ck_assert_int_eq(rc, 0);
		ck_assert_ptr_eq(pq->array[0].data, (void *)57);
		// display_pqueue_ints(pq);
		destroy_pqueue(&pq);
	}
END_TEST

/* test deqpueue */
START_TEST(test_depqueue)
	{
		pqueue_t *pq = NULL;
		void *popped = NULL;
		pq = create_pqueue(16);
		ck_assert_ptr_ne(pq, NULL);
		enpqueue(pq, (void *)55, 3);
		enpqueue(pq, (void *)56, 2);
		enpqueue(pq, (void *)57, 1);
		enpqueue(pq, (void *)60, 6);
		enpqueue(pq, (void *)62, 7);
		enpqueue(pq, (void *)61, 1);
		ck_assert_ptr_eq(pq->array[0].data, (void *)57);
		popped = depqueue(pq);
		ck_assert_ptr_eq(popped, (void *)57);
		popped = depqueue(pq);
		ck_assert_ptr_eq(popped, (void *)61);
		popped = depqueue(pq);
		ck_assert_ptr_eq(popped, (void *)56);
		popped = depqueue(pq);
		ck_assert_ptr_eq(popped, (void *)55);
		destroy_pqueue(&pq);
	}
END_TEST

/* test pqueue searching */
START_TEST(test_search_pqueue)
	{
		pqueue_t *pq = NULL;
		pqueue_element_t *searched = NULL;
		pq = create_pqueue(16);
		ck_assert_ptr_ne(pq, NULL);
		enpqueue(pq, (void *)55, 3);
		enpqueue(pq, (void *)56, 2);
		enpqueue(pq, (void *)57, 1);
		enpqueue(pq, (void *)60, 6);
		enpqueue(pq, (void *)62, 7);
		enpqueue(pq, (void *)61, 1);
		searched = search_pqueue(pq, (void *)60);
		ck_assert_ptr_eq(searched->data, (void *)60);
		destroy_pqueue(&pq);
	}
END_TEST

/* test pqueue index searching */
START_TEST(test_index_pqueue)
	{
		pqueue_t *pq = NULL;
		pqueue_element_t *indexed = NULL;
		pq = create_pqueue(16);
		ck_assert_ptr_ne(pq, NULL);
		enpqueue(pq, (void *)55, 3);
		enpqueue(pq, (void *)56, 2);
		enpqueue(pq, (void *)57, 1);
		enpqueue(pq, (void *)60, 6);
		enpqueue(pq, (void *)62, 7);
		enpqueue(pq, (void *)61, 1);
		indexed = find_pqueue_index(pq, 3);
		ck_assert_ptr_eq(indexed->data, (void *)60);
		destroy_pqueue(&pq);
	}
END_TEST

static TFun pqueue_tests[] = {
	test_create_pqueue,
	test_enpqueue,
	test_depqueue,
	test_search_pqueue,
	test_index_pqueue,
	NULL
};

Suite *pqueue_st(void)
{
	Suite *s = suite_create("DsaPQUEUE");

	TCase *tc = tcase_create("PQUEUE Core");
	TFun *curr = pqueue_tests;
	while (*curr) {
		tcase_add_test(tc, *curr++);
	}
	suite_add_tcase(s, tc);
	return s;
}
