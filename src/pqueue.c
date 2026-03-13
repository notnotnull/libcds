#include "pqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int
adjust_pqueue (pqueue_t *pq)
{
  int ret_external = -1;
  int ret_internal = 0;
  if (pq == NULL)
    {
      goto ret;
    }
  size_t child_1 = 1;
  size_t child_2 = 2;
  size_t parent = 0;
  size_t size = 0;
  size_t current = 0;

  /* readjust binary heap since root (pq_array[0]) will be deleted */
  while (child_1 <= pq->elements - 1)
    {
      /* if only one child, or child 1 is a lower priority */
      if ((child_2 > pq->elements - 1) || (pq->array[child_1].priority < pq->array[child_2].priority))
        {
          /* Child 1 becomes parent */
          pq->array[parent] = pq->array[child_1];
          parent = child_1;
        }
      else
        {
          /* Child 2 becomes parent */
          pq->array[parent] = pq->array[child_2];
          parent = child_2;
        }
      child_1 = 2 * parent + 1;
      child_2 = 2 * parent + 2;
    }

  size = pq->elements;
  current = parent + 1;

  while (current != size)
    {
      pq->elements = current - 1;
      ret_internal = enpqueue (pq, pq->array[current].data, pq->array[current].priority);
      if (ret_internal == -1)
        {
          fprintf (stderr, "adjust_pqueue, enqueue\n");
          goto ret;
        }
      current++;
    }

  pq->elements = size - 1;

  if (pq->elements < pq->max_size / 2 && pq->elements >= 4)
    {
      pq->array = realloc (pq->array, sizeof (pqueue_element_t) * (pq->max_size / 2));
      if (pq->array == NULL)
        {
          fprintf (stderr, "adjust_pqueue, enqueue\n");
          goto ret;
        }
      pq->max_size = pq->max_size / 2;
    }

  ret_external = 0;
ret:
  return ret_external;
}

pqueue_t *
create_pqueue (size_t max_size)
{
  pqueue_t *pq = calloc (1, sizeof (pqueue_t));
  if (pq == NULL)
    {
      printf ("Unable to Allocate Priority Queue\n");
      goto ret;
    }
  pq->max_size = max_size;
  pq->array = malloc (sizeof (pqueue_element_t) * pq->max_size);
  if (pq->array == NULL)
    {
      printf ("Unable to Allocate Priority Queue Array\n");
    }

ret:
  return pq;
}

void
destroy_pqueue (pqueue_t **pq)
{
  free ((*pq)->array);
  free (*pq);
  *pq = NULL;
}

int
enpqueue (pqueue_t *pq, void *data, size_t priority)
{
  int ret_val = -1;
  if (pq == NULL)
    {
      goto ret;
    }

  size_t parent, child = 0;

  /* Dynamically Grow the Queue */
  if (pq->elements >= pq->max_size)
    {
      pq->max_size *= 2;
      pq->array = realloc (pq->array, sizeof (pqueue_element_t) * pq->max_size);
      if (pq->array == NULL)
        {
          perror ("realloc");
          goto ret;
        }
    }
  pq->elements++;

  /* new element is placed at bottom of the array */
  child = pq->elements - 1;
  parent = (child - 1) / 2;

  while ((child > 0) && (priority < pq->array[parent].priority))
    {
      pq->array[child] = pq->array[parent]; // Move parent down
      child = parent;                       // Child index becomes the parent parent index
      parent = (child - 1) / 2;             // Parent's new position
    }
  pq->array[child].data = data;
  pq->array[child].priority = priority;
  ret_val = 0;

ret:
  return ret_val;
}

void *
depqueue (pqueue_t *pq)
{
  void *popped = NULL;
  if (pq == NULL || pq->elements == 0)
    {
      goto ret;
    }
  int ret_internal = 0;

  popped = pq->array[0].data;

  if (pq->elements == 1)
    {
      pq->elements = 0;
    }
  else
    {
      ret_internal = adjust_pqueue (pq);
      if (ret_internal == -1)
        {
          fprintf (stderr, "Error adjusting pqueue");
        }
    }

ret:
  return popped;
}

pqueue_element_t *
search_pqueue (pqueue_t *pq, void *data)
{
  pqueue_element_t *element = NULL;
  if (pq == NULL)
    {
      goto ret;
    }

  for (size_t i = 0; i < pq->elements; i++)
    {
      if (pq->array[i].data == data)
        {
          element = &pq->array[i];
          goto ret;
        }
    }
ret:
  return element;
}

pqueue_element_t *
find_pqueue_index (pqueue_t *pq, size_t index)
{
  pqueue_element_t *indexed = NULL;
  if (pq == NULL || index >= pq->elements)
    {
      goto ret;
    }

  indexed = &pq->array[index];

ret:
  return indexed;
}

void
display_pqueue_ints (pqueue_t *pq)
{
  if (pq == NULL)
    {
      return;
    }
  printf ("PQUEUE ");
  for (size_t i = 0; i < pq->elements; i++)
    {
      printf ("%ld:%d\t", i, *(int *)pq->array[i].data);
    }
  puts ("");
}