#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_utils.h"

void no_op(void *none)
{
	return;
}

/* https://www.gnu.org/software/libc/manual/html_node/Comparison-Functions.html */
int compare_int_desc(void *a, void *b)
{
	int int_a = *((int *)&a);
	int int_b = *((int *)&b);
	int c;

	c = int_a - int_b;
	// printf("c -> %d\n", c);
	return c;
}

int compare_alphanumeric(void *a, void *b)
{
	char *char_a = (char *)a;
	char *char_b = (char *)b;
	int c;

	/* Return negative number if a is less than b, positive number if greater, 
	and 0 if a is equal to b */

	// printf("A -> %s\n", char_a);
	// printf("B -> %s\n", char_b);

	c = strcmp(char_a, char_b);
	// printf("c -> %d\n", c);
	return c;

}