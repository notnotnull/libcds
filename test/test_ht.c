#include <check.h>
#include "ht.h"
#include "test_utils.h"

/* test hash table creation */
START_TEST(test_create_ht)
	{
		hash_table_t *ht = NULL;
		ht = create_ht((size_t)100);
		ck_assert_ptr_ne(ht, NULL);
		ck_assert_int_eq(ht->capacity, 100);
		destroy_ht(&ht, no_op);
		ck_assert_ptr_eq(ht, NULL);
	}
END_TEST

/* test hash table insertion */
START_TEST(test_insert_ht)
	{
		hash_table_t *ht = NULL;
		int rc;
		ht = create_ht((size_t)100);
		ck_assert_ptr_ne(ht, NULL);
		ck_assert_int_eq(ht->capacity, 100);
		insert_ht(ht, (void *)"Hello World", compare_alphanumeric);
		ck_assert_int_eq(ht->items, 1);
		insert_ht(ht, (void *)"Good-bye World", compare_alphanumeric);
		insert_ht(ht, (void *)"Where am I?", compare_alphanumeric);
		insert_ht(ht, (void *)"Ceiling Fan",compare_alphanumeric);
		rc = insert_ht(ht, (void *)"Hello World", compare_alphanumeric);
		ck_assert_int_eq(rc, -1);
		destroy_ht(&ht, no_op);
	}
END_TEST

/* test hash table search */
START_TEST(test_search_ht)
	{
		hash_table_t *ht = NULL;
		ht_item_t *search = NULL;
		ht = create_ht(100);
		ck_assert_ptr_ne(ht, NULL);
		ck_assert_int_eq(ht->capacity, 100);
		insert_ht(ht, (void *)"Hello World", compare_alphanumeric);
		ck_assert_int_eq(ht->items, 1);
		insert_ht(ht, (void *)"Good-bye World", compare_alphanumeric);
		insert_ht(ht, (void *)"Where am I?", compare_alphanumeric);
		search = search_ht(ht, (void *)"Where am I?", compare_alphanumeric);
		ck_assert_ptr_ne(search, NULL);
		ck_assert_str_eq(search->data, (void *)"Where am I?");
		destroy_ht(&ht, no_op);
	}
END_TEST

/* test hash table indexing */
START_TEST(test_index_ht)
	{
		hash_table_t *ht = NULL;
		ht_item_t *index = NULL;

		ht = create_ht((size_t)100);
		ck_assert_ptr_ne(ht, NULL);
		ck_assert_int_eq(ht->capacity, 100);
		insert_ht(ht, (void *)"Hello World", compare_alphanumeric);
		index = index_ht(ht, 11);
		ck_assert_str_eq(index->data, "Hello World");
		destroy_ht(&ht, no_op);
	}
END_TEST

/* test hash table item deletion */
START_TEST(test_delete_ht_item)
	{
		hash_table_t *ht = NULL;
		ht_item_t *search = NULL;

		ht = create_ht((size_t)100);
		ck_assert_ptr_ne(ht, NULL);
		ck_assert_int_eq(ht->capacity, 100);
		insert_ht(ht, (void *)"Hello World", compare_alphanumeric);
		delete_ht_item(ht, (void *)"Hello World", compare_alphanumeric);
		search = search_ht(ht, (void *)"Hello World", compare_alphanumeric);
		ck_assert_ptr_eq(search, NULL);
		ck_assert_int_eq(ht->items, 0);
		destroy_ht(&ht, no_op);
	}
END_TEST

static TFun ht_tests[] = {
	test_create_ht,
	test_insert_ht,
	// test_search_ht,
	// test_index_ht,
	// test_delete_ht_item,
	NULL
};

Suite *ht_st(void)
{
	Suite *s = suite_create("DsaHT");

	TCase *tc = tcase_create("HT Core");
	TFun *curr = ht_tests;
	while (*curr) {
		tcase_add_test(tc, *curr++);
	}
	suite_add_tcase(s, tc);
	return s;
}
