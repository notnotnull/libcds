#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cll.h"

static int cll_insert_empty(cll_t *cll, void *data);

cll_node_t *cll_create_node(void *data)
{
	cll_node_t *new = calloc(1, sizeof(cll_node_t));
	if (new == NULL) {
		goto ret;
	}
	new->data = data;
ret:
	return new;
}

cll_t *cll_create(void)
{
	cll_t *cll = calloc(1, sizeof(cll_t));	
	return cll;
}

void cll_destroy(cll_t **cll, void (*destroy)(void *))
{
	cll_node_t *current = NULL;
	cll_node_t *next = NULL;

	if (cll == NULL) {
		goto ret;
	}

	if ((*cll)->head == NULL) {
		goto ret;
	}

	current = (*cll)->head->next;

	while (current != (*cll)->head && current) {
		next = current->next;
		destroy(current->data);
		free(current);
		current = next;
	}

	destroy((*cll)->head->data);
	free((*cll)->head);

ret:
	free(*cll);
	*cll = NULL;
}

void cll_empty(cll_t *cll, void (*destroy)(void *))
{
	cll_node_t *current = cll->head;
	cll_node_t *next = NULL;

	if (cll->head == NULL) {
		goto ret;
	}

	while (current != cll->tail) {
		next = current->next;
		destroy(current->data);
		free(current);
		current = next;
	}

	destroy(cll->tail->data);
	free(cll->tail);

ret:
	cll->head = NULL;
	cll->tail = NULL;
	cll->nodes = 0;
}

int cll_insert_front(cll_t *cll, void *data)
{
	int ret_external = -1;
	int ret_internal;
	cll_node_t *new = NULL;

	if (cll == NULL) {
		goto ret;
	}

	/* If the Circular Linked Linked is empty insert into empty list */
	if (cll->head == NULL) {
		ret_internal = cll_insert_empty(cll, data);
		if (ret_internal == -1) {
			goto ret;
		}

		goto insert_success;
	}

	/* If not empty create a new node and add it to the front shifting the old head down */
	new = cll_create_node(data);
	if (new == NULL) {
		goto ret;
	}

	/* New's next becomes the old head */
	new->next = cll->tail->next;
	/* The tail's next becomes new head */
	cll->tail->next = new;
	/* The CLL's head becomes new */
	cll->head = new;

insert_success:
	cll->nodes++;
	ret_external = 0;
ret:
	return ret_external;
}

int cll_insert_rear(cll_t *cll, void *data)
{
	int ret_external = -1;
	int ret_internal;
	cll_node_t *new = NULL;

	/* If the Circular Linked Linked is empty insert into empty list */
	if (cll->head == NULL) {
		ret_internal = cll_insert_empty(cll, data);
		if (ret_internal == -1) {
			goto ret;
		}

		goto insert_success;
	}

	/* If not empty create a new node and add it to the rear updating the tail */
	new = cll_create_node(data);
	if (new == NULL) {
		goto ret;
	}

	cll->tail->next = new;
	new->next = cll->head;
	cll->tail = new;
	
insert_success:
	cll->nodes++;
	ret_external = 0;

ret:
	return ret_external;
}

int cll_insert_at_pos(cll_t *cll, size_t index, void *data)
{
	cll_node_t *new, *prev = NULL;
	cll_node_t *temp = cll->head;
	int ret_val = -1;
	size_t count = 0;

	/* If there are no nodes or requested index is 0*/
	if (cll->head == NULL || index == 0) {
		
			cll_insert_front(cll, data);
			goto insert_success;
	}

	/* If index is last node */
	if (index == cll->nodes - 1) {
		
			cll_insert_rear(cll, data);
			goto insert_success;
	}

	/* check if node index exists */
	while (temp->next != cll->head) {

		/* Node exists */
		if (count == index) {
			new = cll_create_node(data);
			if (new == NULL) {
				goto ret;
			}
			prev->next = new;
			new->next = temp;
			break;
		}
		prev = temp;
		temp = temp->next;
		count++;
	}

	/* Index does not exist */
	if (count != index) {
		printf("Index does not exist\n");
		goto ret;
	}

insert_success:
	cll->nodes++;
	ret_val = 0;
ret:
	return ret_val;
}

cll_node_t *cll_search(cll_t *cll, void *data, int (*compare)(void *a, void *b))
{
	cll_node_t *temp = NULL;
	cll_node_t *search = NULL;
	int cmp;

	if (cll == NULL) {
		goto ret;
	}

	if (cll->head == NULL) {
		goto ret;
	}

	cll->tail->next = NULL;
	temp = cll->head;

	while (temp) {
		cmp = compare(temp->data, data);
		if (cmp == 0){
			search = temp;
		}
		temp = temp->next;
	}
	cll->tail->next = cll->head;

ret:
	return search;
}

int cll_delete_node(cll_t *cll, void *data, void (*destroy)(void *))
{
	cll_node_t *current = NULL;
	cll_node_t *prev = NULL;
	int ret_val = 0;

	if (cll == NULL) {
		goto ret;
	}

	if (cll->head == NULL) {
		goto ret;
	}

	current = cll->head;
	prev = current;
	cll->tail->next = NULL;

	while (current) {

		if (current->data == data){
			/* Delete node */
			prev->next = current->next;
			destroy(current->data);
			cll->nodes--;
			free(current);
			break;
		}
		prev = current;
		current = current->next;
	}

	ret_val = 0;

ret:
	cll->tail->next = cll->head;
	return ret_val;
}

void cll_display_ints(cll_t *cll)
{
	cll_node_t *temp = cll->head;

	for (size_t i = 0; i < cll->nodes; i++) {
		printf("%d\n", *(int *)temp->data);
		temp = temp->next;
	};

}

void cll_display_strings(cll_t *cll)
{
	cll_node_t *temp = cll->head;

	for (size_t i = 0; i < cll->nodes; i++) {
		printf("%p --> %s\n", (void *)temp, (char *)temp->data);
		temp = temp->next;
	};

}

int cll_sorted_insert(cll_t *cll, cll_node_t **head_ref, void *data, int (*compare)(void *a, void *b))
{
	int ret_val = -1;
	int compare_result;
	cll_node_t *current = *head_ref;
	
	/* Base Case if no head, insert into empty*/
	if (current == NULL) {
		cll_insert_empty(cll, data);
		goto insert_success;
	}

	cll_node_t *new = cll_create_node(data);
	if (new == NULL) {
		goto ret;
	}
	
	/* if current data is greater than or equal to new data */
	compare_result = compare(current->data, new->data);

	if (compare_result >= 0) {
		/* If value is smaller than head's value then change next of last node */
		while(current->next != *head_ref) {
			current = current->next;
		}

		current->next = new;
		new->next = *head_ref;
		*head_ref = new;
	/* If the current next is not head and current next data is less than new data */
	} else {
		if (cll->nodes == 1) {
			new->next = current;
			current->next = new;
			*head_ref = new;
			goto insert_success;
		}
		
		while (current->next != *head_ref && compare(current->next->data, new->data) < 0) {
			current = current->next;
		}
	
		new->next = current->next;
		current->next = new;
	}
insert_success:
	cll->nodes++;
	ret_val = 0;
ret:
	return ret_val;
}

static int cll_insert_empty(cll_t *cll, void *data)
{
	int ret_val = -1;

	/* If the cll is not empty don't use this function */
	if (cll->head) {
		goto ret;
	}
	cll_node_t *new = cll_create_node(data);
	if (new == NULL) {
		goto ret;
	}
	cll->head = cll->tail = new;
	new->next = cll->head;
	ret_val = 0;

ret:
	return ret_val;
}