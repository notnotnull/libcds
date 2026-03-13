#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dll.h"

dll_node_t *dll_create_node(void *data)
{
	dll_node_t *new = calloc(1, sizeof(dll_node_t));
	if (new == NULL) {
		goto ret;
	}
	new->data = data;

ret:
	return new;
}

dll_t *dll_create(void)
{
	dll_t *dll_p = calloc(1, sizeof(dll_t));	
	return dll_p;
}

void dll_destroy(dll_t **dll, void (*destroy)(void *))
{
	if (dll == NULL) {
		goto ret;
	}
	
	dll_node_t *current = (*dll)->head;
	dll_node_t *next = NULL;

	while (current) {
		next = current->next;
		destroy(current->data);
		free(current);
		current = next;
	}
ret:
	free(*dll);
	*dll = NULL;
}

int dll_insert_front(dll_t *dll, void *data)
{
	int ret_val = -1;

	if (dll == NULL) {
		goto ret;
	}

	dll_node_t *new = dll_create_node(data);
	if (new == NULL) {
		goto ret;
	}

	/* If NULL Head */
	if (dll->head == NULL) {
		dll->head = new;
		dll->tail = new;
	/* Else insert at beginning and change the head */
	} else {
		dll_node_t *old_head = dll->head;
		dll_node_t *new_head = new;

		new_head->next = old_head;
		old_head->previous = new_head;
		dll->head = new_head;
	}
	dll->nodes++;
	ret_val = 0;

ret:
	return ret_val;
}

int dll_insert_rear(dll_t *dll, void *data)
{
	int ret_val = -1;

	if (dll == NULL) {
		goto ret;
	}
	dll_node_t *new = dll_create_node(data);
	if (new == NULL) {
		goto ret;
	}

	/* NULL Head */
	if (dll->head == NULL) {
		dll->head = new;
		dll->tail = new;
	/* Else insert at end and change the tail */
	} else {
		dll_node_t *old_tail = dll->tail;
		dll_node_t *new_tail = new;

		new_tail->previous = old_tail;
		old_tail->next = new_tail;
		dll->tail = new_tail;

	}
	dll->nodes++;
	ret_val = 0;

ret:
	return ret_val;
}

int dll_insert_at_pos(dll_t *dll, size_t index, void *data)
{
	dll_node_t *new = NULL;
	dll_node_t *temp = NULL;
	int ret_val = -1;
	size_t count = 0;

	if (dll == NULL) {
		goto ret;
	}

	temp = dll->head;

	/* If there are no nodes or requested index is 0 */
	if (temp == NULL || index == 0) {
		dll_insert_front(dll, data);
		goto success;
	}

	/* check if node index exists */
	while (temp) {
		/*  Index exists */
		if (count == index) {
			new = dll_create_node(data);
			if (new == NULL) {
				goto ret;
			}
			temp->previous->next = new; /* A points to B */
			new->previous = temp->previous; /* B points to A */
			new->next = temp; /* B points to C */
			temp->previous = new;/* C points to B */
			dll->nodes++;

			break;
		}
		temp = temp->next;
		count++;
	}

	if (count != index) {
		goto ret;
	}

success:
	ret_val = 0;
ret:
	return ret_val;
}

int dll_delete_front(dll_t *dll)
{
	int ret_val = -1;
	dll_node_t *temp = dll->head;

	/* If NULL Head */
	if (temp == NULL) {
		goto ret;
	} else {
		dll->head = temp->next;
		dll->head->previous = NULL;
		free(temp);
	}

	dll->nodes--;

	ret_val = 0;

ret:
	return ret_val;
}

int dll_delete_rear(dll_t *dll)
{
	int ret_val = -1;
	dll_node_t *temp = dll->tail;

	/* If NULL Tail */
	if (temp == NULL) {
		goto ret;
	} else {
		dll->tail = temp->previous;
		dll->tail->next = NULL;
		free(temp);
	}
	dll->nodes--;
	ret_val = 0;

ret:
	return ret_val;
}

int dll_delete_at_pos(dll_t *dll, size_t index)
{
	dll_node_t *temp = dll->head;
	int ret_val = -1;
	size_t count = 0;

	/* If requested index is 0 */
	if (index == 0) {
		dll_delete_front(dll);
		goto success;
	}

	/* If requested index is last node */
	if (index == dll->nodes-1) {
		dll_delete_rear(dll);
		goto success;
	}

	/* check if node index exists */
	while (temp) {
		/*  Index exists */
		if (count == index) {
			temp->previous->next = temp->next;
			temp->next->previous = temp->previous;
			free(temp);
			dll->nodes--;

			break;
		}
		temp = temp->next;
		count++;

	}

	if (count != index) {
		goto ret;
	}

success:
	ret_val = 0;
ret:
	return ret_val;
}

dll_node_t *dll_search(dll_t *dll, void *data)
{
	dll_node_t *temp = dll->head;
	while (temp) {
		if (temp->data == data){
			return temp;
		}
		temp = temp->next;
	}

	return NULL;
}

int dll_insertion_sort(dll_t *dll, dll_node_t **head_ref, void *data, int (*compare)(void *a, void *b))
{
	int ret_val = -1;
	int compare_result;
	dll_node_t *current = *head_ref;
	
	/* Base Case if no head, insert into empty*/
	if (current == NULL) {
		dll_insert_front(dll, data);
		goto insert_success;
	}

	dll_node_t *new = dll_create_node(data);
	if (new == NULL) {
		goto ret;
	}
	
	/* if current data is greater than or equal to new data */
	compare_result = compare(current->data, new->data);

	dll->tail->next = *head_ref;

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
		if (dll->nodes == 1) {
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
	dll->tail->next = NULL;
	dll->nodes++;
	ret_val = 0;
ret:
	return ret_val;
}

void dll_display_strings(dll_t *dll)
{
	dll_node_t *current = dll->head;

	while (current) {
		printf("%s\n", (char *)current->data);
		current = current->next;
	}

	puts("");
}