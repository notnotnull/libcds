#include <stdlib.h>
#include <check.h>
#include "stack.h"

/* test stack creation */
START_TEST(test_stack_create)
	{
		stack_t *s = NULL;
		s = stack_create(64);
		ck_assert_ptr_ne(s, NULL);
		ck_assert_int_eq(s->max_size, 64);
		free(s);
	}
END_TEST

/* test stack destruction */
START_TEST(test_stack_destroy)
	{
		stack_t *s = NULL;
		s = stack_create(64);
		ck_assert_ptr_ne(s, NULL);
		stack_destroy(&s);
		ck_assert_ptr_eq(s, NULL);
	}
END_TEST

/* test stack stack_push */
START_TEST(test_stack_push)
	{
		stack_t *s = NULL;
		int rc;
		s = stack_create(3);
		ck_assert_ptr_ne(s, NULL);
		stack_push(s, (void *)1);
		stack_push(s, (void *)2);
		stack_push(s, (void *)3);
		rc = stack_push(s, (void *)4); // Should not be able to stack_push 4
		ck_assert_int_eq(rc, -2);
		ck_assert_int_eq(s->cells, 3);
		stack_destroy(&s);
	}
END_TEST

/* test stack stack_pop */
START_TEST(test_stack_pop)
	{
		stack_t *s = NULL;
		stack_cell_t *stack_pop_cell = NULL;
		s = stack_create(3);
		ck_assert_ptr_ne(s, NULL);
		stack_push(s, (void *)1);
		stack_push(s, (void *)2);
		stack_push(s, (void *)3);
		stack_pop_cell = stack_pop(s);
		ck_assert_ptr_eq(stack_pop_cell->data, (void *)3);
		ck_assert_int_eq(s->cells, 2);
		stack_destroy(&s);
		free(stack_pop_cell);
	}
END_TEST

/* test stack index searching */
START_TEST(test_stack_find_at_index)
	{
		stack_t *s = NULL;
		stack_cell_t *stack_pop_cell = NULL;
		s = stack_create(3);
		ck_assert_ptr_ne(s, NULL);
		stack_push(s, (void *)1);
		stack_push(s, (void *)2);
		stack_push(s, (void *)3);
		ck_assert_int_eq(s->cells, 3);
		stack_pop_cell = stack_find_at_index(s, 2);
		ck_assert_ptr_eq(stack_pop_cell->data, (void *)1);
		stack_destroy(&s);
	}
END_TEST

Suite *stack_st(void)
{
	Suite *s = suite_create("Stack");

	TCase *tc = tcase_create("STACK Core");
	tcase_add_test(tc, test_stack_create);
	tcase_add_test(tc, test_stack_destroy);
	tcase_add_test(tc, test_stack_push);
	tcase_add_test(tc, test_stack_pop);
	tcase_add_test(tc, test_stack_find_at_index);
	suite_add_tcase(s, tc);
	return s;
}
