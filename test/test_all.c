#include <check.h>
#include "../src/ll.h"
#include "../src/dll.h"
#include "test_ll.c"
#include "test_dll.c"
#include "test_queue.c"
#include "test_stack.c"
#include "test_pqueue.c"
#include "test_bst.c"
#include "test_ht.c"
#include "test_cll.c"
#include "test_wgraph.c"

extern Suite *ll_st(void);
extern Suite *dll_st(void);
extern Suite *queue_st(void);
extern Suite *stack_st(void);
extern Suite *pqueue_st(void);
extern Suite *bst_st(void);
extern Suite *ht_st(void);
extern Suite *cll_st(void);
extern Suite *wgraph_st(void);

int main(void)
{
	SRunner *sr = srunner_create(NULL);
	srunner_set_fork_status(sr, CK_NOFORK); /* Disabled to discard Check's valgrind errors */

	srunner_add_suite(sr, ll_st());
	srunner_add_suite(sr, dll_st());
	srunner_add_suite(sr, queue_st());
	srunner_add_suite(sr, stack_st());
	srunner_add_suite(sr, pqueue_st());
	srunner_add_suite(sr, bst_st());
	srunner_add_suite(sr, ht_st());
	srunner_add_suite(sr, cll_st());
	srunner_add_suite(sr, wgraph_st());

	srunner_run_all(sr, CK_NORMAL);
	int failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return !!failed;
}
