#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"

queue_node_t *queue_create_node(void *data)
{
	queue_node_t *new = calloc(1, sizeof(queue_node_t));
	if (new == NULL) {
		goto ret;
	}
	new->data = data;

ret:
	return new;
}

queue_t *queue_create(void)
{
	queue_t *q = calloc(1, sizeof(queue_t));	
	return q;
}

void queue_destroy(queue_t **q)
{
	if (*q == NULL) {
		goto ret;
	}
	queue_node_t *temp;


	if ((*q)->head == NULL) {
		goto ret;
	}

	while ((*q)->head) {
		temp = (*q)->head;
		(*q)->head = (*q)->head->next;
		free(temp);
	}
ret:
	free(*q);
	*q = NULL;
}

int enqueue(queue_t *q, void *data)
{
	int ret_val = -1;
	
	if (q == NULL) {
		goto ret;
	}
	/* Create the new node */
	queue_node_t * new = queue_create_node(data);
	if (new == NULL) {
		goto ret;
	}

	/* If there is a NULL Head start the queue */
	if (q->head == NULL) {
		q->head = new;
		q->tail = new;
	/* Else insert at end and change the tail */
	} else {
		q->tail->next = new;
		q->tail = new;
	}
	q->nodes++;
	ret_val = 0;

ret:
	return ret_val;
}

queue_node_t *dequeue(queue_t *q)
{
	queue_node_t *dq = NULL;
	if (q == NULL) {
		goto ret;
	}
	dq = q->head;

	/* If head is not null then move the head and decrement nodes. */
	if (dq != NULL) {
		q->head = dq->next;
		q->nodes--;
	}

ret:
	return dq;
}

queue_node_t *queue_search(queue_t *q, void *data, int (*compare)(void *a, void *b))
{
	queue_node_t *search = NULL;
	if (q == NULL) {
		goto ret;
	}
	int cmp = 0;
	search = q->head;
	while (search) {
		cmp = compare(search->data, data);
		if (cmp == 0) {
			break;
		}
		search = search->next;
	}

ret:
	return search;
}

queue_node_t *queue_find_at_index(queue_t *q, size_t index)
{
	queue_node_t *find = NULL;
	if (q == NULL) {
		goto ret;
	}
	find = q->head;
	queue_node_t *idx_node = NULL;
	size_t count = 0;

	/* If NULL head */
	if (q->head == NULL) {
		goto ret;
	}

	/* check if node index exists */
	while (find) {
		/*  Index exists */
		if (count == index) {
			break;
		}
		find = find->next;
		count++;
	}

ret:
	return find;
}