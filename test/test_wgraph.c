#include <check.h>
#include "../src/wgraph.h"
#include "test_utils.h"

/* test weighted graph creation */
START_TEST(test_create_wgraph)
	{
		wgraph_t *g = create_wgraph(10);
		ck_assert_ptr_ne(g, NULL);
		ck_assert_int_eq(g->vertices, 10);
		destroy_wgraph(&g);
		ck_assert_ptr_eq(g, NULL);
	}
END_TEST

/* test weighted graph edge insertion */
START_TEST(test_insert_wgraph_edge)
	{
		int rc;
		wgraph_t *g = create_wgraph(10);
		ck_assert_ptr_ne(g, NULL);
		ck_assert_int_eq(g->vertices, 10);
		rc = insert_wgraph_edge(g, 0, 1, 0);
		ck_assert_int_eq(rc, 0);

		/* attempt to add a node that we should not be able to add */
		rc = insert_wgraph_edge(g, 11, 1, 0);
		ck_assert_int_eq(rc, -1);
		destroy_wgraph(&g);
	}
END_TEST

/* test weighted graph edge search */
START_TEST(test_search_wgraph_edge)
	{
		int rc;
		wgraph_t *g = create_wgraph(10);
		ck_assert_ptr_ne(g, NULL);
		ck_assert_int_eq(g->vertices, 10);
		rc = insert_wgraph_edge(g, 0, 1, 0);
		ck_assert_int_eq(rc, 0);

		rc = find_wgraph_edge(g, 0, 1);
		ck_assert_int_eq(rc, 1);
		destroy_wgraph(&g);
	}
END_TEST

/* test weighted graph edge removal */
START_TEST(test_remove_wgraph_edge)
	{
		int rc;
		wgraph_t *g = create_wgraph(10);
		ck_assert_ptr_ne(g, NULL);
		ck_assert_int_eq(g->vertices, 10);
		insert_wgraph_edge(g, 0, 1, 0);
		insert_wgraph_edge(g, 0, 2, 0);
		insert_wgraph_edge(g, 0, 3, 0);
		insert_wgraph_edge(g, 0, 4, 0);
		insert_wgraph_edge(g, 0, 5, 0);
		insert_wgraph_edge(g, 3, 2, 0);
		insert_wgraph_edge(g, 3, 4, 0);
		// display_wgraph(g);
		rc = remove_wgraph_edge(g, 0, 3);
		ck_assert_int_eq(rc, 0);
		// display_wgraph(g);
		rc = find_wgraph_edge(g, 0, 3);
		ck_assert_int_eq(rc, 0);
		destroy_wgraph(&g);
	}
END_TEST

/* test weighted graph node search */
START_TEST(test_search_wgraph_node)
	{
		int rc;
		wgraph_t *g = create_wgraph(10);
		adj_node_t *search_node = NULL;
		ck_assert_ptr_ne(g, NULL);
		ck_assert_int_eq(g->vertices, 10);
		rc = insert_wgraph_edge(g, 0, 1, 0);
		ck_assert_int_eq(rc, 0);

		search_node = find_wgraph_node(g, 0);
		ck_assert_int_eq(search_node->dst, 1);
		destroy_wgraph(&g);
	}
END_TEST

/* test weighted graph node removal */
START_TEST(test_remove_wgraph_node)
	{
		int rc;
		wgraph_t *g = create_wgraph(10);
		ck_assert_ptr_ne(g, NULL);
		ck_assert_int_eq(g->vertices, 10);
		insert_wgraph_edge(g, 0, 1, 0);
		insert_wgraph_edge(g, 1, 4, 0);
		insert_wgraph_edge(g, 6, 1, 0);
		insert_wgraph_edge(g, 9, 0, 0);
		insert_wgraph_edge(g, 7, 2, 0);
		// display_wgraph(g);
		rc = remove_wgraph_node(g, 1);
		ck_assert_int_eq(rc, 0);
		// display_wgraph(g);
		destroy_wgraph(&g);
	}
END_TEST

/* test weighted graph path weight calculation */
START_TEST(test_calc_wgraph_path_weight)
	{
		wgraph_t *g = create_wgraph(10);
		uint64_t path[5] = {1, 3, 5, 7};
		size_t weight = 0;
		ck_assert_ptr_ne(g, NULL);
		ck_assert_int_eq(g->vertices, 10);
		insert_wgraph_edge(g, 0, 1, 5);
		insert_wgraph_edge(g, 1, 3, 6);
		insert_wgraph_edge(g, 3, 5, 2);
		insert_wgraph_edge(g, 5, 7, 3);
		weight = calc_wgraph_weight(g, path, 5);
		ck_assert_int_eq(weight, 11);
		// display_wgraph(g);
		destroy_wgraph(&g);
	}
END_TEST


static TFun wwgraph_tests[] = {
	test_create_wgraph,
	test_insert_wgraph_edge,
	test_search_wgraph_edge,
	test_remove_wgraph_edge,
	test_search_wgraph_node,
	test_remove_wgraph_node,
	test_calc_wgraph_path_weight,
	NULL
};

Suite *wgraph_st(void)
{
	Suite *s = suite_create("DsaWGRAPH");

	TCase *tc = tcase_create("WGRAPH Core");
	TFun *curr = wwgraph_tests;
	while (*curr) {
		tcase_add_test(tc, *curr++);
	}
	suite_add_tcase(s, tc);
	return s;
}


